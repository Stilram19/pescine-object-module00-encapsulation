# include "Account.hpp"

// constructors
Account::Account() : id(-1), value(0) {}

Account::Account(int id, int value) : id(id), value(value) {}

Account::~Account() {}

// setters
void Account::setId(int id) {
    this.id = id;
}

void Account::setValue(int value) {
    this.value = value;
}

// getters
void Account::getId(void) {
    return this->id;
}

void Account::getValue(void) {
    return this->value;
}

// friend function (global scope)
std::ostream& operator << (std::ostream& p_os, const Account& p_account)
{
    p_os << "[" << p_account.id << "] - [" << p_account.value << "]";
    return (p_os);
}