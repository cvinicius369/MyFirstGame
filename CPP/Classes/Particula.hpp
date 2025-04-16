#ifndef PARTICULA_HPP
#define PARTICULA_HPP

#include <SFML/Graphics.hpp>
#include <random>

class Particula : public sf::RectangleShape {
public:
    sf::Color color;
    int speed = 8;
    int rotation = 0;
    int timer = 0;
    double xa, ya;
    double dx, dy;

    Particula(int x, int y, int width, int height, sf::Color color) {
        xa = x;
        ya = y;
        this->color = color;
        setSize(sf::Vector2f(width, height));
        setPosition(static_cast<float>(x), static_cast<float>(y));
        setFillColor(color);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<> dist(0.0, 1.0);
        dx = dist(gen);
        dy = dist(gen);
    }

    void update() {
        xa += dx * speed;
        ya += dy * speed;
        setPosition(static_cast<float>(xa), static_cast<float>(ya));
        timer++;
    }

    void render(sf::RenderWindow& window) {
        window.draw(*this);
    }
};

#endif
