# include "Graph.hpp"

// void    test1() {
//     Vector2 v(2, 2);
//     Graph g(v);

//     for (int i = 0; i <= 4; i++) {
//         v.resetX(i);
//         for (int j = 0; j <= 4; j++) {
//             v.resetY(j);
//             g.addPoint(v);
//             std::cout << "*************************************" << std::endl;
//         }
//     }
// }

int main(int argc, char **argv) {

    try {
        Graph g;

        if (argc != 2) {
            throw std::runtime_error("invalid number of arguments");
        }

        std::ifstream is(argv[1]);

        if (!is.is_open()) {
            throw std::runtime_error("Couldn't open the file");
        }

        g->parse_input_file(is);        
    }
    catch (const std::runtime_error &e) {
        std::cout << "ERROR: " << e.what() << std::endl;
    }
    catch (const std::bad_alloc &e) {
        std::cout << "BAD_ALLOC: " << e.what() << std::endl;
    }
    return (0);
}