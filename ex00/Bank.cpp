# include "Bank.hpp"

// constructor & destructor
Bank::Bank() : current_id(1), liquidity(0) {}

Bank::~Bank() {
    for (std::vector<Account *>::iterator it = this->clientAccounts.begin(); it != this->clientAccounts.end(); i++) {
        delete *it;
    }
}

// methods
void Bank::createAccount(int initial_amount) {
    if (this->current_id == MAX_ACCOUNTS_NUM) {
        std::cout << "The bank can't create an account for the moment, try later." << std::endl;
        return ;
    }
    try {
        Account *new_account = new Account(this->current_id, initial_amount);

        this->current_id++;
        clientAccounts.push_back(new_account);
    }
    catch (std::bad_alloc &e) {
        std::cout << "Memory allocation failed!" << e.what() << std::endl;
    }
}

void Bank::deleteAccount(int id) {
    for (std::vector<Account *>::iterator it = this->clientAccounts.begin(); it != this->clientAccounts.begin(); it++) {
        if ((*it)->getId() == id)
        {
            delete (*it);
            this->clientAccounts.erase(it);
            this->current_id--;
            return ;
        }
    }
}

void Bank::depositAmount(int id, int added_value) {
    for (std::vector<Account *>::const_iterator it = this->clientAccounts.begin(); it != this->clientAccounts.end(); it++) {
        if ((*it)->getId() == id) {
            // money deposit charge 5%
            size_t brute_amount = (*it)->getValue() + added_value;
            size_t net_amount = (*it)->getValue() + added_value * 0.95;

            if (added_value < MIN_AMOUNT) {
                std::cout << "You cannot deposit less than 100" << std::endl;
                return ;
            }

            if (net_amount > INT_MAX) {
                std::cout << "This number is too big to fit in your account, try with " \
                << INT_MAX - (*it)->getValue() << " or think of creating a new account" << std::endl;
                return ;
            }
            size_t new_liquidity = liquidity + brute_amount - net_amount;

            if (new_liquidity > INT_MAX) {
                std::cout << "ERROR, cannot perform this operation for the moment, try later." << std::endl;
                return ;
            }
            (*it)->setValue(net_amount);

            this->liquidity += brute_amount - net_amount;
            return ;
        }
    }
}

void Bank::loanClient(int id, int value) const {

    for (std::vector<Account *>::const_iterator it = this->clientAccounts.begin(); it != this->clientAccounts.end(); it++) {        
        if ((*it)->getId() == id) {
            if ((*it)->getTotalLoan() != 0) {
                std::cout << "Soory, you have to pay your debt first." << std::endl;
                return ;
            }
            if (value < MIN_AMOUNT || value > liquidity) {
                std::cout << "Sorry the bank can't loan you this amount, try " \
                << (liquidity >= 100 ? "100." : "later.") << std::endl;
                return ;
            }

            size_t new_amount = value + (*it)->getValue();

            if (new_amount > INT_MAX) {
                std::cout << "This loan is too much for your account, think of creating a new account" << std::endl;
                return ;
            }

            (*it)->setValue(new_amount);

            // a loan charges 10%
            (*it)->addLoan(value * 1.1);
            return ;
        }
    }
}

void Bank::payLoan(int id, int value) {
    if (value < MIN_AMOUNT) {
        std::cout << "You cannot pay less than " << MIN_AMOUNT << " back for your laon" << std::endl;
        return ;
    }
    for (std::vector<Account *>::const_iterator it = this->clientAccounts.begin(); it != this->clientAccounts.end(); it++) {
        if ((*it)->getId()) {
            if (value < MIN_AMOUNT) {
                std::cout << "You cannot pay less than " << MIN_AMOUNT << " back for your laon" << std::endl;
                return ;
            }
            if (value > (*it)->getTotalLoan()) {
                std::cout << "This is more than your total loan, you're loan is " << (*it)->getTotalLoan() << std::endl;
                return ;
            }

            size_t new_liquidity = liquidity + value;

            if (new_liquidity > INT_MAX) {
                std::cout << "ERROR, cannot perform this operation for the moment, try later." << std::endl;
                return ;
            }

            this->liquidity += value;
        }
    }
}

void Bank::moneyWithdraw(int id, int value) const {
    for (std::vector<Account *>::const_iterator it = this->clientAccounts.begin(); it != this->clientAccounts.end(); it++) {
        if ((*it)->getId() == id) {
            if (value < MIN_AMOUNT) {
                std::cout << "You cannot withdraw less than " << MIN_AMOUNT << std::endl;
                return ;
            }
            if (value > MAX_WITHDRAW) {
                std::cout << "You cannot withdraw more than " << MAX_WITHDRAW << " at once" << std::endl;
                return ;
            }
            if (value > (*it)->getValue()) {
                std::cout << "This is more than what you have in your account" << std::endl;
                return ;
            }
            int new_amount = (*it)->getValue() - value;

            (*it)->setValue(new_amount);
        }
    }
}

std::ostream& operator << (std::ostream& p_os, const Bank& p_bank)
{
    p_os << "Bank informations : " << std::endl;
    p_os << "Liquidity : " << p_bank.liquidity << std::endl;
    for (auto &clientAccount : p_bank.clientAccounts)
    p_os << *clientAccount << std::endl;
    return (p_os);
}
