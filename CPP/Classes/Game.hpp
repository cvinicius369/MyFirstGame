#pragma once
#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>
#include "Spawner.hpp"

class Game {
public:
    static const int WIDTH = 640, HEIGHT = 480;
    static int contador;
    static int pontuacao;
    static int mx, my;
    static bool clicado;
    static bool gameOver;

    Spawner spawner;
    sf::RenderWindow window;

    Game() : window(sf::VideoMode(WIDTH, HEIGHT), "Meu jogo") {
        window.setFramerateLimit(60);
    }

    void update() {
        spawner.update();
        if (!gameOver) {
            if (contador <= 0) {
                contador = 100;
                gameOver = true;
            }
        }
    }

    void render() {
        window.clear(sf::Color::Black);

        if (!gameOver) {
            sf::RectangleShape barra(sf::Vector2f(contador * 3, 20));
            barra.setPosition(WIDTH / 2 - 100 - 70, 20);
            barra.setFillColor(sf::Color::Green);
            window.draw(barra);

            sf::RectangleShape contorno(sf::Vector2f(300, 20));
            contorno.setPosition(WIDTH / 2 - 100 - 70, 20);
            contorno.setFillColor(sf::Color::Transparent);
            contorno.setOutlineColor(sf::Color::White);
            contorno.setOutlineThickness(1);
            window.draw(contorno);

            spawner.render(window);
        } else {
            sf::Font font;
            if (!font.loadFromFile("Arial.ttf")) {
                std::cout << "Erro ao carregar a fonte" << std::endl;
            }

            sf::Text gameOverText("Game Over", font, 30);
            gameOverText.setPosition(WIDTH / 2 - 100, HEIGHT / 2 - 200);
            gameOverText.setFillColor(sf::Color::Red);
            window.draw(gameOverText);

            sf::Text score("Seu score: " + std::to_string(pontuacao), font, 30);
            score.setPosition(WIDTH / 2 - 120, HEIGHT / 2 - 150);
            score.setFillColor(sf::Color::Green);
            window.draw(score);

            sf::Text tryAgain(">> Press Enter to play again <<", font, 30);
            tryAgain.setPosition(WIDTH / 2 - 270, HEIGHT / 2 + 80);
            tryAgain.setFillColor(sf::Color::White);
            window.draw(tryAgain);
        }

        window.display();
    }

    void run() {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    clicado = true;
                    mx = event.mouseButton.x;
                    my = event.mouseButton.y;
                }

                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && gameOver) {
                    pontuacao = 0;
                    contador = 100;
                    gameOver = false;
                }
            }

            update();
            render();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
        }
    }
};
