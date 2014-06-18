#pragma once
#ifndef RESOURCES_H
#define RESOURCES_H

#include <SFML/Graphics.hpp>

/* This is a singleton class containing textures and fonts used by the game.
*/

class Resources {
public:

	// Returns the singleton Resources object. If it doesn't exist, one is created.
	static const Resources& getResources();

    Resources();
    ~Resources();

	const sf::Font& getFont() const;
	const sf::Texture& getShopTexture() const;
	const sf::Texture& getShopBackgroundTexture() const;
	const sf::Texture& getAirTileTexture() const;
	const sf::Texture& getSurfaceTileTexture() const;
	const sf::Texture& getDirtTileTexture() const;
	const sf::Texture& getGoldTileTexture() const;
	const sf::Texture& getGoldItemTexture() const;
	const sf::Texture& getPlayerTexture() const;
	const sf::Texture& getPlayerDeadTexture() const;

private: 
	static const std::string SEGOEUI_FONT_FILE;
	static const std::string SHOP_TEXTURE_FILE;
	static const std::string SHOP_BACKGROUND_TEXTURE_FILE;

	static Resources* singleton;

    // Constructs a square sprite of the specified color, with sides of the 
    // given size, and with a black outline.
    static sf::Texture* makeSquareTexture( sf::Color color, int size );

    // Constructs a circular sprite of the specified colour.
    static sf::Texture* makeCircleTexture( sf::Color );

	// Loads a texture from a file, and exits if it fails.
	static sf::Texture* loadTexture( std::string filename );
    
	sf::Font* m_SegoeuiFont;

	sf::Texture* m_ShopTexture;
	sf::Texture* m_ShopBackgroundTexture;

	sf::Texture* m_AirTileTexture;
	sf::Texture* m_SurfaceTileTexture;
	sf::Texture* m_DirtTileTexture;
	sf::Texture* m_GoldTileTexture;

	sf::Texture* m_GoldItemTexture;

	sf::Texture* m_PlayerTexture;
	sf::Texture* m_PlayerDeadTexture;
};

#endif // RESOURCES_H
