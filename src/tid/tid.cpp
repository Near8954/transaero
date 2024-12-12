//
// Created by Иванов Кирилл on 12.12.2024.
//

#include "tid.h"

lexemeType tid::getType(std::string &id) {
    if (!checkId(id)) throw 2;
    return data_[id];
}

bool tid::checkId(std::string &id) {
    return data_[id] != def;
}

void tid::pushId(lexemeType type, std::string &id) {
    if (data_[id] != def) throw 3;
    data_[id] = type;
}