#pragma once

#include <tuple>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <exception>


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
        //CSVParser& parser;
		bool isEnd = false;
		std::size_t lineNumber = 0;

		std::tuple<Args...> record;

		//Private functions
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

    std::vector<std::string> getTokens(const std::string& line) {
        std::string token;
        std::vector<std::string> tokens;

        std::stringstream tmp_stream(line);

        while (getline(tmp_stream, token, ';')) {
            tokens.push_back(token);
        }

        return tokens;
    }

    template<typename T>
    T getValue(const std::string& str) {
        cout << typeid(T).name() << endl; // for debug
        //std::stringstream convertStream(str);
        T val;
        std::istringstream convertStream;
        convertStream.clear();
        convertStream.str(str);
        //convertStream << str;
        //convertStream >> val;
        if (convertStream >> val) {
            string errorMassage = "GetValue error. std::stringstream convertStream failed. Current var. type is ";
            errorMassage += typeid(T).name();
            throw std::exception(errorMassage.c_str());
        }
        return val;
    }

    template<>
    std::string getValue<std::string>(const std::string& str) {
        return str;
    }

    template<>
    int getValue<int>(const std::string& str) {
        return std::stoi(str);
    }

    template<>
    double getValue<double>(const std::string& str) {
        return std::stod(str);
    }

    template<>
    float getValue<float>(const std::string& str) {
        return std::stof(str);
    }

    template<>
    char getValue<char>(const std::string& str) {
        return str.at(0);
    }


    
    std::tuple<Args...> getRecord(const std::string& line) {
        if (file.eof()) {
            return std::tuple<Args...>();
        }
        std::vector<std::string> tokens(getTokens(line));

        reverse(tokens.begin(), tokens.end());
        auto tokensIterator = tokens.begin();

        std::tuple<Args...> result = std::tuple<Args...>(getValue<Args>(*tokensIterator++)...);

        return result;
    }
};
