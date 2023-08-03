#include<random>
#include<algorithm>
#include<ranges>

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

    // second initialize all of the vectors
    for (auto x : std::ranges::views::iota(10))
    {
        std::vector<int> temporary_user{};
        std::vector<int> temporary_uncovered{};
        for (auto y : std::ranges::views::iota(10))
        {
            temporary_user.push_back(0);
            temporary_uncovered.push_back(1);
        }
        user_board.push_back(temporary_user);
        uncovered_board.push_back(temporary_uncovered);
    }

	// third get 8 random positions to put in the board which represent the bombs
    for (auto i : std::ranges::views::iota(8))
    {
        auto RandomX = RandomNumber();
        auto RandomY = RandomNumber();

        uncovered_board[RandomX][RandomY] = 3;
    }

    // fourth fill in the numbers for the grid, how many bombs are neighbouring the cell in the grid
    int total_bomb_count = 0;

    for (int i = 0; i < uncovered_board.size(); i++)
    {
        for (int j = 0; j < uncovered_board[i].size(); i++)
        {
            if ((j - 1) >= 0) { if (uncovered_board[i][j - 1] == 3) { total_bomb_count += 1; } }
            if ((j + 1) <= 9) { if (uncovered_board[i][j + 1] == 3) { total_bomb_count += 1; } }
            if ((i - 1) >= 0) { if (uncovered_board[i - 1][j] == 3) { total_bomb_count += 1; } }
            if ((i + 1) <= 9) { if (uncovered_board[i + 1][j] == 3) { total_bomb_count += 1; } }

            if ((j - 1) >= 0 && (i - 1) >= 0) { if (uncovered_board[i - 1][j - 1] == 3) { total_bomb_count += 1; } }
            if ((j + 1) <= 9 && (i + 1) <= 9) { if (uncovered_board[i + 1][j + 1] == 3) { total_bomb_count += 1; } }
            if ((i - 1) >= 0 && (j + 1) <= 9) { if (uncovered_board[i - 1][j + 1] == 3) { total_bomb_count += 1; } }
            if ((i + 1) <= 9 && (j - 1) >= 0) { if (uncovered_board[i + 1][j - 1] == 3) { total_bomb_count += 1; } }

            uncovered_board[i][j] = total_bomb_count + 4;
        }
    }
}

auto Board::draw(sf::RenderWindow& window) const noexcept -> void
{
    for (auto i : uncovered_board)
    {
        for (auto j : i)
        {
            if (j == 0) {}
            else if (j == 1)  { window.draw(covered_sprite); }
            else if (j == 2)  { window.draw(nothing_sprite); }
            else if (j == 3)  { window.draw(bomb_sprite); }
            else if (j == 4)  { window.draw(nothing_sprite); }
            else if (j == 5)  { window.draw(one_bomb_sprite); }
            else if (j == 6)  { window.draw(two_bomb_sprite); }
            else if (j == 7)  { window.draw(three_bomb_sprite); }
            else if (j == 8)  { window.draw(four_bomb_sprite); }
            else if (j == 9)  { window.draw(five_bomb_sprite); }
            else if (j == 10) { window.draw(six_bomb_sprite); }
            else if (j == 11) { window.draw(seven_bomb_sprite); }
            else if (j == 12) { window.draw(eight_bomb_sprite); }
        }
    }
}

auto Board::HasGameFinished() -> bool
{
    return amount_of_land_uncovered == 0;
}

auto Board::RandomNumber() -> int
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 9); // distribution in range [1, 10]

    return dist6(rng);
}
