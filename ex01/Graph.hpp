#ifndef GRPAH_HPP
# define GRAPH_HPP

# include <fstream>
# include <string>
# include <sstream>
# include <cmath>
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
        ~Graph();
        Graph(const Vector2 &size);

    // methods
    private:
        bool    hasPoint(int x, int y) const;

    public:
        void    resize_graph(const Vector2 &new_size);
        void    addPoint(const Vector2 &p);
        void    simpleGraphDisplay() const;
        void    parse_vector(const std::string &key, const std::string &value);
        void    parse_line(const std::string &value);
        void    parse_and_execute(std::ifstream &is);

        // static functions
        static void displayHelp();
        static bool is_float(const std::string &literal);
        static float float_converter(const std::string &str);
        static void trim(std::string &str);
};

#endif