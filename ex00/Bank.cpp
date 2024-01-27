# include "Bank.hpp"

// constructor & destructor
Bank::Bank() : current_id(1), liquidity(0), totalAccounts(0) {}

Bank::~Bank() {
    for (std::vector<Bank::Account *>::iterator it = this->clientAccounts.begin(); it != this->clientAccounts.end(); it++) {
        delete *it;
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

    try {
        Bank::Account *new_account = new Bank::Account(this->current_id, initial_amount - transaction_fee);

        this->current_id++;
        this->totalAccounts++;
        this->liquidity += transaction_fee;
        clientAccounts.push_back(new_account);
    }
    catch (std::bad_alloc &e) {
        throw std::runtime_error("We're out of memory!");
    }
}

void Bank::deleteAccount(int id) {
    for (std::vector<Bank::Account *>::iterator it = this->clientAccounts.begin(); it != this->clientAccounts.end(); it++) {
        if ((*it)->getId() == id)
        {
            size_t new_liquidity = this->liquidity + (*it)->getValue();

            if (new_liquidity > INT_MAX) {
                throw std::runtime_error("Error: cannot delete account for the moment, try later");
            }
            this->liquidity += (*it)->getValue();
            delete (*it);
            this->clientAccounts.erase(it);
            this->totalAccounts--;
            return ;
        }
    }
}

void Bank::modifyAmount(int id, int new_value) {
    for (std::vector<Bank::Account *>::const_iterator it = this->clientAccounts.begin(); it != this->clientAccounts.end(); it++) {
        if ((*it)->getId() == id) {
            if (new_value < 0) {
                throw std::runtime_error("ERROR: try with a reasonable amount!");
            }
            // if the new value is more than the old one, then the bank needs to pay the difference
            // otherwise the difference goes to the bank.
            // the code below is checking the possibility of the operation.
            int diff = (*it)->getValue() - new_value;

            size_t new_liquidity = this->liquidity + diff;
            if (this->liquidity + diff < 0 || new_liquidity > INT_MAX) {
                throw std::runtime_error("Error: this operation is invalid for the moment, try later.");
            }
            this->liquidity += diff;

            (*it)->value = new_value;
            // (*it)->setValue(new_value);
            return ;
        }
    }
}

void Bank::depositAmount(int id, int added_value) {
    for (std::vector<Bank::Account *>::const_iterator it = this->clientAccounts.begin(); it != this->clientAccounts.end(); it++) {
        if ((*it)->getId() == id) {
            // money deposit charge 5%
            size_t transaction_fee = added_value * 0.05;
            size_t brute_amount = (*it)->getValue() + added_value;
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
            (*it)->value = net_amount;
            // (*it)->setValue(net_amount);

            this->liquidity += transaction_fee;
            return ;
        }
    }
}

void Bank::loanClient(int id, int value) {

    for (std::vector<Bank::Account *>::const_iterator it = this->clientAccounts.begin(); it != this->clientAccounts.end(); it++) {        
        if ((*it)->getId() == id) {
            if ((*it)->getTotalLoan() != 0) {
                throw std::runtime_error("Soory, you have to pay your debt first.");
            }
            if (value < MIN_AMOUNT || value > liquidity) {
                throw std::runtime_error("Sorry the bank can't loan you this amount, try ");
            }

            size_t new_amount = value + (*it)->getValue();

            if (new_amount > INT_MAX) {
                throw std::runtime_error("This loan is too much for your account, think of creating a new account");
            }

            (*it)->value = new_amount;
            // (*it)->setValue(new_amount);

            // a loan charges 10%
            this->liquidity -= value;

            (*it)->loan_amount = value * 1.1;
            // (*it)->setLoan(value * 1.1);
            return ;
        }
    }
}

void Bank::payLoan(int id, int value) {
    for (std::vector<Bank::Account *>::const_iterator it = this->clientAccounts.begin(); it != this->clientAccounts.end(); it++) {
        if ((*it)->getId() == id) {
            if (value <= 0) {
                throw std::runtime_error("ERROR: try with a reasonable amount!");
            }

            if (value > (*it)->getValue()) {
                throw std::runtime_error("You cannot afford this value, think of a deposit");
            }

            if (value > (*it)->getTotalLoan()) {
                throw std::runtime_error("This is more than your total loan");
            }

            size_t new_liquidity = liquidity + value;

            if (new_liquidity > INT_MAX) {
                throw std::runtime_error("ERROR, cannot perform this operation for the moment, try later.");
            }

            (*it)->loan_amount -= value;
            (*it)->value -= value;
            // (*it)->payLoan(value);
            this->liquidity += value;
        }
    }
}

void Bank::moneyWithdraw(int id, int value) const {
    for (std::vector<Bank::Account *>::const_iterator it = this->clientAccounts.begin(); it != this->clientAccounts.end(); it++) {
        if ((*it)->getId() == id) {
            if (value < MIN_AMOUNT) {
                throw std::runtime_error("You cannot withdraw less than 100");
            }
            if (value > MAX_WITHDRAW) {
                throw std::runtime_error("You cannot withdraw more than 2000 at once");
            }
            if (value > (*it)->getValue()) {
                throw std::runtime_error("This is more than what you have in your account");
            }
            int new_amount = (*it)->getValue() - value;

            // (*it)->setValue(new_amount);
            (*it)->value = new_amount;
        }
    }
}

// friend function (global scope)
std::ostream& operator << (std::ostream& p_os, const Bank& p_bank)
{
    p_os << "Bank informations : " << std::endl;
    p_os << "Liquidity : " << p_bank.liquidity << std::endl;
    for (std::vector<Bank::Account *>::const_iterator clientAccount = p_bank.clientAccounts.begin(); clientAccount != p_bank.clientAccounts.end(); clientAccount++) {
        p_os << "[id: " << (*clientAccount)->getId() << "] - [amount: " << (*clientAccount)->getValue() << "] - [totalLoan: " \
    << (*clientAccount)->getTotalLoan() << "]" << std::endl;
    }
    return (p_os);
}

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
