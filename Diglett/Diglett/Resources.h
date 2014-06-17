#pragma once
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

private: 
	static const std::string SHOP_TEXTURE_FILE;
	static const std::string SEGOEUI_FONT_FILE;

	static Resources* singleton;
    
	sf::Font* m_SegoeuiFont;
	sf::Texture* m_ShopTexture;

};

