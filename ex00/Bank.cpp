# include "Bank.hpp"

// constructor & destructor
Bank::Bank() : current_id(1), liquidity(0), totalAccounts(0) {}

Bank::~Bank() {
    for (std::map<int, Bank::Account *>::iterator it = this->clientAccounts.begin(); it != this->clientAccounts.end(); it++) {
        delete it->second;
    }
}

// methods
void Bank::createAccount(int initial_amount) {
    if (initial_amount < MIN_AMOUNT) {
        throw std::runtime_error("Initial Deposit must be no less than 100");
    }

    int transaction_fee = initial_amount * 0.05;
    size_t new_liquidity = this->liquidity + transaction_fee;

    if (new_liquidity > INT_MAX || this->totalAccounts == MAX_ACCOUNTS_NUM) {
        throw std::runtime_error("The bank can't create an account for the moment, try later.");
    }

    Bank::Account *new_account = new Bank::Account(this->current_id, initial_amount - transaction_fee);

    this->clientAccounts[this->current_id] = new_account;
    this->current_id++;
    this->totalAccounts++;
    this->liquidity += transaction_fee;
}

void Bank::deleteAccount(int id) {
    Bank::Account &acc = (*this)[id];

    size_t new_liquidity = this->liquidity + acc.getValue();

    if (new_liquidity > INT_MAX) {
        throw std::runtime_error("Error: cannot delete account for the moment, try later");
    }
    this->liquidity += acc.getValue();
    delete (this->clientAccounts.at(id));
    this->clientAccounts.erase(id);
    this->totalAccounts--;
}

void Bank::modifyAmount(int id, int new_value) {
    Bank::Account &acc = (*this)[id];

    if (new_value < 0) {
        throw std::runtime_error("try with a reasonable amount!");
    }
    // if the new value is more than the old one, then the bank needs to pay the difference
    // otherwise the difference goes to the bank.
    // the code below is checking the possibility of the operation.
    int diff = acc.getValue() - new_value;

    size_t new_liquidity = this->liquidity + diff;
    if (this->liquidity + diff < 0) {
        throw std::runtime_error("this operation is invalid.");
    }
    if (new_liquidity > INT_MAX) {
        throw std::runtime_error("this operation is invalid for the moment, try later please!");
    }
    this->liquidity += diff;

    acc.value = new_value;
    // acc.setValue(new_value);
}

void Bank::depositAmount(int id, int added_value) {
    Bank::Account &acc = (*this)[id];

    // money deposit charge 5%
    size_t transaction_fee = added_value * 0.05;
    size_t brute_amount = acc.getValue() + added_value;
    size_t net_amount = brute_amount - transaction_fee;

    if (added_value < MIN_AMOUNT) {
        throw std::runtime_error("You cannot deposit less than 100");
    }

    if (net_amount > INT_MAX) {
        throw std::runtime_error("This number is too big to fit in your account, think of creating a new account");
    }
    size_t new_liquidity = liquidity + transaction_fee;

    if (new_liquidity > INT_MAX) {
        throw std::runtime_error("cannot perform this operation for the moment, try later.");
    }
    acc.value = net_amount;
    // acc.setValue(net_amount);

    this->liquidity += transaction_fee;
}

void Bank::loanClient(int id, int value) {

    Bank::Account &acc = (*this)[id];

    if (acc.getTotalLoan() != 0) {
        throw std::runtime_error("Soory, you have to pay your debt first.");
    }
    if (value < MIN_AMOUNT || value > liquidity) {
        throw std::runtime_error("Sorry the bank can't loan you this amount, try ");
    }

    size_t new_amount = value + acc.getValue();

    if (new_amount > INT_MAX) {
        throw std::runtime_error("This loan is too much for your account, think of creating a new account");
    }

    acc.value = new_amount;
    // acc.setValue(new_amount);

    // a loan charges 10%
    this->liquidity -= value;

    acc.loan_amount = value * 1.1;
    // acc.setLoan(value * 1.1);
}

void Bank::payLoan(int id, int value) {
    Bank::Account &acc = (*this)[id];

    if (value <= 0) {
        throw std::runtime_error("ERROR: try with a reasonable amount!");
    }

    if (value > acc.getValue()) {
        throw std::runtime_error("You cannot afford this value, think of a deposit");
    }

    if (value > acc.getTotalLoan()) {
        throw std::runtime_error("This is more than your total loan");
    }

    size_t new_liquidity = liquidity + value;

    if (new_liquidity > INT_MAX) {
        throw std::runtime_error("ERROR, cannot perform this operation for the moment, try later.");
    }

    acc.loan_amount -= value;
    acc.value -= value;
    // acc.payLoan(value);
    this->liquidity += value;
}

void Bank::moneyWithdraw(int id, int value) const {
    Bank::Account &acc = (*this)[id];

    if (value < MIN_AMOUNT) {
        throw std::runtime_error("You cannot withdraw less than 100");
    }
    if (value > MAX_WITHDRAW) {
        throw std::runtime_error("You cannot withdraw more than 2000 at once");
    }
    if (value > acc.getValue()) {
        throw std::runtime_error("This is more than what you have in your account");
    }
    int new_amount = acc.getValue() - value;

    // acc.setValue(new_amount);
    acc.value = new_amount;
}

// friend function (global scope)
std::ostream& operator << (std::ostream& p_os, const Bank& p_bank)
{
    p_os << "Bank informations : " << std::endl;
    p_os << "Liquidity : " << p_bank.liquidity << std::endl;
    for (std::map<int, Bank::Account *>::const_iterator clientAccount = p_bank.clientAccounts.begin(); clientAccount != p_bank.clientAccounts.end(); clientAccount++) {
        p_os << "[id: " << clientAccount->second->getId() << "] - [amount: " << clientAccount->second->getValue() << "] - [totalLoan: " \
    << clientAccount->second->getTotalLoan() << "]" << std::endl;
    }
    return (p_os);
}

Bank::Account &Bank::operator[](int id) const {
    // out of range exception will be caught in the main function, if any.
    Bank::Account *acc = this->clientAccounts.at(id);

    return *acc;
}

// Bank::Account definitions

Bank::Account::Account(int id, int value) : id(id), value(value), loan_amount(0) {}

Bank::Account::~Account() {}

// setters

// void Bank::Account::setValue(int value) {
//     this->value = value;
// }

// void Bank::Account::setLoan(int value) {
//     this->loan_amount = value;
// }

// void Bank::Account::payLoan(int value) {
//     this->loan_amount -= value;
//     this->value -= value;
// }

// getters
int Bank::Account::getId() const {
    return this->id;
}

int Bank::Account::getValue() const {
    return this->value;
}

int Bank::Account::getTotalLoan() const {
    return this->loan_amount;
}
