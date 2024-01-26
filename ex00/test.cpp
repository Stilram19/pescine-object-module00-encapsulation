# include <iostream>
# include <climits>

class myClass {
    public:
    int a;
};

int main(void) {
    int a = 100, b = 101;
    int brute_amount = a + b;
    int net_amount = a + b * 0.95;

    std::cout << brute_amount - net_amount << ", " << b * 0.95 << ", " << net_amount << std::endl;
    return (0);
}
