#ifndef GRPAH_HPP
# define GRAPH_HPP

# include <fstream>
# include <string>
# include <sstream>
# include <cmath>
# include <cstring>
# include "Vector2.hpp"
# include "HelpException.hpp"

# define MAX_COORDINATE 10
# define MIN_COORDINATE 2
# define PIXEL_SCALE 4
# define POINT_COLOR 0xFF0000FF
# define BACKGROUND_COLOR 0xFFFF0000

class Graph {

    // Png class encapsulated within the Graph class
    private:
        class Png {
            private:
                size_t img_width;
                size_t img_height;
                int *img_data;
                unsigned long crc_table[256];

            private:
                Png();
                Png(const Png &other);
                Png &operator=(const Png &other);

            private:
                static int big_endian(int a);
                void write_png_header(std::ofstream &os) const;
                void displayData() const;
                void write_first_chunk(std::ofstream &os) const;
                void write_data_chunk(std::ofstream &os) const;
                void write_last_chunk(std::ofstream &os) const;
                unsigned long cycle_redundancy_check(unsigned char *data, size_t len) const;

            public:
                Png(const std::vector<Vector2 *> &v_data, const Vector2 &g_size);
                ~Png();

                void produce_png() const;
        };

    // Attributes
    private:
        Vector2                 g_size;
        std::vector<Vector2 *>  points;
        Graph::Png              *png;

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