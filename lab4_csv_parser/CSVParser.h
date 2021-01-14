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

		std::tuple<Args...> record;

		void _getRecord() {
			std::string line;
			if (!isEnd) {
				std::getline(parser->file, line);
				isEnd = parser->file.eof();
				record = parser->getRecord(line);
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

        while (getline(tmp_stream, token, ';')) {
            tokens.push_back(token);
        }

        return tokens;
    }

    template<typename T>
    T getValueFromStr(const std::string& str) {
        std::stringstream convertStream(str);
        T val;
        convertStream >> val;
        return val;
    }

    template<>
    std::string getValueFromStr<std::string>(const std::string& str) {
        return str;
    }

    template<size_t N>
    void fillTuple(std::tuple<Args...>& t, std::vector<std::string>& strings) {
        std::get<N - 1>(t) = getValueFromStr<std::tuple_element<N - 1, std::tuple<Args...>>::type>(strings.at(N - 1));
        fillTuple<N - 1>(t, strings);
    }

    template<>
    void fillTuple<1>(std::tuple<Args...>& t, std::vector<std::string>& strings) {
        std::get<0>(t) = getValueFromStr<std::tuple_element<0, std::tuple<Args...>>::type>(strings.at(0));
    }
    
    std::tuple<Args...> getRecord(const std::string& line) {
        if (file.eof()) {
            return std::tuple<Args...>();
        }
        std::vector<std::string> strings(getStrings(line));

        std::tuple<Args...> result; 
        fillTuple<sizeof...(Args)>(result, strings);

        return result;
    }
};
