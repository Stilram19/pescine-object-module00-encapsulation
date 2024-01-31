# include "Graph.hpp"

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

        g.parse_and_execute(is);      
    }
    catch (const HelpException &e) {
        std::cout << "INVALID INPUT: " << e.what() << std::endl;
        Graph::displayHelp();
    }
    catch (const std::runtime_error &e) {
        std::cout << "ERROR: " << e.what() << std::endl;
    }
    catch (const std::bad_alloc &e) {
        std::cout << "BAD_ALLOC: " << e.what() << std::endl;
    }
    return (0);
}
