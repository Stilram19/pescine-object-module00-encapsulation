# include <iostream>

class HelpException : public std::runtime_error {
    public:
        HelpException(const std::string &message) : std::runtime_error(message) {}
};
