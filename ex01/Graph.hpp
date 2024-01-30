# include <fstream>
# include <string>
# include <sstream>
# include "Vector2.hpp"
# include "HelpException.hpp"

# define MAX_COORDINATE 10
# define MIN_COORDINATE 2

class Graph {
    private:
        Vector2                 g_size;
        std::vector<Vector2 *>  points;

    public:
        Graph();
        Graph(const Vector2 &size);

    // methods
    private:
        bool    hasPoint(int x, int y) const;

    public:
        void        addPoint(const Vector2 &p);
        void        simpleGraphDisplay() const;
        void        parse_vector(const std::string &key, const std::string &value);
        void        parse_line(const std::string &value);
        void        parse_input_file(std::ifstream &is);

        // static functions
        static void displayHelp();
        static bool is_float(const std::string &literal);
        static float float_converter(const std::string &str);
};
