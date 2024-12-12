//
// Created by Иванов Кирилл on 12.12.2024.
//
#pragma once

#include "iostream"
#include <map>

class tid {
public:
    tid() = default;

    void pushId(std::string& type, std::string& id);

    bool checkId(std::string& id);

    std::string getType(std::string& id);

private:
    std::map<std::string, std::string> data_;
};



