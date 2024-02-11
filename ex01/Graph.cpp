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
    // 1 added to the width is for the filter bytes for each scanline (row)
    this->img_width = (g_size.getX() + 1) * PIXEL_SCALE;
    this->img_height = (g_size.getY() + 1) * PIXEL_SCALE;
    this->img_size = this->img_width * this->img_height;
    this->img_data = new int[img_size];

    for (size_t i = 0; i < this->img_size; i++) {
        this->img_data[i] = BACKGROUND_COLOR;
    }

    // adding the pixels and the filter bytes
    for (size_t i = 0; i < v_data.size(); i++) {
        size_t init_j = v_data[i]->getX();
        size_t init_k = g_size.getY() - v_data[i]->getY();
        for (size_t j = init_j * PIXEL_SCALE; j < (init_j + 1) * PIXEL_SCALE; j++) {
            for (size_t k = init_k * PIXEL_SCALE; k < (init_k + 1) * PIXEL_SCALE; k++) {
                int index = j + k * this->img_width;
                this->img_data[index] = POINT_COLOR;
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

// int Graph::Png::get_compression_info() const {
//     int ret = this->img_size * sizeof(int);
//     int w_size_log;

//     for (w_size_log = 0; ret > 1; w_size_log++) {
//         ret /= 2;
//     }

//     w_size_log -= 8;
//     if (w_size_log < 8)
//         w_size_log = 8;

//     if (w_size_log > )

//     return (w_size_log << 4);
// }

char *Graph::Png::get_format_header(size_t uncompressed_data_size) const {
    char *format_header = new char[7];

    // the zlib header (2 bytes)
    format_header[0] = 0x78; // CM
    format_header[1] = 0x01;

    // the essential infos (5 bytes)
    format_header[2] = 0x01; // the first bit indicates the last data chunk
    format_header[3] = uncompressed_data_size >> 8; // the size of the uncompressed data
    format_header[4] = uncompressed_data_size;
    format_header[5] = format_header[3] ^ 0xff; // the size in 1's complement (redundancy used for error detection)
    format_header[6] = format_header[4] ^ 0xff;

    return (format_header);
}

void Graph::Png::write_first_chunk(std::ofstream &os) const {
    int length = this->big_endian(13);
    char type[] = "IHDR";
    int width = this->big_endian(this->img_width);
    int height = this->big_endian(this->img_height);
    char bit_depth = 8;
    char color_type = 6;
    char zero[] = {0, 0, 0};
    unsigned char crc_input_data[17];

    memcpy(crc_input_data, type, sizeof(type) - 1);
    memcpy(crc_input_data + 4, &width, sizeof(int));
    memcpy(crc_input_data + 8, &height, sizeof(int));
    memcpy(crc_input_data + 12, &bit_depth, 1);
    memcpy(crc_input_data + 13, &color_type, 1);
    memcpy(crc_input_data + 14, zero, 3);

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
    int img_length = this->img_size * sizeof(int);
    int _img_width = this->img_width * sizeof(int);
    int uncompressed_data_length = img_length + this->img_height; // adding img_height to count filter bytes
    char type[] = "IDAT";
    size_t crc_input_data_size = 8 + FORMAT_HEADER_SIZE + uncompressed_data_length;// 8 is for the type and the adler32 checksum
    int chunk_data_length = this->big_endian(crc_input_data_size - 4);
    char *crc_input_data = new char[crc_input_data_size];
    char *format_header = this->get_format_header(uncompressed_data_length);

    memcpy(crc_input_data, type, 4);
    memcpy(crc_input_data + 4, format_header, FORMAT_HEADER_SIZE);

    delete format_header;

    for (size_t i = 0, j = FORMAT_HEADER_SIZE + 4; i < this->img_size; i += this->img_width) {
        // the filter byte added to the beginning of each scanline
        crc_input_data[j] = 0x0;
        j++;
        // rest of the scanline
        memcpy(crc_input_data + j, this->img_data + i, _img_width);
        j += _img_width;
    }

    // calculating the adler_32 for the uncompressed data
    char *adler_buffer = crc_input_data + FORMAT_HEADER_SIZE + 4;
    u_int32_t adler32_checksum = Graph::Png::big_endian(Graph::Png::adler32(reinterpret_cast<u_int8_t *>(adler_buffer), uncompressed_data_length, 1));

    memcpy(crc_input_data + crc_input_data_size - 4, &adler32_checksum, 4);

    // data length
    os.write(reinterpret_cast<char *>(&chunk_data_length), sizeof(int));

    // chunk type & format header & uncompressed data
    os.write(crc_input_data, crc_input_data_size);

    // crc
    unsigned int crc = this->cycle_redundancy_check(reinterpret_cast<unsigned char *>(crc_input_data), crc_input_data_size);
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

    // the original value is 0xae426082, i just want it to be represented in big endian.
    int crc = 0x826042ae;

    // write crc
    os.write(reinterpret_cast<char *>(&crc), sizeof(unsigned int));

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

u_int32_t Graph::Png::adler32(u_int8_t *buffer, size_t buffer_size, u_int32_t previous_key) {
    size_t buffer_iterator = 0;
    u_int32_t lower_word    = previous_key & 0xffff;
    u_int32_t upper_word    = (previous_key >> 16) & 0xffff;

    for (buffer_iterator = 0; buffer_iterator < buffer_size; buffer_iterator++) {
        lower_word += buffer[buffer_iterator];
        upper_word += lower_word;

        if((buffer_iterator != 0)
         && ((buffer_iterator % 0x15b0 == 0)
          ||  (buffer_iterator == buffer_size - 1)))
        {
            lower_word = lower_word % 0xfff1;
            upper_word = upper_word % 0xfff1;
        }
    }
    return ((upper_word << 16) | lower_word);
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
    char *ptr = reinterpret_cast<char *>(&b);

    ptr[0] = (a >> 24); // most significant byte
    ptr[1] = (a >> 16);
    ptr[2] = (a >> 8);
    ptr[3] = a; // least significant byte

    return (b);
}

void Graph::Png::displayData() const {
    std::cout << "IMG HEIGHT: " << this->img_height << ", IMG WIDTH: " << this->img_width << std::endl;

    std::cout << "IMG DATA: " << std::endl;  

    for (size_t i = 0; i < this->img_size; i++) {
        std::cout << (this->img_data[i] == (int)POINT_COLOR ? "P" : "N");
        std::cout << ((i + 1) % this->img_width == 0 ? "\n" : " ");
    }
}
