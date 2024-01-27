# include <iostream>
# include <vector>
# include <climits>

# define MIN_AMOUNT 100
# define MIN_AMOUNT_STR "100"
# define MAX_ACCOUNTS_NUM 1000000
# define MAX_WITHDRAW 2000
# define MAX_WITHDRAW_STR "2000"

struct Bank
{
    // encapsulating the Account struct
    private:
        struct Account {
            public:
                // Attributes
                int id;
                int value;
                int loan_amount;

                // copying is prohibited for accounts
                Account(const Account &);
                Account &operator=(const Account &);

                // cannot construct by default (the id and value are dependent on the bank)
                Account();
            public:
                // contructor & destructor
                Account(int id, int value);
                ~Account();

            public:
                // setters
                // void setValue(int value);
                // void setLoan(int value);
                // void payLoan(int value);

                // getters
                int getId() const;
                int getValue() const;
                int getTotalLoan() const;

            public:
                friend std::ostream& operator << (std::ostream& p_os, const Bank::Account& p_account);
        };

    private:
        // private attributes
        int current_id;
        int liquidity;
        int totalAccounts;
        std::vector<Bank::Account *> clientAccounts;

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
