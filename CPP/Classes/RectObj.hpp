#ifndef RECTOBJ_HPP
#define RECTOBJ_HPP

#include <SFML/Graphics.hpp>
#include <random>

class RectObj {
private:
    float x, y;
    float width, height;
    sf::Color color;
    int speed;
    int rotation;

public:
    RectObj(int x, int y, int width, int height)
        : x(x), y(y), width(width), height(height), rotation(0) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> cor(0, 255);
        color = sf::Color(cor(gen), cor(gen), cor(gen));

        std::uniform_real_distribution<> speedDist(2, 6);
        speed = speedDist(gen);
    }

    void update() {
        x += 2 + speed;
        rotation++;
        if (rotation >= 360) rotation = 0;
    }

    float getX() const { return x; }
    float getY() const { return y; }
    float getWidth() const { return width; }
    float getHeight() const { return height; }
    int getRotation() const { return rotation; }
    sf::Color getColor() const { return color; }
};

#endif
