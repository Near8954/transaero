//
// Created by Иванов Кирилл on 12.12.2024.
//

#include "tid.h"

lexemeType tid::getType(std::string &id) {
    if (!checkId(id)) {
        throw std::runtime_error("Variable not initialized");
    }
    return data_[id];
}

bool tid::checkId(std::string &id) {
    return data_[id] != def;
}

void tid::pushId(lexemeType type, std::string &id) {
    if (data_[id] != def) {
        throw std::runtime_error("Variable already initialized");
    }
    data_[id] = type;
}