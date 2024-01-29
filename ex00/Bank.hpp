# include <iostream>
# include <map>
# include <climits>

# define MIN_AMOUNT 100
# define MAX_ACCOUNTS_NUM 1000000
# define MAX_WITHDRAW 2000

struct Bank
{
    // encapsulating the Account struct
    private:
        struct Account {
            private:
                // copying is prohibited for accounts
                Account(const Account &);
                Account &operator=(const Account &);
            public:
                // Attributes
                int id;
                int value;
                int loan_amount;

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
        std::map<int, Bank::Account *> clientAccounts;

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

        Bank::Account &operator[](int id) const;
        friend std::ostream& operator << (std::ostream& p_os, const Bank& p_bank);
};
