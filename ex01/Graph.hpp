# include "Vector2.hpp"

# define MAX_GRAPH_SIZE 100
# define MAX_COORDINATE 9
# define SQRT_OF(X) Graph::sqrt(X)

class Graph {
    private:
        size_t                  g_size;
        std::vector<Vector2 *>  points;

    public:
        Graph();
        Graph(size_t size);

    // methods
    private:
        void         displayGraph();
        static int   sqrt(size_t x);

    public:
        void            addPoint(const Vector2 &p);
        static size_t   adjust_size(size_t size);
};
