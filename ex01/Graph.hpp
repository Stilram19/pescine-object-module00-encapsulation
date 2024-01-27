# include "Vector2.hpp"

# define MAX_DIM 10

class Graph {
    private:
        Vector2                 limits;
        std::vector<Vector2 *>  points;

    // methods
    private:
        void    displayGraph();

    public:
        void    addPoint(const Vector2 &p);
};
