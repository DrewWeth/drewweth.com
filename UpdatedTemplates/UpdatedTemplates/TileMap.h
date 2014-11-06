#include<SFML/Graphics.hpp>
#include<iostream>
#include<fstream>
#include<string>
#include<cctype>
#include<vector>

class tileMap
{
public:
	void mTileMap();
	sf::Texture tileTexture;
	std::vector<sf::Vector2i> tempMap;
	std::string tileLocation;
	sf::Sprite tiles;
	std::vector<std::vector<sf::Vector2i>> map;
};