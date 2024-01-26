# include "Bank.hpp"
# include <cstdlib>

// struct Account
// {
//     private:
//         // private attributes
// 	    int id;
// 	    int value;

//     public:

//         Account(): id(-1), value(0) {}

//         friend std::ostream& operator << (std::ostream& p_os, const Account& p_account)
//         {
//             p_os << "[" << p_account.id << "] - [" << p_account.value << "]";
//             return (p_os);
//         }
// };

// struct Bank
// {
//     private:
//         // private attributes
//         int liquidity;
//         std::vector<Account *> clientAccounts;

//     public:

//         Bank() : liquidity(0) {}

//         friend std::ostream& operator << (std::ostream& p_os, const Bank& p_bank)
//         {
//             p_os << "Bank informations : " << std::endl;
//             p_os << "Liquidity : " << p_bank.liquidity << std::endl;
//             for (auto &clientAccount : p_bank.clientAccounts)
//             p_os << *clientAccount << std::endl;
//             return (p_os);
//         }
// };

// int main()
// {
// 	Account accountA = Account();
// 	accountA.id = 0;
// 	accountA.value = 100;

// 	Account accountB = Account();
// 	accountB.id = 1;
// 	accountB.value = 100;

// 	Bank bank = Bank();
// 	bank.liquidity = 999;
// 	bank.clientAccounts.push_back(&accountA);
// 	bank.clientAccounts.push_back(&accountB);

// 	bank.liquidity -= 200;
// 	accountA.value += 400;

// 	std::cout << "Account : " << std::endl;
// 	std::cout << accountA << std::endl;
// 	std::cout << accountB << std::endl;

// 	std::cout << " ----- " << std::endl;

// 	std::cout << "Bank : " << std::endl;
// 	std::cout << bank << std::endl;

// 	return (0);
// }

void test1() {
	Bank b;

	std::cout << b;
	b.createAccount(0);
	std::cout << b;
	b.createAccount(-1);
	std::cout << b;
	b.createAccount(10);
	std::cout << b;
	b.createAccount(99);
	std::cout << b;
	b.createAccount(100);
	std::cout << b;
}

void	test2() {
	Bank b;

	std::cout << b;
	b.createAccount(100);
	std::cout << b;
	b.createAccount(101);
	std::cout << b;
	b.createAccount(102);
	std::cout << b;
	b.createAccount(103);
	std::cout << b;
	b.createAccount(104);
	std::cout << b;
	b.createAccount(105);
	std::cout << b;
	b.createAccount(106);
	std::cout << b;
	b.createAccount(107);
	std::cout << b;
	b.createAccount(108);
	std::cout << b;
	b.createAccount(109);
	std::cout << b;
	b.createAccount(110);
	std::cout << b;
	b.createAccount(14555);
	std::cout << b;
}

void	test3() {
	Bank b;

	b.createAccount(100);
	std::cout << b;
	b.depositAmount(1, 10);
	std::cout << b;
	b.depositAmount(2, 2000);
	std::cout << b;
	b.depositAmount(1, 101);
	std::cout << b;
	b.depositAmount(1, 2094);
	std::cout << b;
	b.depositAmount(1, 100);
	std::cout << b;
}

void	test4() {
	Bank b;

	b.createAccount(100);
	b.loanClient(1, 2);
	std::cout << b;
	b.createAccount(100000);
	std::cout << b;
	b.loanClient(1, 100);
	std::cout << b;
	b.loanClient(1, 1000);
	std::cout << b;
	b.payLoan(1, 50);
	std::cout << b;
	b.payLoan(1, 100);
	std::cout << b;
	b.payLoan(1, 60);
	std::cout << b;
	b.loanClient(1, 150);
	std::cout << b;
	b.moneyWithdraw(1, 150);
	std::cout << b;
	b.payLoan(1, 165);
	std::cout << b;
	b.depositAmount(1, 100);
	std::cout << b;
	b.payLoan(1, 165);
	std::cout << b;
}

void	test5() {
	Bank b;

	b.createAccount(100);
	b.createAccount(100);
	b.createAccount(100);
	b.createAccount(100);
	b.createAccount(100);

	std::cout << b;

	b.modifyAmount(1, 0);
	b.modifyAmount(2, 400);
	b.modifyAmount(3, 123);

	std::cout << b;

	b.deleteAccount(20);
	b.deleteAccount(2);
	b.deleteAccount(5);

	std::cout << b;

	b.createAccount(1000);

	std::cout << b;
}

void	test6() {
	Bank b;

	b.createAccount(100);
	std::cout << b;
	b.modifyAmount(1, 200);
	std::cout << b;
	b.modifyAmount(1, 100);
	std::cout << b;
	for (int i = 0; i < 25; i++) {
		b.createAccount(INT_MAX);
	}

	std::cout << b;
}

void	test7() {
	Bank b;

	b.createAccount(INT_MAX);
	b.depositAmount(1, INT_MAX);
	std::cout << b;
}

int	main() {
	// test1();
	// test2();
	// test3();
	// test4();
	// test5();
	// test6();
	// test7();
	return (0);
}
