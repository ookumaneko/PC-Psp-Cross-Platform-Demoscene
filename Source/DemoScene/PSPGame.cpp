#if defined (_PSP_VER)

#include "Game.h"
#include "Renderer.h"

BaseGame::BaseGame()
{

}

//-------------Start of Frawework Methods---------//

int Game::Run()
{
	Initialize();
	while ( 1 ) 
	{
		Update( 0.0f );
		Draw( 0.0f );
	}

	Shutdown();
	return 0;
}

void Game::Initialize()
{
	_renderer = Renderer::GetInstance();
	//_renderer->Initialize();
}

void Game::Shutdown()
{
	_renderer->Shutdown();
	delete _renderer;
	_renderer = 0;
}

void Game::Update(float delta)
{

}

void Game::Draw(float delta)
{

}

//---------------End of Frawework Methods---------//


#endif