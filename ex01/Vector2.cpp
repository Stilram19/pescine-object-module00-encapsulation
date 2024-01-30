# include "Vector2.hpp"

Vector2::Vector2() : X(0), Y(0) {}

Vector2::Vector2(float X, float Y) {
    //! is std::isnan allowed
    if (std::isnan(X) || std::isnan(Y))
        throw std::runtime_error("Coordinates must be numbers");
    this->X = X;
    this->Y = Y;
}

float Vector2::getX() const {
    return this->X;
}

float Vector2::getY() const {
    return this->Y;
}

void Vector2::resetX(float X) {
    this->X = X;
}

void Vector2::resetY(float Y) {
    this->Y = Y;
}