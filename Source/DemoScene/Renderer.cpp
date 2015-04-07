#include "Renderer.h"

Renderer* Renderer::_instance = 0;

Renderer::Renderer(void)
{
	_clearColour = 0x00000000;
}

Renderer::~Renderer(void)
{

}

Renderer* Renderer::GetInstance()
{
	if ( _instance == 0 )
		_instance = new Renderer();

	return _instance;
}
