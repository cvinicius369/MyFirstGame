// Codigo teste para verificar a funcionalidade da lib SFML 3 
// Será testado tambem outros metodos para a conversão do jogo em java para cpp
#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>

using namespace sf;
using namespace std;

class Game : public sf::Drawable{   // herança de SFML::Drawable semelhante ao canvas
    public:
        static const int WIDTH = 640, HEIGHT = 480;
        static int contador;
        static int pontuacao;
        static int mx, my;
        static bool clicado;
        static bool gameOver;

        Spawner spawner;
        RenderWindow window;

        Game() : window(VideoMode(WIDTH, HEIGHT), "Meu jogo"){ // COnstrutor da janela
            window.setFramerateLimit(60);                      // configuração de frames
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
            if(!gameOver){

                // Criação de retangulo
                RectangleShape barra(Vector2f(contador * 3, 20));
                barra.setPosition(WIDTH / 2 - 100 - 70, 20);
                barra.setFillColor(Color::Green);
                window.draw(barra);

                RectangleShape contorno(Vector2f(300, 20));
                contorno.setPosition(WIDTH / 2 - 100 - 70, 20);
                contorno.setFillColor(Color::Transparent);
                contorno.setOutlineColor(Color::White);
                contorno.setOutlineThickness(1);
                window.draw(contorno);

                spawner.render(window);
            } else {
                Font font;
                if(!font.loadFromFile("Arial.ttf")){ cout << "Erro ao carregar a fonte" << endl; }

                // Configuraçao da frase "Game Over"
                Text gameOverText("Game Over", font, 30);
                gameOverText.setPosition(WIDTH / 2, HEIGHT / 2 - 200);
                gameOverText.setFillColor(Color::Red);
                window.draw(gameOverText);

                Text score("Seu score: " + to_string(pontuacao), font, 30);
                score.setPosition(WIDTH / 2 - 120, HEIGHT / 2 - 150);
                score.setFillColor(Color::Green);
                window.draw(score);

                Text tryAgain(">> Press Enter to play again <<", font, 30);
                tryAgain.setPosition(WIDTH / 2 - 270, HEIGHT / 2 + 80);
                tryAgain.setFillColor(Color::White);
                window.draw(tryAgain);
            }
            window.display();
        }

        void run(){
            while (window.isOpen())
            {
                Event event;
                while (window.pollEvent(event))
                {
                    if(event.type == Event::Closed){ window.close(); }
                    if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left){
                        clicado == true;
                        mx = event.mouseButton.x;
                        my = event.mouseButton.y;
                    }
                    if(event.type == Event::KeyPressed && event.key.code == Keyboard::Enter && gameOver){
                        pontuacao = 0;
                        contador = 100;
                        gameOver = false;
                    }
                }
                update(); render();
                this_thread::sleep_for(chrono::milliseconds(1000/60));   // limnitador de frames (60FPS)
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
    Game game;
    game.run();
    return 0;
}
