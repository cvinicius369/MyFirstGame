#ifndef SPAWNER_HPP
#define SPAWNER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <random>
#include <algorithm>
#include "RectObj.hpp"
#include "Particula.hpp"
#include "Game.hpp"

class Spawner {
public:
    int timer = 0;
    std::vector<std::shared_ptr<RectObj>> rectangles;
    std::vector<std::shared_ptr<Particula>> particulas;

    std::random_device numberRandom;
    std::mt19937 gen{numberRandom()};
    std::uniform_int_distribution<> dist{40, 480};

    void update() {
        timer++;
        if (timer % 60 == 0) {
            rectangles.push_back(std::make_shared<RectObj>(0, dist(gen), 40, 40));
        }

        for (size_t i = 0; i < rectangles.size(); ++i) {
            auto current = rectangles[i];
            current->update();

            if (current->getX() > Game::WIDTH) {
                rectangles.erase(rectangles.begin() + i);
                Game::contador -= 2;
                --i;
                continue;
            }

            if (Game::clicado &&
                Game::mx > current->getX() && Game::mx < current->getX() + current->getWidth() &&
                Game::my > current->getY() && Game::my < current->getY() + current->getHeight()) {
                rectangles.erase(rectangles.begin() + i);
                Game::pontuacao++;
                Game::clicado = false;

                for (int n = 0; n < 50; ++n) {
                    particulas.push_back(std::make_shared<Particula>(current->getX(), current->getY(), 8, 8, current->getColor()));
                }
                --i;
            }
        }

        for (size_t i = 0; i < particulas.size(); ++i) {
            particulas[i]->update();
            if (particulas[i]->timer >= 60) {
                particulas.erase(particulas.begin() + i);
                --i;
            }
        }
    }

    void render(sf::RenderWindow& window) {
        for (auto& current : rectangles) {
            sf::RectangleShape rect(sf::Vector2f(current->getWidth(), current->getHeight()));
            rect.setPosition(current->getX(), current->getY());
            rect.setFillColor(current->getColor());
            rect.setOrigin(current->getWidth() / 2, current->getHeight() / 2);
            rect.setRotation(current->getRotation());
            window.draw(rect);
        }

        for (auto& p : particulas) {
            p->render(window);
        }
    }
};

#endif
