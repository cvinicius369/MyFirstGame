// Codigo teste para verificar a funcionalidade da lib SFML 3 
// Será testado tambem outros metodos para a conversão do jogo em java para cpp
#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>

using namespace sf;
using namespace std;

class Game : public sf::Drawable{
    public:
        static const int WIDTH = 640, HEIGHT = 480;
        static int contador;
        static int pontuacao;
        static int mx, my;
        static bool clicado;
        static bool gameOver;

        Spawner spawner;
        RenderWindow window;

        Game() : window(VideoMode(WIDTH, HEIGHT), "Meu jogo"){
            window.setFramerateLimit(60);
        }
        void update(){
            spawner.update();
            if(!gameOver){
                if(contador <= 0){
                    contador = 100;
                    gameOver = true;
                }
            }
        }
        void render(){
            window.clear(Color::Black);
            if(gameOver){
                RectangleShape barra(Vector2f(contador * 3, 20));
                barra.setPosition(WIDTH / 2 - 100 - 70, 20);
                barra.setFillColor(Color::Green);
            }
        }
};

int Game::contador = 100;
int Game::pontuacao = 0;
int Game::mx = 0;
int Game::my = 0;
bool Game::clicado = false;
bool Game::gameOver = false;

int main() {
    RenderWindow window(VideoMode({800, 600}), "Canvas com SFML 3");

    CircleShape shape(100.f);
    shape.setFillColor(Color::Green);

    while (window.isOpen()) {
        auto event = window.pollEvent();

        if (event.has_value()) {
            if (event->getIf<Event::Closed>()) {
                window.close();
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
