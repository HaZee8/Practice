#pragma once

#include <string>
#include <map>
#include <stdexcept>
#include <sstream>
#include <type_traits>

class SystemParameters {
public:
    void setParameter(const std::string& key, const std::string& value);

    template<typename T>
    T getParameter(const std::string& key) const;

private:
    std::map<std::string, std::string> systemParams;
};

template<typename T>
T SystemParameters::getParameter(const std::string& key) const {
    auto it = systemParams.find(key);
    if (it == systemParams.end()) {
        throw std::runtime_error("Системный параметр не найден");
    }
    std::istringstream iss(it->second);
    T result;

    if constexpr (std::is_same<T, bool>::value) {
        std::string temp;
        iss >> temp;
        if (temp == "true" || temp == "1") {
            result = true;
        }
        else if (temp == "false" || temp == "0") {
            result = false;
        }
        else {
            throw std::runtime_error("Неверный ввод для булевого типа");
        }
    }
    else {
        if (!(iss >> result)) {
            throw std::runtime_error("Неверный ввод");
        }
    }

    return result;
}
