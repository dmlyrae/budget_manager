#pragma once
#include <numeric>
#include "date.h"
#include <iostream>

struct DayBudget {
    double income = 0.0;
    double spend = 0.0;
};

template <typename Data>
Data operator+(const Data& lhs, const Data& rhs) {
    Data result;
    result.income = lhs.income + rhs.income;
    result.spend = lhs.spend + rhs.spend;
    return result;
}

class BudgetManager {
public:
    inline static const Date START_DATE{2000, 1, 1};
    inline static const Date END_DATE{2100, 1, 1};
    inline static const double TAX_COEF = 0.87;

    BudgetManager() {
        size_t days_size = GetDayIndex(END_DATE) - GetDayIndex(START_DATE);
        days_.resize(days_size, 0.0);
    }

    static size_t GetDayIndex(Date day) {
        return static_cast<size_t>(Date::ComputeDistance(START_DATE, day));
    }

    void Earn(Date from, Date to, int sum) {
        size_t index_from = GetDayIndex(from);
        size_t index_to = GetDayIndex(to);
        size_t earn_length = index_to - index_from + 1;
        double day_sum = (sum / static_cast<double>(earn_length));
        for (size_t i = index_from; i <= index_to; ++i) {
            days_[i] += day_sum;
        }
    }

    void PayTax(Date from, Date to) {
        size_t index_from = GetDayIndex(from);
        size_t index_to = GetDayIndex(to);
        for (size_t i = index_from; i <= index_to; ++i) {
            days_[i] *= TAX_COEF;
            // std::cout << "tax for day " << i << ": " << days_[i] << std::endl;
        }
    }

    double ComputeIncome(Date from, Date to) {
        size_t index_from = GetDayIndex(from);
        size_t index_to = GetDayIndex(to);
        return accumulate(days_.begin() + index_from, days_.begin() + index_to + 1, 0.0);
    }

private:
    std::vector<double> days_;
};
