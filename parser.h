#pragma once
#include <optional>
#include "date.h"

// напишите в этом классе код, ответственный за чтение запросов

const char DefaultDelimeter = ' ';

inline std::vector<std::string_view> Split(std::string_view str) {
    std::vector<std::string_view> result;

    auto start = str.find_first_not_of(DefaultDelimeter);
    while (start != std::string_view::npos) {
        auto end = str.find(DefaultDelimeter, start);
        result.emplace_back(str.substr(start, end - start));
        start = str.find_first_not_of(DefaultDelimeter, end);
    }

    return result;
}
