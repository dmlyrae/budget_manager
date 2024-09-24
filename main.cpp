#include "budget_manager.h"

#include <iostream>
#include <string_view>
#include "parser.h"
#include "date.h"

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

    Date date_from = Date::FromString(parts[1]);
    Date date_to = Date::FromString(parts[2]);

    if (parts[0] == "ComputeIncome") {
        ReadQuery read_query(date_from, date_to);
        read_query.Print(manager, std::cout);
    } else if (parts[0] == "PayTax") {
        PayQuery pay_query(date_from, date_to);
        pay_query.Process(manager);
    } else if (parts[0] == "Earn" && parts.size() == 4) {
        size_t sum = static_cast<size_t>(stoi(string(parts[3])));
        IncomeQuery income(date_from, date_to, sum);
        income.Process(manager);
    }

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
