#pragma once

#include<vector>

#include<SFML/Graphics.hpp>

struct Board
{
	Board();

	auto HandleMouseClicked(sf::Event& e) -> void;

	auto draw(sf::RenderWindow& window) const noexcept -> void;

	auto HasGameFinished(sf::RenderWindow& window) -> bool;
	auto RandomNumber() -> int;

	auto blow_up_all_bombs() -> void;
	auto showAllNotBombs() -> void;

	std::vector<std::vector<int>> uncovered_board{};
	std::vector<std::vector<int>> user_board{};
	std::vector<float> sprite_positions_x{};
	std::vector<float> sprite_positions_y{};

	sf::Texture bomb_texture; sf::Sprite bomb_sprite;
	sf::Texture nothing_texture; sf::Sprite nothing_sprite;
	sf::Texture covered_texture; sf::Sprite covered_sprite;
	sf::Texture one_bomb_texture; sf::Sprite one_bomb_sprite;
	sf::Texture two_bomb_texture; sf::Sprite two_bomb_sprite;
	sf::Texture three_bomb_texture; sf::Sprite three_bomb_sprite;
	sf::Texture four_bomb_texture; sf::Sprite four_bomb_sprite;
	sf::Texture five_bomb_texture; sf::Sprite five_bomb_sprite;
	sf::Texture six_bomb_texture; sf::Sprite six_bomb_sprite;
	sf::Texture seven_bomb_texture; sf::Sprite seven_bomb_sprite;
	sf::Texture eight_bomb_texture; sf::Sprite eight_bomb_sprite;

	int amount_of_land_uncovered = 0;
	bool game_over = false;
	bool hundered_by_hundered = false;
};