//
// Created by Иванов Кирилл on 12.12.2024.
//

#include "tid.h"

std::string tid::getType(std::string &id) {
    if (!checkId(id)) throw 2;
    return data_[id];
}

bool tid::checkId(std::string &id) {
    return !data_[id].empty();
}

void tid::pushId(std::string &type, std::string &id) {
    if (!data_[id].empty()) throw 3;
    data_[id] = type;
}