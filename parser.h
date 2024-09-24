#pragma once
#include <optional>
#include <cstddef>
#include "date.h"
#include "budget_manager.h"

// напишите в этом классе код, ответственный за чтение запросов

const char DefaultDelimeter = ' ';

// const enum Command {
// 	ComputeIncome,
// 	Earn,
// 	PayTax
// };

inline std::vector<std::string_view> Split(std::string_view str, char delimeter = DefaultDelimeter) {
	std::vector<std::string_view> result;

	auto start = str.find_first_not_of(delimeter);
	while (start != std::string_view::npos) {
		auto end = str.find(DefaultDelimeter, start);
		result.emplace_back(str.substr(start, end - start));
		start = str.find_first_not_of(DefaultDelimeter, end);
	}

	return result;
}

struct ReadResult {
	void Print(std::ostream& out) {
		out << total.income - total.spend << std::endl;
	}
	DayBudget total;
};

class Query {
public:

	Query(Date from, Date to)
		: from_(from), 
		to_(to) {}

	Date GetFrom() const {
		return from_;
	}

	Date GetTo() const {
		return to_;
	}

	virtual ~Query() = default;

private:
	Date from_, to_;
	// Command command_;
};

class ReadQuery : public Query {
public:
	using Query::Query;

    ReadQuery(Date from, Date to) 
        : Query(from, to) {}

	void Print(BudgetManager& budget, std::ostream& out) const {
		double income = budget.ComputeIncome(GetFrom(), GetTo());
		out << income << std::endl; 
	};

	virtual ~ReadQuery() = default;
};

class EditQuery : public Query {
public:
	using Query::Query;

	~EditQuery() = default;
};

class IncomeQuery : public EditQuery {
public:
    IncomeQuery(Date from, Date to, size_t sum = 0) 
        : EditQuery(from, to),
		sum_(sum) {}

    void Process(BudgetManager& budget) const {
		budget.Earn(GetFrom(), GetTo(), sum_);
    }

    virtual ~IncomeQuery() = default;
private:
	size_t sum_;
};

class PayQuery : public EditQuery {
public:
    PayQuery(Date from, Date to) 
        : EditQuery(from, to) {}

	void Process(BudgetManager& budget) const {
		budget.PayTax(GetFrom(), GetTo());
	};

	virtual ~PayQuery() = default;
};