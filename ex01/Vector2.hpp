# include <iostream>
# include <vector>
# include <cmath>

struct Vector2 {
    private:
        float X;
        float Y;

    public:
        Vector2();
        Vector2(float X, float Y);

    // getters
    public:
        float   getX() const;
        float   getY() const;
        void    resetX(float X);
        void    resetY(float Y);
};
