# include "Graph.hpp"

Graph::Graph() : g_size(0) {}

Graph::Graph(size_t size) {

    if (size > MAX_GRAPH_SIZE) {
        throw std::runtime_error("Graph size is too big!");
    }

    this->g_size = Graph::adjust_size(size);
}

// private methods

void Graph::displayGraph() {

}

int Graph::sqrt(size_t x) {

    if (x == 0) {
        return (0);
    }

    size_t lower = 1, upper = x, mid;

    while (lower <= upper) {
        mid = (upper + lower) / 2;
        if (mid * mid == x) {
            return mid;
        }
        if (mid * mid < x) {
            lower = mid + 1;
            continue ; 
        }
        upper = mid - 1;
    }
    return (-1);
}

// public methods

void Graph::addPoint(const Vector2 &p) {

    if (p.getX() > MAX_COORDINATE || p.getY() > MAX_COORDINATE) {
        throw std::runtime_error("Coordinates are too big for the graph");
    }

    Vector2 *new_point = new Vector2(p.getX(), p.getY());
    size_t max_coord = p.getX() > p.getY() ? p.getX() : p.getY();
    this->g_size = max_coord * max_coord >= this->g_size ? max_coord * max_coord + 1 : this->g_size;

    this->displayGraph();
}

// this function adjusts the size so it become a perfect square
// it is based on the fact that the floor of the sqrt of a non perfect square number
// is the sqrt of the first perfect square which happens to be less than our number.
size_t Graph::adjust_size(size_t size) {

    size_t ret = 0;

    for (size_t i = size; i > 0; i--) {
        ret = Graph::sqrt(i);

        if (ret != -1) {
            break ;
        }
    }

    return (ret);
}
