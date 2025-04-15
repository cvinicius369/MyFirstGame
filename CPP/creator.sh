echo "Compilando ..."
g++ Game.cpp -std=c++17 -I/opt/SFML/include -L/opt/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system -o game
echo "Executando"
LD_LIBRARY_PATH=/opt/SFML/lib ./game