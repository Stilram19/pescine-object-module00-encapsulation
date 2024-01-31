# include "Graph.hpp"

Graph::Graph() : g_size(MIN_COORDINATE, MIN_COORDINATE) {}

Graph::Graph(const Vector2 &size) {
    if (size.getX() > MAX_COORDINATE || size.getY() > MAX_COORDINATE
        || size.getX() < MIN_COORDINATE || size.getY() < MIN_COORDINATE) {
        throw std::runtime_error("Size is too big or too small");
    }
    this->g_size = size;
}

Graph::~Graph() {
    for (std::vector<Vector2 *>::iterator it = this->points.begin(); it != this->points.end(); it++) {
        delete (*it);
    }
}

void Graph::resize_graph(const Vector2 &new_size) {
    if (new_size.getX() < MIN_COORDINATE || new_size.getY() < MIN_COORDINATE
        || new_size.getX() > MAX_COORDINATE || new_size.getY() > MAX_COORDINATE) {
            throw std::runtime_error("coordinates are too big or too small");
        }
    if (new_size.getX() < this->g_size.getX() || new_size.getY() < this->g_size.getY()) {
        throw std::runtime_error("cannot resize Graph with smaller size!");
    }
    this->g_size = new_size;
}

bool Graph::hasPoint(int x, int y) const {
    Vector2 cmp(x, y);

    for (std::vector<Vector2 *>::const_iterator it = this->points.begin(); it != this->points.end(); it++) {
        if (**it == cmp) {
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
        return ;
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

void    Graph::parse_and_execute(std::ifstream &is) {
    std::string my_buffer;

    while (std::getline(is, my_buffer)) {
        if (my_buffer.empty()) {
            continue ;
        }

        size_t pos = my_buffer.find(':');

        if (pos == std::string::npos) {
            throw HelpException("syntax error: expected ':'");
        }
        std::string key = my_buffer.substr(0, pos);


        Graph::trim(key);
        if (key != "Point" && key != "Size" && key != "Line") {
            throw HelpException("Invalid Key");
        }

        std::string value = my_buffer.substr(pos + 1);

        if (key == "Point" || key == "Size")
        {
            this->parse_vector(key, value);
            continue ;
        }

        this->parse_line(value);
    }

    this->simpleGraphDisplay();
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

    // std::cout << "(*) BEFORE: " << std::endl;
    // std::cout << "v1: |" << v1 << "|" << std::endl;
    // std::cout << "v2: |" << v2 << "|" << std::endl;

    Graph::trim(v1);
    Graph::trim(v2);    

    // std::cout << "(*) AFTER: " << std::endl;
    // std::cout << "v1: |" << v1 << "|" << std::endl;
    // std::cout << "v2: |" << v2 << "|" << std::endl;

    if (!Graph::is_float(v1) || !Graph::is_float(v2)) {
        throw HelpException("the coordinates must be floats");
    }

    x = Graph::float_converter(v1);
    y = Graph::float_converter(v2);

    Vector2 new_size(x, y);

    if (key == "Size")
    {
        this->resize_graph(new_size);
        return ;
    }
    std::cout << "POINT: " << new_size.getX() << '/' << new_size.getY() << std::endl;
    this->addPoint(new_size);
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

    Graph::trim(v1);
    Graph::trim(v2);
    Graph::trim(v3);
    Graph::trim(v4);

    if (!Graph::is_float(v1) || !Graph::is_float(v2) || !Graph::is_float(v3) || !Graph::is_float(v4)) {
        throw HelpException("the coordinates must be floats");
    }

    Vector2 pt1(Graph::float_converter(v1), Graph::float_converter(v2));
    Vector2 pt2(Graph::float_converter(v3), Graph::float_converter(v4));

    std::cout << "Line: " << v1 << "/" << v2 << "-" << v3 << "/" << v4 << std::endl;

    // checking if the line is valid
    if (pt1 == pt2) {
        throw HelpException("Invalid line!");
    }

    if (fabs(pt1.getX() - pt2.getX()) != fabs(pt1.getY() - pt2.getY())
        && pt1.getX() != pt2.getX() && pt1.getY() != pt2.getY()) {
        throw HelpException("Invalid line!");
    }

    // adding the line to the graph point by point
    while (pt1 != pt2) {
        this->addPoint(pt1);

        if (pt1.getX() < pt2.getX()) {
            pt1.resetX(pt1.getX() + 1);
        }
        if (pt1.getX() > pt2.getX()) {
            pt1.resetX(pt1.getX() - 1);
        }
        if (pt1.getY() < pt2.getY()) {
            pt1.resetY(pt1.getY() + 1);
        }
        if (pt1.getY() > pt2.getY()) {
            pt1.resetY(pt1.getY() - 1);
        }

        this->addPoint(pt1);
    }
}

void    Graph::displayHelp() {
    std::cout << std::endl << "=====> HELP: " << std::endl << std::endl;
    std::cout << "(*) Each line must be in the form: 'KEY: VALUE' without quotes." << std::endl;
    std::cout << "(*) KEY is 'Size', 'Point' or 'Line'" << std::endl;
    std::cout << "(*) For 'Size' and 'Point', VALUE must be in the from: X/Y (X and Y must be floats)" << std::endl;
    std::cout << "(*) For 'Line', VALUE must be in the form: X1/X2-X3/X4 (X1, X2, X3 and X4 must be floats, they are the coordinates of the two points that defines the line)" << std::endl;
    std::cout << "(*) For 'Line', VALUE must be in the form: X1/X2-X3/X4 (X1, X2, X3 and X4 must be floats, they are the coordinates of the two points that defines the line)" << std::endl;
    std::cout << "(*) Coordinates must be not more than " << MAX_COORDINATE << std::endl;
    std::cout << "(*) Size Coordinates must be no less than " << MIN_COORDINATE << std::endl;
    std::cout << "(*) Point Coordinates must be no less than 0" << std::endl;
    std::cout << "(*) Lines can be either diagonal, horizontal or vertical" << std::endl;
}

// this is an old code reused here (from the cpp modules off the common core)
bool Graph::is_float(const std::string &literal)
{
	int			i = 0;
	bool		point = false;
	std::string cmp;
	std::string temp(literal);

    if (temp.empty() || temp == ".f") {
        return (false);
    }

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
				continue ;
			}
			return (false);
		}
	}
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

float Graph::float_converter(const std::string &str) {
    float a;
    std::stringstream s;

    s << str;
    s >> a;

    return (a);
}

void Graph::trim(std::string &str) {
    size_t start = str.find_first_not_of(" \t");
    size_t end = str.find_last_not_of(" \t");

    if (start == std::string::npos) {
        str = "";
        return ;
    }
    str = str.substr(start, end - start + 1);
}
