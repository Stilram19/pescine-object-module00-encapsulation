# include "Graph.hpp"

void Graph::displayGraph() {

}

void Graph::addPoint(const Vector2 &p) {
    if (p.getX() > MAX_DIM || p.getY() > MAX_DIM) {
        throw std::runtime_error("Too big coordinates");
    }
    try {
        Vector2 *new_p = new Vector2(p);

        this->points.push_back(new_p);
        float max_coordinate = new_p->getX() > new_p->getY() ? new_p->getX() : new_p->getY();

        if (max_coordinate >= this->limits.getX())
            this->limits.reset(max_coordinate + 1);
        this->displayGraph();
    }
    catch (std::bad_alloc &e) {
        throw std::runtime_error("We're out of memory!");
    }
}
