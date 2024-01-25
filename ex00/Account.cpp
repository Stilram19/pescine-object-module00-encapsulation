# include "Account.hpp"

// constructors
// Account::Account() : id(-1), value(0) {}

Account::Account(int id, int value) : id(id), value(value), loan_amount(0) {}

Account::~Account() {}

// setters

void Account::setValue(int value) {
    this->value = value;
}

void Account::addLoan(int value) {
    this->loan_amount += value;
}

void Account::payLoan(int value) {
    this->loan_amount -= value;
}

// getters
int Account::getId(void) const {
    return this->id;
}

int Account::getValue(void) const {
    return this->value;
}

int Account::getTotalLoan(void) const {
    return this->loan_amount;
}

// friend function (global scope)
std::ostream& operator << (std::ostream& p_os, const Account& p_account)
{
    p_os << "[" << p_account.id << "] - [" << p_account.value << "]";
    return (p_os);
}