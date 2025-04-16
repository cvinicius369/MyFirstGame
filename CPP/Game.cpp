// Codigo teste para verificar a funcionalidade da lib SFML 3 
// Será testado tambem outros metodos para a conversão do jogo em java para cpp
#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>
#include "Classes/Game.hpp"
#include "Classes/Spawner.hpp"

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
