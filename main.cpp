#include <SFML/Graphics.hpp>

#include<iostream>

#include "Board.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(150, 150), "SFML works!");

    Board board;

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
                    if (!board.HasGameFinished())
                    {
                        board.HandleMouseClicked(event);
                    }
                    else
                    {
                        board.showAllNotBombs();
                        board.game_over = true;
                    }
                }
            }
            if (event.type == sf::Event::Resized)
            {
                window.setSize(sf::Vector2u(150, 150));
            }
        }

        window.clear();
        board.draw(window);
        window.display();
    }

    return 0;
}
