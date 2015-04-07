#if !defined(_PSP_VER)

#include "Colour.h"
#include "Maths.h"

const unsigned int Colour::White	= 0xffffffff;
const unsigned int Colour::Black	= 0xff000000;
const unsigned int Colour::Red		= 0xffff0000;
const unsigned int Colour::Green	= 0xff00ff00;
const unsigned int Colour::Yellow	= 0xffffff00;
const unsigned int Colour::CornFlowerBlue = 0xff6495ED;

Colour::Colour(void)
{
}

Colour::~Colour(void)
{
}

int Colour::SetFade(int col)
{
	//col = ( (0xc0 + (rand() % 0x40) ) << 2 ) | col;
	return ( col - 0xff000000 );//( (0xc0 + (rand() % 0x40) ) << 2 ) | col );
}

unsigned int Colour::GetFade(int col, int a)
{
	return 0;
}

unsigned int Colour::GetRandColour(unsigned int max)
{
	return 0;
}

#endif