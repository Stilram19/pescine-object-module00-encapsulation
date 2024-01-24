# include <iostream>
# include <vector>

struct Account;

struct Bank
{
    private:
        // private attributes
        static int current_id;
        int liquidity;
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
        void modifyAccount(int value);

        friend std::ostream& operator << (std::ostream& p_os, const Bank& p_bank);
};
