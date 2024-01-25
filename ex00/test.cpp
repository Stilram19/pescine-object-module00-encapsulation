# include <iostream>
# include <climits>

class myClass {
    public:
    int a;
};

int main(void) {
    int a, b, c = INT_MAX;

    a = 0.95 * c;
    b = 0.05 * c;

    std::cout << a << ", " << b << ", " << a + b << std::endl;
    return (0);
}
