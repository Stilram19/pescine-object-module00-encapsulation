# include <iostream>

struct Account
{
    private:
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
        void setValue(int value);
        void setLoan(int value);
        void payLoan(int value);

        // getters
        int getId() const;
        int getValue() const;
        int getTotalLoan() const;

    public:
        friend std::ostream& operator << (std::ostream& p_os, const Account& p_account);
};
