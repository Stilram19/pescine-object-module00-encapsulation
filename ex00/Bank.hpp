# include <iostream>
# include <vector>
# include <climits>
# include "Account.hpp"

# define MIN_AMOUNT 100
# define MAX_ACCOUNTS_NUM 1000000
# define MAX_WITHDRAW 2000

struct Bank
{
    private:
        // private attributes
        int current_id;
        int liquidity;
        int totalAccounts;
        std::vector<Account *> clientAccounts;

        // copying banks is prohibited
        Bank(const Bank &);
        Bank &operator=(const Bank &);

    public:
        // constructor & destructor
        Bank();
        ~Bank();

    public:
        // methods
        void createAccount(int initial_value);
        void deleteAccount(int id);
        void loanClient(int id, int value);
        void payLoan(int id, int value);
        void depositAmount(int id, int value);
        void modifyAmount(int id, int value);
        void moneyWithdraw(int id, int value) const;

        friend std::ostream& operator << (std::ostream& p_os, const Bank& p_bank);
};
