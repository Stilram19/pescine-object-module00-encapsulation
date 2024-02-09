# include "Graph.hpp"

Graph::Graph() : g_size(MIN_COORDINATE, MIN_COORDINATE), png(NULL) {}

Graph::Graph(const Vector2 &size) {
    if (size.getX() > MAX_COORDINATE || size.getY() > MAX_COORDINATE
        || size.getX() < MIN_COORDINATE || size.getY() < MIN_COORDINATE) {
        throw std::runtime_error("Size is too big or too small");
    }
    this->g_size = size;
    this->png = NULL;
}

Graph::~Graph() {
    for (std::vector<Vector2 *>::iterator it = this->points.begin(); it != this->points.end(); it++) {
        delete (*it);
    }
    delete png;
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
    this->png = new Png(this->points, this->g_size);
    this->png->produce_png();
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

    Graph::trim(v1);
    Graph::trim(v2);

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

// this is an old code reused here (from the cpp modules of the common core)
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

// Png implementation

Graph::Png::Png(const std::vector<Vector2 *> &v_data, const Vector2 &g_size) {
    this->img_width = (g_size.getX() + 1) * PIXEL_SCALE;
    this->img_height = (g_size.getY() + 1) * PIXEL_SCALE;
    this->img_data = new int[this->img_width * this->img_height];

    for (size_t i = 0; i < v_data.size(); i++) {
        size_t init_j = v_data[i]->getX();
        size_t init_k = g_size.getY() - v_data[i]->getY();
        // std::cout << "POINT: " << init_j << ", " << init_k << std::endl;
        for (size_t j = init_j * PIXEL_SCALE; j < (init_j + 1) * PIXEL_SCALE; j++) {
            for (size_t k = init_k * PIXEL_SCALE; k < (init_k + 1) * PIXEL_SCALE; k++) {
            // std::cout << "J: " << j << ", " << "K: " << k << std::endl;
                int index = j + k * this->img_width;
                this->img_data[index] = 0xffffffff;
            }
        }
    }

    // make the crc table
    unsigned long crc;

    for (int i = 0; i < 256; i++) {
        crc = (unsigned long) i;
        for (int j = 0; j < 8; j++) {
            if (crc & 1) {
                crc = 0xedb88320L ^ (crc >> 1);
            } else {
                crc = crc >> 1;
            }
        }
        this->crc_table[i] = crc;
    }
    this->displayData();
}

Graph::Png::~Png() {
    delete this->img_data;
}

void Graph::Png::produce_png() const {
    // this->displayData()
    // name 
    std::ofstream os("graph.png", std::ios_base::out | std::ios_base::binary);

    if (!os.is_open()) {
        throw std::runtime_error("Can't open graph.png");
    }

    this->write_png_header(os);
    this->write_first_chunk(os);
    this->write_data_chunk(os);
    this->write_last_chunk(os);

    os.close();
}

void Graph::Png::write_first_chunk(std::ofstream &os) const {
    int length = this->big_endian(13);
    char type[] = "IHDR";
    int width = this->big_endian(this->img_width);
    int height = this->big_endian(this->img_height);
    char bit_depth = 8;
    char color_type = 6;
    char zero[] = {0, 0, 0};
    // char crc_input_data[] = {'I', 'H', 'D', 'R', (char)(width >> 24), (char)(width >> 16),
    // (char)(width >> 8), (char)(width), (char)(height >> 24), (char)(height >> 16), (char)(height >> 8), (char)(height), 8, 6, 0, 0, 0};

    unsigned char crc_input_data[] = {0x49, 0x48, 0x44, 0x52, 0x0, 0x0, 0x0, 0x06, 0x0, 0x0, 0x0, 0x6, 0x8, 0x6, 0x0, 0x0, 0x0};

    // for (int i = 0; i < 17; i++) {
    //     if (crc_input_data[i] != data[i]) {
    //         std::cout << "FALSE" << std::endl;
    //         return ;
    //     }
    // }

    // std::cout << "TRUEEE" << std::endl;

    // data length and chunk type
    os.write(reinterpret_cast<char *>(&length), sizeof(int));
    os.write(type, sizeof(type) - 1);

    // chunk data
    os.write(reinterpret_cast<char *>(&width), sizeof(int));
    os.write(reinterpret_cast<char *>(&height), sizeof(int));
    os.write(&bit_depth, 1);
    os.write(&color_type, 1);
    os.write(zero, 3);

    // crc
    unsigned int crc = this->cycle_redundancy_check(reinterpret_cast<unsigned char *>(crc_input_data), 17);
    unsigned int big_endian_crc = this->big_endian(crc);

    // write crc
    os.write(reinterpret_cast<char *>(&big_endian_crc), sizeof(unsigned int));

    if (os.fail()) {
        throw std::runtime_error("Can't write to Graph.png");
    }
}

void Graph::Png::write_data_chunk(std::ofstream &os) const {
    int little_endian_length = this->img_width * this->img_height * sizeof(int);
    int big_endian_length = this->big_endian(little_endian_length);
    char type[] = "IDAT";
    char *crc_input_data = new char[little_endian_length + sizeof(type) - 1];

    memcpy(crc_input_data, type, sizeof(type) - 1);
    memcpy(crc_input_data + sizeof(type) - 1, this->img_data, little_endian_length);

    // data length & chunk type
    os.write(reinterpret_cast<char *>(&big_endian_length), sizeof(int));
    os.write(type, sizeof(type) - 1);

    // chunk data
    os.write(reinterpret_cast<char *>(this->img_data), little_endian_length);

    // crc
    unsigned int crc = this->cycle_redundancy_check(reinterpret_cast<unsigned char *>(crc_input_data), little_endian_length + sizeof(type) - 1);
    unsigned int big_endian_crc = this->big_endian(crc);

    delete crc_input_data;

    // write crc
    os.write(reinterpret_cast<char *>(&big_endian_crc), sizeof(unsigned int));

    if (os.fail()) {
        throw std::runtime_error("Can't write to Graph.png");
    }
}

void Graph::Png::write_last_chunk(std::ofstream &os) const {
    int length = 0;
    char type[] = "IEND";

    // data length & chunk type
    os.write(reinterpret_cast<char *>(&length), sizeof(int));
    os.write(type, sizeof(type) - 1);

    // no data

    // crc
    // unsigned int crc = this->cycle_redundancy_check(NULL, 0);
    // unsigned int big_endian_crc = this->big_endian(crc);
// 0xae426082
// 0x826042ae
    int c = 0x826042ae;
    // write crc
    // os.write(reinterpret_cast<char *>(&big_endian_crc), sizeof(unsigned int));
    os.write(reinterpret_cast<char *>(&c), sizeof(unsigned int));

    if (os.fail()) {
        throw std::runtime_error("Can't write to Graph.png");
    }
}

unsigned long Graph::Png::cycle_redundancy_check(unsigned char *data, size_t len) const {
    unsigned long c = 0xffffffffL;

    for (size_t i = 0; i < len; i++) {
        c = crc_table[(c ^ data[i]) & 0xff] ^ (c >> 8);
    }
    return c ^ 0xffffffffL;
}

void Graph::Png::write_png_header(std::ofstream &os) const {
    char header[] = "\x89\x50\x4E\x47\x0D\x0A\x1A\x0A";

    os.write(header, 8);
    if (os.fail()) {
        throw std::runtime_error("failed to write to Graph.png");
    }
}

int Graph::Png::big_endian(int a) {
    int b = 0;

    b += (a << 24);
    b += (a << 8) & 0x00ff0000;
    b += (a >> 8) & 0x0000ff00;
    b += (a >> 24) & 0x000000ff;

    return (b);
}

void Graph::Png::displayData() const {
    std::cout << "IMG HEIGHT: " << this->img_height << ", IMG WIDTH: " << this->img_width << std::endl;
    for (size_t i = 0; i < this->img_height * this->img_width; i++) {
        std::cout << (this->img_data[i] ? "P" : "N");
        std::cout << ((i + 1) % this->img_width == 0 ? "\n" : " ");
    }
}
