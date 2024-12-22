//
// Created by Роман Балдин on 22.12.2024.
//

#ifndef FUNCTION_TABLE_H
#define FUNCTION_TABLE_H
#include <string>
#include <vector>
#include "../lexeme/lexeme.h"
#include "../error/error.h"

class function_table {
public:
    void checkId(const std::string &function_name, const lexemeType return_type,
                 const std::vector<lexemeType> &args) const {
        for (auto e: table_) {
            if (e.name_ == function_name && e.args_ == args) {
                throw Error("Function already defined");
            }
        }
    }

    void push(const std::string &name, const lexemeType return_type, const std::vector<lexemeType> &args) {
        checkId(name, return_type, args);
        table_.push_back({name, return_type, args});
    }

    lexemeType getType(const std::string &function_name,
                       const std::vector<lexemeType> &args) {
        for (const auto& e: table_) {
            if (e.name_ == function_name && e.args_ == args) {
                return e.return_type_;
            }
        }
        throw Error("Unknown function");
    }

private:
    struct function {
        std::string name_;
        lexemeType return_type_;
        std::vector<lexemeType> args_;
    };

    std::vector<function> table_;
};


#endif //FUNCTION_TABLE_H
