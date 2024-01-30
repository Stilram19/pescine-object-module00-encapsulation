# include "Graph.hpp"

Graph::Graph() : g_size(MIN_COORDINATE, MIN_COORDINATE) {}

Graph::Graph(const Vector2 &size) {
    if (size.getX() > MAX_COORDINATE || size.getY() > MAX_COORDINATE
        || size.getX() < MIN_COORDINATE || size.getY() < MIN_COORDINATE) {
        throw std::runtime_error("Size is too big or too small");
    }
    this->g_size = size;
}

bool Graph::hasPoint(int x, int y) const {
    for (std::vector<Vector2 *>::const_iterator it = this->points.begin(); it != this->points.end(); it++) {
        if ((*it)->getX() == x && (*it)->getY() == y) {
            return (true);
        }
    }
    return (false);
}

void Graph::simpleGraphDisplay() const {
    for (int i = this->g_size.getY(); i >= 0; i--) {
        std::cout << ">&  " << i << (i > 9 ? " " : "  ");
        for (int j = 0; j <= this->g_size.getX(); j++) {
            std::cout << (Graph::hasPoint(j, i) == true ? "X" : ".");
            std::cout << (j < this->g_size.getX() ? "  " : "\n");
        }
    }
    std::cout << ">&     ";
    for (int i = 0; i <= this->g_size.getX(); i++) {
        std::cout << i << (i < this->g_size.getX() ? "  " : "\n");
    }
}

void Graph::addPoint(const Vector2 &p) {

    if (p.getX() > MAX_COORDINATE || p.getY() > MAX_COORDINATE
        || p.getX() < 0 || p.getY() < 0) {
        throw std::runtime_error("Coordinates are too big or too small");
    }

    if (this->hasPoint(p.getX(), p.getY())) {
        throw std::runtime_error("Point already exists!");
    }

    Vector2 *new_point = new Vector2(p);

    if (p.getX() >= this->g_size.getX()) {
        this->g_size.resetX(p.getX());
    }
    if (p.getY() >= this->g_size.getY()) {
        this->g_size.resetY(p.getY());
    }
    this->points.push_back(new_point);
    // this->simpleGraphDisplay();
}

void    Graph::parse_input_file(std::ifstream &is) {
    std::string my_buffer;

    while (std::getline(is, my_buffer)) {
        size_t pos = my_buffer.find(':');

        if (pos == std::string::npos) {
            throw HelpException("syntax error: expected ':'");
        }
        std::string key = my_buffer.substr(0, pos);

        if (key != "Point" && key != "Size" && key != "Line") {
            throw HelpException("Invalid Key");
        }

        std::string value = my_buffer.substr(pos + 1);

    }
}

void    Graph::parse_vector(const std::string &key, const std::string &value) {
    float x, y;
    size_t pos = value.find('/');

    if (pos == std::string::npos) {
        throw HelpException("syntax error: expected '/'");
    }

    std::string v1, v2;

    v1 = value.substr(0, pos);
    v2 = value.substr(pos + 1);

    if (!Graph::is_float(v1) || !Graph::is_float(v2)) {
        throw HelpException("the coordinates must be floats");
    }

    x = Graph::float_converter(v1);
    y = Graph::float_converter(v2);
    
    Vector2 v(x, y);
    
    if (key == "Size")
    {
        this->g_size = v;
        return ;
    }
    this->addPoint(v);
}

void    Graph::parse_line(const std::string &value) {
    size_t pos = value.find('/');

    if (pos == std::string::npos) {
        throw HelpException("syntax error: expected '/'");
    }

    std::string v1, v2, v3, v4;

    v1 = value.substr(0, pos);
    v2 = value.substr(pos + 1);
    pos = v2.find('-');

    if (pos == std::string::npos) {
        throw HelpException("Syntax error: expected '-'");
    }
    v3 = v2.substr(pos + 1);
    v2 = v2.substr(0, pos);
    pos = v3.find('/');
    if (pos == std::string::npos) {
        throw HelpException("Syntax error: expected '/'");
    }
    v4 = v3.substr(pos + 1);
    v3 = v3.substr(0, pos);

    Vector2 pt1(Graph::float_converter(v1), Graph::float_converter(v2));
    Vector2 pt2(Graph::float_converter(v3), Graph::float_converter(v4));

    // checking if the line is valid (diagonal)
    
}


// this is an old code reused here (from the cpp modules off the common core)
bool Graph::is_float(const std::string &literal)
{
	int			i = 0;
	bool		point = false;
	bool		end_f = false;
	std::string cmp;
	std::string temp;

	if (literal == "+inff" || literal == "-inff" || literal == "nanf")
		return (true);
	if (literal == ".f")
		return (false);
	temp = literal.c_str() + (literal[0] == '+' || literal[0] == '-');
	for (i = 0; temp[i]; i++)
	{
		if (!isdigit(temp[i]))
		{
			if (temp[i] == '.')
			{
				if (point)
					return (false);
				point = true;
				continue ;
			}
			if (temp[i] == 'f')
			{
				if (!point || temp[i + 1])
					return (false);
				end_f = true;
				continue ;
			}
			return (false);
		}
	}
	if (point && !end_f)
		return (false);
	for (i = 0; temp[i]; i++)
	{
		if (temp[i] == '.')
			break ;
	}
	cmp = temp.substr(0, i);
	if (cmp.length() > 39)
		return (false);
	return (true);
}

// Point: 0/1
// Size: 1/2
// Line: 1/0-2/2
