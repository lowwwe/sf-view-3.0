/// <summary>
/// author Pete Lowe May 2025
/// you need to change the above line or lose marks
/// Also don't have any member properties called Delete...
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
#pragma warning( push )
#pragma warning( disable : 4275 )
// ignore this warning
// C:\SFML - 3.0.0\include\SFML\System\Exception.hpp(41, 47) : 
// warning C4275 : non dll - interface class 'std::runtime_error' used as base for dll - interface class 'sf::Exception'

/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the #endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


const sf::Color ULTRAMARINE{ 5, 55,242,255 }; // const colour
const float CITY_WIDTH = 3872.0f;
const float CITY_HEIGHT = 1895.0f;



class Game
{
public:
	Game();
	~Game();
	void run();

private:

	void processEvents();
	void processKeys(const std::optional<sf::Event> t_event);
	void checkKeyboardState();
	void update();
	void render();
	
	void setupTexts();
	void setupSprites();
	void panX(float t_mapScale, float t_viewScale);
	void panY(float t_mapScale, float t_viewScale);
	void zoom(float t_scale);
	void zoomReset();


	
	sf::RenderWindow m_window; // main SFML window
	sf::Font m_jerseyFont;// font used by message
	
	sf::Text m_instructions{ m_jerseyFont }; // text used for message on screen
	sf::Texture m_dublinTexture;//  texture used for sfml logo
	sf::Sprite m_dublinSprite{ m_dublinTexture }; // sprite used for sfml logo
	sf::Texture m_miniTexture; // texture for minimap
	sf::Sprite m_miniMapSprite{ m_miniTexture };// sprite for miniMap
	
	sf::Texture m_wallyTexture; // texture for minimap
	sf::Sprite m_wallySprite{ m_wallyTexture };// sprite for miniMap

	sf::View m_view; // view used to show part of map
	sf::RectangleShape m_viewFinder;// viewfinder rectangle
	float m_zoomScale = 1.0f; // ratio for photo to screen
	bool m_DELETEexitGame; // control exiting game

};

#pragma warning( pop ) 
#endif // !GAME_HPP

