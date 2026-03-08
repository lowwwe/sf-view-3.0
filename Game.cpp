/// <summary>
/// author Pete Lowe May 2025
/// you need to change the above line or lose marks
/// </summary>


#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the texts
/// load and setup the images

/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ sf::Vector2u{800U, 600U}, 32U }, "Find Wally" },
	m_DELETEexitGame{false} //when true game will exit
{
	setupTexts(); // load font 
	setupSprites(); // load texture

}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	
	while (const std::optional newEvent = m_window.pollEvent())
	{
		if ( newEvent->is<sf::Event::Closed>()) // close window message 
		{
			m_DELETEexitGame = true;
		}
		if (newEvent->is<sf::Event::KeyPressed>()) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(const std::optional<sf::Event> t_event)
{
	const sf::Event::KeyPressed *newKeypress = t_event->getIf<sf::Event::KeyPressed>();
	if (sf::Keyboard::Key::Escape == newKeypress->code)
	{
		m_DELETEexitGame = true; 
	}
}

/// <summary>
/// Check if any keys are currently pressed
/// </summary>
void Game::checkKeyboardState()
{
	sf::Vector2f centre;
	sf::Vector2f viewFinderLocation;
	sf::Vector2f zoom;
	float shiftScale = 1.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		m_DELETEexitGame = true; 
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift))
	{
		shiftScale = 10.0f;
	}
	shiftScale *= m_view.getSize().x / 800.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
			centre = m_view.getCenter();
			centre.x -= 1.0f *shiftScale;
			m_view.setCenter(centre);
			viewFinderLocation = m_viewFinder.getPosition();
			viewFinderLocation.x -= 0.0577f * shiftScale;
			m_viewFinder.setPosition(viewFinderLocation);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		centre = m_view.getCenter();
		centre.x += 1.0f * shiftScale;
		m_view.setCenter(centre);
		viewFinderLocation = m_viewFinder.getPosition();
		viewFinderLocation.x += 0.0577f * shiftScale;
		m_viewFinder.setPosition(viewFinderLocation);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		centre = m_view.getCenter();
		centre.y -= 1.0f * shiftScale;
		m_view.setCenter(centre);
		viewFinderLocation = m_viewFinder.getPosition();
		viewFinderLocation.y -= 0.0633f * shiftScale;
		m_viewFinder.setPosition(viewFinderLocation);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		centre = m_view.getCenter();
		centre.y += 1.0f * shiftScale;
		m_view.setCenter(centre);
		viewFinderLocation = m_viewFinder.getPosition();
		viewFinderLocation.y += 0.0633f * shiftScale;
		m_viewFinder.setPosition(viewFinderLocation);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Add))
	{
		zoom = m_view.getSize();
		zoom *= 0.99f;
		m_view.setSize(zoom);
		zoom = m_viewFinder.getSize();
		zoom *= 0.99f;
		m_viewFinder.setSize(zoom);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Subtract))
	{
		zoom = m_view.getSize();
		zoom *= 1.01f;
		m_view.setSize(zoom);
		zoom = m_viewFinder.getSize();
		zoom *= 1.01f;
		m_viewFinder.setSize(zoom);
	
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
	{		
		m_view.setSize(sf::Vector2f{ 800.0f,480.0f });
		m_viewFinder.setSize(sf::Vector2f{ 46.1f,30.0f });
	}

}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	checkKeyboardState();
	if (m_DELETEexitGame)
	{
		m_window.close();
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(ULTRAMARINE);

	m_window.setView(m_view);
	m_window.draw(m_dublinSprite);
	m_window.draw(m_wallySprite);
	m_window.setView(m_window.getDefaultView());
	m_window.draw(m_instructions);
	m_window.draw(m_miniMapSprite);
	m_window.draw(m_viewFinder);
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupTexts()
{
	if (!m_jerseyFont.openFromFile("ASSETS\\FONTS\\Jersey20-Regular.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_instructions.setFont(m_jerseyFont);
	m_instructions.setString("Arrow Keys to move, + & - to zoom");
	m_instructions.setPosition(sf::Vector2f{ 60.0f, 520.0f });
	m_instructions.setCharacterSize(36U);
	m_instructions.setFillColor(sf::Color::White);
	
}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprites()
{
	if (!m_wallyTexture.loadFromFile("ASSETS\\IMAGES\\wally.png")) // 2872 x 1895
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}

	m_wallySprite.setTexture(m_wallyTexture, true);// to reset the dimensions of texture
	m_wallySprite.setPosition(sf::Vector2f{ 1752.0f, 533.0f });
	m_wallySprite.setScale(sf::Vector2f{ 0.02f,0.02f });
	m_viewFinder.setOutlineColor(sf::Color::Red);
	m_viewFinder.setOutlineThickness(2.0f);
	m_viewFinder.setFillColor(sf::Color::Transparent);
	m_viewFinder.setSize(sf::Vector2f{ 46.1f,30.0f });
	//m_viewFinder.setPosition(sf::Vector2f{664.0f , 525.0f });
	m_viewFinder.setPosition(sf::Vector2f{ 575.0f , 480.0f });
	if (!m_miniTexture.loadFromFile("ASSETS\\IMAGES\\minimap.jpg")) // 2872 x 1895
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}

	m_miniMapSprite.setTexture(m_miniTexture, true);// to reset the dimensions of texture
	m_miniMapSprite.setPosition(sf::Vector2f{ 575.0f, 480.0f });

	if (!m_dublinTexture.loadFromFile("ASSETS\\IMAGES\\city.jpg")) // 2872 x 1895
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}

	m_dublinSprite.setTexture(m_dublinTexture, true);// to reset the dimensions of texture
	m_dublinSprite.setPosition(sf::Vector2f{ 0.0f,  0.0f });
	//m_view.setCenter(sf::Vector2f{ CITY_WIDTH / 2.0f, CITY_HEIGHT / 2.0f -240.0f});
	m_view.setCenter(sf::Vector2f{ 400.0f, 240.0f });
	m_view.setSize(sf::Vector2f{800.0f, 480.0f}); // 80% of 600 Height
	m_view.setViewport(sf::FloatRect{ sf::Vector2f{0.0f,0.0f}, sf::Vector2f{1.0f,0.8f} }); // use top 80% of screen
}


