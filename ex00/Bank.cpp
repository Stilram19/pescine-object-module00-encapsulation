# include "Bank.hpp"

// constructor & destructor
Bank::Bank() : current_id(1), liquidity(0) {}

Bank::~Bank() {

}

// methods
void Bank::createAccount(int initial_value) {
    try {
        Account *new_account = new Account(this->current_id, initial_value);

        clientAccounts.push_back(new_account);
    }
    catch (std::bad_alloc &e) {
        std::cout << "Memory allocation failed!" << e.what() << std::endl;
    }
}

void Bank::deleteAccount(int id) {

}

void Bank::modifyAccount(int id, int new_value) {

}

friend std::ostream& operator << (std::ostream& p_os, const Bank& p_bank)
{
    p_os << "Bank informations : " << std::endl;
    p_os << "Liquidity : " << p_bank.liquidity << std::endl;
    for (auto &clientAccount : p_bank.clientAccounts)
    p_os << *clientAccount << std::endl;
    return (p_os);
}
