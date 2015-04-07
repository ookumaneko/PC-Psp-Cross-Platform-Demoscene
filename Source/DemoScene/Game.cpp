#include "Game.h"
#include "Renderer.h"

Game* Game::_instance = 0;


//-------------Constructor and Destructor---------//


Game::Game(void)
{
	if ( _instance == 0 )
	{
		_instance = this;
	}
}

Game::~Game(void)
{
	Shutdown();
}



//------------------End of Constructors-----------//


Game* Game::GetInstance()
{
	if ( _instance == 0 )
		_instance = new Game();

	return _instance;
}