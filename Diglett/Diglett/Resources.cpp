#include "Resources.h"
#include <iostream>

const std::string Resources::SHOP_TEXTURE_FILE = "Sprites/shop.png";
const std::string Resources::SEGOEUI_FONT_FILE = "Fonts/segoeui.ttf";

const Resources& Resources::getResources() {
    if( singleton == NULL ) {
		singleton = new Resources();
	}
	return *singleton;
}

Resources* Resources::singleton = NULL;

Resources::Resources() {
	m_SegoeuiFont = new sf::Font();
    if ( !m_SegoeuiFont->loadFromFile( SEGOEUI_FONT_FILE ) ) {
        std::cerr << "Failed to load font: " << SEGOEUI_FONT_FILE << "\n";
        exit(1);
    }
	m_ShopTexture = new sf::Texture();
    if ( !m_ShopTexture->loadFromFile( SHOP_TEXTURE_FILE ) ) {
        std::cerr << "Failed to load file: " << SHOP_TEXTURE_FILE << "\n";
        exit(1);
    }
}

Resources::~Resources(void) {
	delete m_SegoeuiFont;
	delete m_ShopTexture;
}

const sf::Font& Resources::getFont() const {
    return *m_SegoeuiFont;
}

const sf::Texture& Resources::getShopTexture() const {
    return *m_ShopTexture;
}
