//
// Created by Иванов Кирилл on 12.12.2024.
//
#pragma once

#include "iostream"
#include <map>
#include "../lexeme/lexeme.h"

class tid {
public:
    tid() = default;

    void pushId(lexemeType type, std::string& id);

    bool checkId(std::string& id);

    lexemeType getType(std::string& id);

private:
    std::map<std::string, lexemeType> data_;
};



