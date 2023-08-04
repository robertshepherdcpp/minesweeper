#include<random>
#include<algorithm>
#include<ranges>
#include<type_traits>
#include<iostream>

#include "Board.h"

// covered_sprite = 0
// nothing_sprite = 1
// bomb_sprite = 3

Board::Board()
{
    // first initialize the sprites and textures
    bomb_texture.loadFromFile("bomb.png");
    bomb_sprite.setTexture(bomb_texture);

    nothing_texture.loadFromFile("nothing.png");
    nothing_sprite.setTexture(nothing_texture);

    covered_texture.loadFromFile("covered.png");
    covered_sprite.setTexture(covered_texture);

    one_bomb_texture.loadFromFile("one_bomb_sprite.png");
    one_bomb_sprite.setTexture(one_bomb_texture);

    two_bomb_texture.loadFromFile("two_bomb_sprite.png");
    two_bomb_sprite.setTexture(two_bomb_texture);

    three_bomb_texture.loadFromFile("three_bomb_sprite.png");
    three_bomb_sprite.setTexture(three_bomb_texture);

    four_bomb_texture.loadFromFile("four_bomb_sprite.png");
    four_bomb_sprite.setTexture(four_bomb_texture);

    five_bomb_texture.loadFromFile("five_bomb_sprite.png");
    five_bomb_sprite.setTexture(five_bomb_texture);

    six_bomb_texture.loadFromFile("six_bomb_sprite.png");
    six_bomb_sprite.setTexture(six_bomb_texture);

    seven_bomb_texture.loadFromFile("seven_bomb_sprite.png");
    seven_bomb_sprite.setTexture(seven_bomb_texture);

    eight_bomb_texture.loadFromFile("eight_bomb_sprite.png");
    eight_bomb_sprite.setTexture(eight_bomb_texture);

    std::cout << "finished setting up the sprites.\n";

    // second initialize all of the vectors
    for (int x = 0; x < 10; x++)
    {
        std::vector<int> temporary_user{};
        std::vector<int> temporary_uncovered{};
        for (int y = 0; y < 10; y++)
        {
            temporary_user.push_back(0);
            temporary_uncovered.push_back(1);
        }
        user_board.push_back(temporary_user);
        uncovered_board.push_back(temporary_uncovered);
    }

    std::cout << "finished initializing the vectors\n";

	// third get 10 random positions to put in the board which represent the bombs
    for (int i = 0; i < 11; i++)
    {
        auto RandomX = RandomNumber();
        auto RandomY = RandomNumber();

        uncovered_board[RandomX][RandomY] = 3;
    }

    std::cout << "finished putting the bombs in the uncovered_board vector.\n";

    // fourth fill in the numbers for the grid, how many bombs are neighbouring the cell in the grid
    int total_bomb_count = 0;

    for (int i = 0; i < uncovered_board.size(); i++)
    {
        std::cout << "\n" << i << "\n\t";
        for (int j = 0; j < uncovered_board[i].size(); j++)
        {
            std::cout << j << " ";
            if ((j - 1) >= 0) { if (uncovered_board[i][j - 1] == 3) { total_bomb_count += 1; } }
            if ((j + 1) <= 9) { if (uncovered_board[i][j + 1] == 3) { total_bomb_count += 1; } }
            if ((i - 1) >= 0) { if (uncovered_board[i - 1][j] == 3) { total_bomb_count += 1; } }
            if ((i + 1) <= 9) { if (uncovered_board[i + 1][j] == 3) { total_bomb_count += 1; } }

            if (((j - 1) >= 0) && ((i - 1) >= 0)) { if (uncovered_board[i - 1][j - 1] == 3) { total_bomb_count += 1; } }
            if (((j + 1) <= 9) && ((i + 1) <= 9)) { if (uncovered_board[i + 1][j + 1] == 3) { total_bomb_count += 1; } }
            if (((i - 1) >= 0) && ((j + 1) <= 9)) { if (uncovered_board[i - 1][j + 1] == 3) { total_bomb_count += 1; } }
            if (((i + 1) <= 9) && ((j - 1) >= 0)) { if (uncovered_board[i + 1][j - 1] == 3) { total_bomb_count += 1; } }
            if (uncovered_board[i][j] != 3)
            {
                uncovered_board[i][j] = total_bomb_count + 4;
            }
            total_bomb_count = 0;
        }
        total_bomb_count = 0;
    }

    std::cout << "finished filling the numbers in the grid.\n";

    // fifth, we uncover some blocks in the user_board, so that they can start somewhere.

    for (int i = 0; i < 6; i++)
    {
        auto RandomX = RandomNumber();
        auto RandomY = RandomNumber();

        if (uncovered_board[RandomX][RandomY] != 3)
        {
            user_board[RandomX][RandomY] = uncovered_board[RandomX][RandomY];
        }
        else
        {
            i -= 1;
        }
    }

    std::cout << "finished uncovering 5 random blocks in the user_board.\n";
}

auto Board::HandleMouseClicked(sf::Event& e) -> void
{
    if (!game_over)
    {
        auto positionOfMouseX = e.mouseButton.x;
        auto positionOfMouseY = e.mouseButton.y;

        int vectorPositionJ = ((positionOfMouseX - (positionOfMouseX % 10)) / 10);
        int vectorPositionI = ((positionOfMouseY - (positionOfMouseY % 10)) / 10);

        user_board[vectorPositionI][vectorPositionJ] = uncovered_board[vectorPositionI][vectorPositionJ];

        if (uncovered_board[vectorPositionI][vectorPositionJ] == 3)
        {
            game_over = true;
            blow_up_all_bombs();
        }

        amount_of_land_uncovered += 1;
    }
}

auto Board::draw(sf::RenderWindow& window) const noexcept -> void
{
    //int current_x = 0;
    //int current_y = 0;
    //for (int i = 0; i < uncovered_board.size(); i++)
    //{
    //    for (int j = 0; j < uncovered_board[i].size(); i++)
    //    {
    //        sprite_positions_x.push_back(current_x);
    //        sprite_positions_y.push_back(current_y);

    //        current_x += 10;
    //    }

    //    current_y += 10;
    //    current_x = 0;
    //}

    float current_x = 0.f;
    float current_y = 0.f;

    for (int i = 0; i < user_board.size(); i++)
    {
        for (int j = 0; j < user_board[i].size(); j++)
        {
            if (user_board[i][j] == 100) {}
            else if (user_board[i][j] == 0) { sf::Sprite copy_of_sprite = covered_sprite;  copy_of_sprite.setPosition(current_x, current_y); window.draw(copy_of_sprite); }
            else if (user_board[i][j] == 1)  { sf::Sprite copy_of_sprite = nothing_sprite;  copy_of_sprite.setPosition(current_x, current_y); window.draw(copy_of_sprite); }
            else if (user_board[i][j] == 3)  { sf::Sprite copy_of_sprite = bomb_sprite;  copy_of_sprite.setPosition(current_x, current_y); window.draw(copy_of_sprite); }
            else if (user_board[i][j] == 4)  { sf::Sprite copy_of_sprite = nothing_sprite;  copy_of_sprite.setPosition(current_x, current_y); window.draw(copy_of_sprite); }
            else if (user_board[i][j] == 5)  { sf::Sprite copy_of_sprite = one_bomb_sprite;  copy_of_sprite.setPosition(current_x, current_y); window.draw(copy_of_sprite); }
            else if (user_board[i][j] == 6)  { sf::Sprite copy_of_sprite = two_bomb_sprite;  copy_of_sprite.setPosition(current_x, current_y); window.draw(copy_of_sprite); }
            else if (user_board[i][j] == 7)  { sf::Sprite copy_of_sprite = three_bomb_sprite;  copy_of_sprite.setPosition(current_x, current_y); window.draw(copy_of_sprite); }
            else if (user_board[i][j] == 8)  { sf::Sprite copy_of_sprite = four_bomb_sprite;  copy_of_sprite.setPosition(current_x, current_y); window.draw(copy_of_sprite); }
            else if (user_board[i][j] == 9)  { sf::Sprite copy_of_sprite = five_bomb_sprite;  copy_of_sprite.setPosition(current_x, current_y); window.draw(copy_of_sprite); }
            else if (user_board[i][j] == 10) { sf::Sprite copy_of_sprite = six_bomb_sprite;  copy_of_sprite.setPosition(current_x, current_y); window.draw(copy_of_sprite); }
            else if (user_board[i][j] == 11) { sf::Sprite copy_of_sprite = seven_bomb_sprite;  copy_of_sprite.setPosition(current_x, current_y); window.draw(copy_of_sprite); }
            else if (user_board[i][j] == 12) { sf::Sprite copy_of_sprite = eight_bomb_sprite;  copy_of_sprite.setPosition(current_x, current_y); window.draw(copy_of_sprite); }

            current_x += 10.f;
        }
        current_x = 0.f;
        current_y += 10.f;
    }
}

auto Board::HasGameFinished() -> bool
{
    return amount_of_land_uncovered == 100;
}

auto Board::RandomNumber() -> int
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 8); // distribution in range [1, 10]

    return dist6(rng);
}

auto Board::blow_up_all_bombs() -> void
{
    for (int i = 0; i < user_board.size(); i++)
    {
        for (int j = 0; j < user_board[i].size(); j++)
        {
            if (uncovered_board[i][j] == 3)
            {
                user_board[i][j] = uncovered_board[i][j];
            }
        }
    }
}