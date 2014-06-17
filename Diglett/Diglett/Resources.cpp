#include "Resources.h"
#include <iostream>
#include "Constants.h"

//
//
// Static Constants
//
//
const std::string Resources::SEGOEUI_FONT_FILE = "Fonts/segoeui.ttf";
const std::string Resources::SHOP_TEXTURE_FILE = "Sprites/shop.png";
const std::string Resources::SHOP_BACKGROUND_TEXTURE_FILE = 
	    "Sprites/ShopBackground.png";

//
//
// Static Members
//
//
const Resources& Resources::getResources() {
    if( singleton == NULL ) {
		singleton = new Resources();
	}
	return *singleton;
}

Resources* Resources::singleton = NULL;

sf::Texture* Resources::makeSquareTexture( sf::Color color, int size ) {
    // Make the render area.
    sf::RenderTexture renderer;
    renderer.create( size, size );
    renderer.clear();
    // Draw the outline.
    sf::RectangleShape outline( sf::Vector2f( size, size ) );
    outline.setFillColor( sf::Color::Black );
    renderer.draw( outline );
    // Draw the filling colour over it.
    sf::RectangleShape fill( sf::Vector2f( size - 2, 
            size - 2 ) );
    fill.setFillColor( color );
    fill.move( 1.0f, 1.0f );
    renderer.draw( fill );
    // Make the texture.
    renderer.display();
    sf::Texture texture = renderer.getTexture();
    return new sf::Texture( texture );
}

sf::Texture* Resources::makeCircleTexture( sf::Color color ) {
    // Make the render area.
    sf::RenderTexture renderer;
    renderer.create( PIXELS_PER_TILE, PIXELS_PER_TILE );
    renderer.clear( sf::Color::Transparent );
    
    // Draw the filling colour over it.
    sf::CircleShape circle( PIXELS_PER_TILE / 2 );
    circle.setFillColor( color );
    renderer.draw( circle );
    // Make the texture.
    renderer.display();
    sf::Texture texture = renderer.getTexture();
    return new sf::Texture( texture );
}

sf::Texture* Resources::loadTexture( std::string filename ) {
	sf::Texture* texture = new sf::Texture();
    if ( !texture->loadFromFile( filename ) ) {
        std::cerr << "Failed to load texture: " << filename << "\n";
        exit(1);
    }
	return texture;
}

//
//
// Instance Members
//
//
Resources::Resources() {
	m_SegoeuiFont = new sf::Font();
    if ( !m_SegoeuiFont->loadFromFile( SEGOEUI_FONT_FILE ) ) {
        std::cerr << "Failed to load font: " << SEGOEUI_FONT_FILE << "\n";
        exit(1);
    }

	m_ShopTexture = loadTexture( SHOP_TEXTURE_FILE );
	m_ShopBackgroundTexture = loadTexture( SHOP_BACKGROUND_TEXTURE_FILE );

	m_AirTileTexture = 
		    makeSquareTexture( sf::Color( 156, 94, 0, 255 ), PIXELS_PER_TILE );
	m_SurfaceTileTexture = 
		    makeSquareTexture( sf::Color::Blue, PIXELS_PER_TILE );
	m_DirtTileTexture = 
		    makeSquareTexture( sf::Color( 126, 64, 0, 255 ), PIXELS_PER_TILE );
	m_GoldTileTexture = makeSquareTexture( 
		    sf::Color( 255, 215, 0, 255 ), PIXELS_PER_TILE );

	m_GoldItemTexture = makeSquareTexture( 
		    sf::Color( 255, 215, 0, 255 ), PIXELS_PER_ITEM_SPRITE );

	m_PlayerTexture = makeCircleTexture( sf::Color::Magenta );
	m_PlayerDeadTexture = makeCircleTexture( sf::Color::Red );
}

Resources::~Resources(void) {
	delete m_SegoeuiFont;
	delete m_ShopTexture;
	delete m_ShopBackgroundTexture;
	delete m_AirTileTexture;
	delete m_SurfaceTileTexture;
	delete m_DirtTileTexture;
	delete m_GoldTileTexture;
	delete m_GoldItemTexture;
	delete m_PlayerTexture;
	delete m_PlayerDeadTexture;
}

const sf::Font& Resources::getFont() const {
    return *m_SegoeuiFont;
}
const sf::Texture& Resources::getShopTexture() const {
    return *m_ShopTexture;
}
const sf::Texture& Resources::getShopBackgroundTexture() const {
    return *m_ShopBackgroundTexture;
}
const sf::Texture& Resources::getAirTileTexture() const {
    return *m_AirTileTexture;
}
const sf::Texture& Resources::getSurfaceTileTexture() const {
    return *m_SurfaceTileTexture;
}
const sf::Texture& Resources::getDirtTileTexture() const {
    return *m_DirtTileTexture;
}
const sf::Texture& Resources::getGoldTileTexture() const {
    return *m_GoldTileTexture;
}
const sf::Texture& Resources::getGoldItemTexture() const {
    return *m_GoldItemTexture;
}
const sf::Texture& Resources::getPlayerTexture() const {
    return *m_PlayerTexture;
}
const sf::Texture& Resources::getPlayerDeadTexture() const {
    return *m_PlayerDeadTexture;
}
