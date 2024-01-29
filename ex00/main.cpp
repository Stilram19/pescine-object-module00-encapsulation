# include "Bank.hpp"

void accountCreationTest1(int initial_deposit) {
	Bank b;

	std::cout << b;
	b.createAccount(initial_deposit);
	std::cout << b;
}

void	accountCreationTest2() {
	Bank b;

	std::cout << b;
	for (int i = 0; i < 12; i++) {
		b.createAccount(100 + i);
		std::cout << b;
	}
}

void	depositTest1(int id, int deposit) {
	Bank b;

	b.createAccount(100);
	std::cout << b;
	b.depositAmount(id, deposit);
	std::cout << b;
}

void	depositTest2() {
	Bank b;

	for (int i = 0; i < 10; i++) {
		b.createAccount(100 + i);
	}

	std::cout << b;

	for (int i = 0; i < 10; i++) {
		b.depositAmount(i + 1, 100 + i);
		std::cout << b;
	}
}

void	loanTest1(int id, int initial_amount, int value) {
	Bank b;

	std::cout << b;
	b.createAccount(initial_amount);
	std::cout << b;
	b.loanClient(id, value);
	std::cout << b;
}

void	loanTest2() {
	Bank b;

	b.createAccount(10000);
	std::cout << b;
	b.loanClient(1, 100);
	std::cout << b;
	b.loanClient(1, 100);
	std::cout << b;
}

void	loanTest3() {
	Bank b;

	b.createAccount(10000);
	std::cout << b;
	b.loanClient(1, 100);
	std::cout << b;
	b.payLoan(1, 110);
	std::cout << b;
	b.loanClient(1, 100);
	std::cout << b;
}

void	deleteAccountTest(int id) {
	Bank b;

	for (int i = 0; i < 10; i++) {
		b.createAccount(100 + i);
	}

	std::cout << "(*) BEFORE: " << std::endl;
	std::cout << b;

	b.deleteAccount(id);

	std::cout << "(*) AFTER: " << std::endl;
	std::cout << b;
}

void	modifyAmountTest(int id, int value) {
	Bank b;

	for (int i = 0; i < 10; i++) {
		b.createAccount(100 + i);
	}

	std::cout << "(*) BEFORE: " << std::endl;
	std::cout << b;

	b.modifyAmount(id, value);

	std::cout << "(*) AFTER: " << std::endl;
	std::cout << b;
}

void	overflowTest1() {
	Bank b;

	b.createAccount(100);
	std::cout << b;
	for (int i = 0; i < 25; i++) {
		b.createAccount(INT_MAX);
	}

	std::cout << b;
}

void	overflowTest2() {
	Bank b;

	b.createAccount(INT_MAX);
	b.depositAmount(1, INT_MAX);
	std::cout << b;
}

int	main() {
	try {
		// accountCreationTest1(10);
		// accountCreationTest2();
		// depositTest1(1, 10000);
		// depositTest2();
		// loanTest1(1, 10000, 100);
		// loanTest2();
		// loanTest3();
		// deleteAccountTest(110);
		// modifyAmountTest(1, 130);
		// overflowTest1();
		// overflowTest2();
	}
	catch (const std::runtime_error &e) {
		std::cout << "ERROR: " << e.what() << std::endl;
	}
	catch (const std::out_of_range &e) {
		std::cout << "OUT_OF_RANGE: No such account with the provided Id" << std::endl;
	}
	catch (const std::bad_alloc &e) {
		std::cout << "BAD_ALLOC: We're out of memory!" << std::endl;
	}
	return (0);
}
