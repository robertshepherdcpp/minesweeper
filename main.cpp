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
                        board.HandleMouseClicked(event);

                        if (board.HasGameFinished(window))
                        {
                            window.setSize(sf::Vector2u(1000, 1000));
                        }
                }
            }
            if (event.type == sf::Event::Resized)
            {
                if (!board.hundered_by_hundered)
                {
                    window.setSize(sf::Vector2u(150, 150));
                }
                else
                {
                    window.setSize(sf::Vector2u(1000, 1000));
                }
            }
        }

        window.clear();
        board.draw(window);
        window.display();
    }

    return 0;
}
