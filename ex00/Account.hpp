# include <iostream>

struct Account
{
    private:
        // Attributes
        int id;
        int value;

        // copying is prohibited for accounts
        Account(const Account &);
        Account &operator=(const Account &);

    public:
        // contructor & destructor
        Account();
        ~Account();

        // setters
        void setId(int id);
        void setValue(int value);

        // getters
        void getId(void);
        void getValue(void);

    public:
        friend std::ostream& operator << (std::ostream& p_os, const Account& p_account);
};
