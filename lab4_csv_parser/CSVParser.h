#pragma once

#include <tuple>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>


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

		//Private functions
		void getRecord() {
			std::string line;
			if (!isEnd) {
				std::getline(parser->file, line);
				isEnd = parser->file.eof();
				record = parser->getRecord(line);
			}
		}

    public:
        explicit iterator() : isEnd(true) {}

        explicit iterator(CSVParser& parser) : parser(&parser) {
            auto& file = parser.file;
            while (!isEnd && lineNumber < parser.linesToSkip) {
                file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                isEnd = file.eof();
                lineNumber++;
            }
            /*for (; !isEnd && lineNumber < parser.linesToSkip; lineNumber++) {
                file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                isEnd = file.eof();
            }*/
            getRecord();
        }

        iterator& operator++() {
            if (!isEnd) {
                lineNumber++;
                getRecord();
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

    template<typename T, typename std::enable_if<!std::is_same<T, std::string>::value>::type* = nullptr>
    static T getValue(const std::string& token, std::size_t tokenNo) {
        static std::istringstream convertStream;

        T val;
        convertStream.clear();
        convertStream.str(token);
        convertStream >> val;

        return val;
    }

    template<typename T, typename std::enable_if<std::is_same<T, std::string>::value>::type* = nullptr>
    static const T& getValue(const std::string& token, std::size_t) {
        return token;
    }

    std::tuple<Args...> getRecord(const std::string& line) {
        std::string value;

        if (file.eof()) {
            return std::tuple<Args...>();
        }

        auto tokens = getTokens(line);
        auto tokensIterator = tokens.begin();

        std::size_t k = 0;
        return std::tuple<Args...>(getValue<Args>(*tokensIterator++, k++)...);
    }


};

