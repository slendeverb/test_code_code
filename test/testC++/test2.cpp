#include <stdexcept>
#include <source_location>
#include <cstdarg>
#include <filesystem>
#include <iomanip>
#include <concepts>
#include <cstdio>
#include <ctime>
#include <bit>
#include <windows.h>
#include <algorithm>
#include <array>
#include <charconv>
#include <cmath>
#include <compare>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <format>
#include <fstream>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <locale>
#include <map>
#include <memory>
#include <numbers>
#include <optional>
#include <set>
#include <span>
#include <sstream>
#include <stack>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
//
using namespace std;
using namespace std::filesystem;

class FileError:public std::exception{
public:
    FileError(std::string fileName):m_fileName{std::move(fileName)}{}
    const char* what() const noexcept override {return m_message.c_str();}
    virtual const std::string& getFileName() const noexcept {return m_fileName;}
protected:
    virtual void setMessage(std::string message){m_message=std::move(message);}
private:
    std::string m_fileName;
    std::string m_message;
};

class FileOpenError:public FileError{
public:
    FileOpenError(std::string fileName):FileError{std::move(fileName)}{
        setMessage(std::format("Unable to open {}.",getFileName()));
    }
protected:
private:
};

class FileReadError:public FileError{
public:
    FileReadError(std::string fileName,size_t lineNumber)
        :FileError{std::move(fileName)},m_lineNumber{lineNumber}{
            setMessage(std::format("Error reading {}, line {}.",getFileName(),m_lineNumber));
        }
    virtual const size_t getLineNumber() const noexcept {return m_lineNumber;}
protected:
private:
    size_t m_lineNumber{0};
};

vector<int> readIntegerFile(string_view filename)
{
    ifstream inputStream{filename.data()};
    if (inputStream.fail())
    {
        // We failed to open the file: throw an exception.
        throw FileOpenError{filename.data()};
    }
    // Read the integers one-by-one and add them to a vector.
    vector<int> integers;
    size_t  lineNumber{0};
    while(!inputStream.eof()){
        std::string line;
        std::getline(inputStream,line);
        ++lineNumber;
        std::istringstream lineStream{line};
        int temp;
        while(lineStream>>temp){
            integers.push_back(temp);
        }
        if(!lineStream.eof()){
            throw FileReadError{filename.data(),lineNumber};
        }
    }
    return integers;
}

void logMessage(std::string_view message,const std::source_location& location = std::source_location::current()){
    std::cout<<std::format("{}({}): {}: {}",location.file_name(),location.line(),location.function_name(),message)<<std::endl;
}

class MyException:public std::exception{
public:
    MyException(std::string message,std::source_location location=std::source_location::current())
        :m_message{std::move(message)},m_location{std::move(location)}{}
    const char* what() const noexcept override {return m_message.c_str();}
    virtual const std::source_location& where() const noexcept {return m_location;}
protected:
private:
    std::string m_message;
    std::source_location m_location;
};



void solve()
{
    
}

int main()
{
    std::ifstream in{"../in.txt"};
    std::streambuf *oldIn{std::cin.rdbuf(in.rdbuf())};
    std::ofstream out{"../out.txt"};
    std::streambuf *oldOut{std::cout.rdbuf(out.rdbuf())};
    std::ofstream err{"../err.txt"};
    std::streambuf *oldErr{std::cerr.rdbuf(err.rdbuf())};
    std::streambuf *oldLog{std::clog.rdbuf(err.rdbuf())};

    clock_t startTime{clock()};
    solve();
    clock_t endTime{clock()};
    std::cout << "time cost: " << endTime - startTime << std::endl;
    return 0;
}
