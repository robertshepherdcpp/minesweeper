#include <SFML/Graphics.hpp>

#include<iostream>

#include "Board.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(150, 150), "SFML works!");

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
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    board.HandleMouseClicked(event);
                }
            }
        }

        window.clear();
        board.draw(window);
        window.display();
    }

    return 0;
}
