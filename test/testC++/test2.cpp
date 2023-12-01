#include <stdlib.h>
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
#include <stdexcept>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
//
class WeatherPrediction {
   public:
    virtual ~WeatherPrediction();
    virtual void setCurrentTempFahrenheit(int temp);
    virtual void setPositionOfJupiter(int distanceFromMars);
    virtual int getTomorrowTempFahrenheit() const;
    virtual double getChanceOfRain() const;
    virtual void showResult() const;
    virtual std::string getTemperature() const;

   private:
    int m_currentTempFahrenheit{0};
    int distanceFromMars{0};
};

std::string WeatherPrediction::getTemperature() const {
    return std::to_string(m_currentTempFahrenheit);
}

class MyWeatherPrediction : public WeatherPrediction {
   public:
    virtual ~MyWeatherPrediction();
    virtual void setCurrentTempCelsius(int temp);
    virtual int getTomorrowTempCelsius() const;
    void showResult() const override;
    std::string getTemperature() const override;

   private:
    static int convertCelsiusToFahrenheit(int celsius);
    static int convertFahrenheitToCelsius(int fahrenheit);
};

int MyWeatherPrediction::convertCelsiusToFahrenheit(int celsius) {
    return (celsius * 9 / 5) + 32;
}

int MyWeatherPrediction::convertFahrenheitToCelsius(int fahrenheit) {
    return (fahrenheit - 32) * 5 / 9;
}

void MyWeatherPrediction::setCurrentTempCelsius(int temp) {
    int fahrenheitTemp{convertCelsiusToFahrenheit(temp)};
    setCurrentTempFahrenheit(fahrenheitTemp);
}

int MyWeatherPrediction::getTomorrowTempCelsius() const {
    int fahrenheitTemp{getTomorrowTempFahrenheit()};
    return convertFahrenheitToCelsius(fahrenheitTemp);
}

void MyWeatherPrediction::showResult() const {
    std::cout
        << std::format(
               "Tomorrow will be {} degrees Celsius ({} degrees Fahrenheit)",
               getTomorrowTempCelsius(), getTomorrowTempFahrenheit())
        << std::endl;
    std::cout << std::format("Chance of rain is {}%", getChanceOfRain() * 100)
              << std::endl;
    if (getChanceOfRain() > 0.5) {
        std::cout << "Bring an umbrella!" << std::endl;
    }
}

std::string MyWeatherPrediction::getTemperature() const {
    return WeatherPrediction::getTemperature() + "\u00B0F";
}

class Book {
   public:
    virtual ~Book() = default;
    virtual std::string getDescription() const { return "Book"; }
    virtual int getHeight() const { return 120; }
};

class Paperback : public Book {
   public:
    std::string getDescription() const override {
        return "Paperback " + Book::getDescription();
    }
};

class Romance : public Paperback {
   public:
    std::string getDescription() const override {
        return "Romance " + Paperback::getDescription();
    }
    int getHeight() const override { return Paperback::getHeight() / 2; }
};

class Technical : public Book {
   public:
    std::string getDescription() const override {
        return "Technical " + Book::getDescription();
    }
};

int main() {
    clock_t startTime{clock()};
    Romance novel;
    Book book;
    std::cout << novel.getDescription() << std::endl;
    std::cout << book.getDescription() << std::endl;
    std::cout << novel.getHeight() << std::endl;
    std::cout << book.getHeight() << std::endl;
    clock_t endTime{clock()};
    std::cout << endTime - startTime << std::endl;
    return 0;
}
