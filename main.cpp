#include "budget_manager.h"

#include <iostream>
#include <string_view>
#include "parser.h"

using namespace std;

int ReadNumberOnLine(istream& input) {
    std::string line;
    std::getline(input, line);
    return std::stoi(line);
}

void ParseAndProcessQuery(BudgetManager& manager, string_view line) {
    std::vector<std::string_view> parts = Split(line);
    
    if (parts.size() < 3) {
        std::cerr << "Invalid line format: " << line << std::endl;
        return;
    }

    std::cout << parts[0] << " " << parts[1] << " " << parts[2] << endl;
}

int main() {
    BudgetManager manager;

    const int query_count = ReadNumberOnLine(cin);

    for (int i = 0; i < query_count; ++i) {
        std::string line;
        std::getline(cin, line);
        ParseAndProcessQuery(manager, line);
    }
}
