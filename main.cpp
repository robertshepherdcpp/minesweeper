#include <SFML/Graphics.hpp>

#include<iostream>

#include "Board.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(150, 150), "SFML works!");
    sf::CircleShape shape(10.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(sf::Vector2f(110, 10));

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
                    auto mouse_pos = sf::Mouse::getPosition(window); // Mouse position relative to the window
                    auto translated_pos = window.mapPixelToCoords(mouse_pos); // Mouse position translated into world coordinates
                    if (shape.getGlobalBounds().contains(translated_pos)) // Rectangle-contains-point check
                    {
                        board.showAllNotBombs();
                    }
                    else
                    {
                        board.HandleMouseClicked(event);

                        if (board.HasGameFinished(window))
                        {
                            window.setSize(sf::Vector2u(1000, 1000));
                        }
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
        window.draw(shape);
        board.draw(window);
        window.display();
    }

    return 0;
}
