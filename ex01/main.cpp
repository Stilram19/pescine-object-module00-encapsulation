# include "Graph.hpp"

int main(int argc, char **argv) {
    try {

    }
    catch (const std::runtime_error &e) {
        std::cout << "ERROR: " << e.what() << std::endl;
    }
    catch (const std::bad_alloc &e) {
        std::cout << "BAD_ALLOC: " << e.what() << std::endl;
    }
    return (0);
}