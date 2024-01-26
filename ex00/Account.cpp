# include "Account.hpp"

// constructors
// Account::Account() : id(-1), value(0) {}

Account::Account(int id, int value) : id(id), value(value), loan_amount(0) {}

Account::~Account() {}

// setters

void Account::setValue(int value) {
    this->value = value;
}

void Account::setLoan(int value) {
    this->loan_amount = value;
}

void Account::payLoan(int value) {
    this->loan_amount -= value;
    this->value -= value;
}

// getters
int Account::getId() const {
    return this->id;
}

int Account::getValue() const {
    return this->value;
}

int Account::getTotalLoan() const {
    return this->loan_amount;
}

// friend function (global scope)
std::ostream& operator << (std::ostream& p_os, const Account& p_account)
{
    p_os << "[id: " << p_account.id << "] - [amount: " << p_account.value << "] - [totalLoan: " \
    << p_account.loan_amount << "]";
    return (p_os);
}