#include <SFML/Graphics.hpp>

#include<iostream>

#include "Board.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");

    Board board;

    for (auto i : board.uncovered_board)
    {
        for (auto j : i)
        {
            std::cout << j << " ";
        }
        std::cout << "\n";
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        board.draw(window);
        window.display();
    }

    return 0;
}
