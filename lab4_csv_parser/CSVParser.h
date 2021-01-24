#pragma once

#include <tuple>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <exception>
#include <iterator>


using namespace std;

template<typename... Args>
class CSVParser {
private:
	ifstream& file;
	size_t linesToSkip = 0;
    char sepSymbol = ';';

public:
	CSVParser(std::ifstream& _file, const size_t& _linesToSkip) : file(_file), linesToSkip(_linesToSkip) {}
	virtual ~CSVParser() = default;

	class iterator : public std::iterator<std::input_iterator_tag, std::tuple<Args...>,
		long, const std::tuple<Args...>*, std::tuple<Args...>> 
    {

	private:
		CSVParser* parser = nullptr;
		bool isEnd = false;
		std::size_t lineNumber = 0;

        //std::size_t currentLine = lineNumber;
		std::tuple<Args...> record;

		void _getRecord() {
            try {
                std::string line;
                if (!isEnd) {
                    std::getline(parser->file, line);
                    isEnd = parser->file.eof();
                    record = parser->getRecord(line);
                }
            }
            catch (const std::exception& e) {
                string massage = e.what();
                massage += to_string(lineNumber + 1);
                massage += " line. ";
                throw exception(massage.c_str());
            }
			
		}

    public:

        explicit iterator() : isEnd(true) {}

        explicit iterator(CSVParser& _parser) : parser(&_parser) {
            auto& file = _parser.file;
            while (!isEnd && lineNumber < _parser.linesToSkip) {
                file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                isEnd = file.eof();
                lineNumber++;
            }
            _getRecord();
        }

        iterator& operator++() {
            if (!isEnd) {
                lineNumber++;
                _getRecord();
            }
            return *this;
        }

        const iterator operator++(int) {
            iterator retVal = *this;
            ++(*this);
            return retVal;
        }

        bool operator==(const iterator& other) {
            return (isEnd && other.isEnd) || (!isEnd && !other.isEnd && (lineNumber == other.lineNumber));
        }

        bool operator!=(const iterator& other) {
            return !(*this == other);
        }

        std::tuple<Args...>& operator*() {
            return record;
        }

	}; // iterator 

    iterator begin() {
        return iterator(*this);
    }
    iterator end() {
        return iterator();
    }

    std::vector<std::string> getStrings(const std::string& line) {
        std::string token;
        std::vector<std::string> tokens;

        std::stringstream tmp_stream(line);

        while (getline(tmp_stream, token, sepSymbol)) {
            tokens.push_back(token);
        }

        return tokens;
    }

    template<typename T>
    T getValueFromStr(const std::string& str) {
        std::stringstream convertStream(str);
        T val;
        if (!(convertStream >> val)) {
            std::string massage = "Parser type error. ";
            throw std::exception(massage.c_str());
        }
        return val;
    }

    template<>
    std::string getValueFromStr<std::string>(const std::string& str) {
        return str;
    }

    template<size_t N>
    void fillTuple(std::tuple<Args...>& t, std::vector<std::string>& strings) {
        try {
            std::get<N - 1>(t) = getValueFromStr<std::tuple_element<N - 1, std::tuple<Args...>>::type>(strings.at(N - 1));
        }
        catch (const std::exception& e) {
            string massage = e.what();
            massage += "Wrong type at ";
            massage += to_string(N);
            massage += " column. ";
            throw exception(massage.c_str());
            return;
        }
        fillTuple<N - 1>(t, strings);
    }

    template<>
    void fillTuple<1>(std::tuple<Args...>& t, std::vector<std::string>& strings) {
        try {
            std::get<0>(t) = getValueFromStr<std::tuple_element<0, std::tuple<Args...>>::type>(strings.at(0));
        }
        catch (const std::exception& e) {
            string massage = e.what();
            massage += "Wrong type at ";
            massage += to_string(1);
            massage += " column. ";
            throw std::exception(massage.c_str());
            return;
        }
    }
    
    std::tuple<Args...> getRecord(const std::string& line) {
        if (file.eof()) {
            return std::tuple<Args...>();
        }
        std::vector<std::string> strings(getStrings(line));

        /*auto stringsIterator = strings.begin();
        return std::tuple<Args...>(getValueFromStr<Args>(*stringsIterator++)...);*/

        std::tuple<Args...> result; 
        try {
            fillTuple<sizeof...(Args)>(result, strings);
        }
        catch (const std::exception& e) {
            throw e;
        }

        return result;
    }

    void setSepSymbol(const char& symbol) {
        sepSymbol = symbol;
    }
};
