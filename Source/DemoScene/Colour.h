#ifndef _COLOUR_H
#define _COLOUR_H
#include "basecolour.h"

class Colour : public BaseColour
{
	public:
		Colour(void);
		~Colour(void);

	// constant colout values
	public:
		static const unsigned int White;
		static const unsigned int Black;
		static const unsigned int Yellow;
		static const unsigned int Red;
		static const unsigned int Green;
		static const unsigned int CornFlowerBlue;

	public:
		static int SetFade(int col);
		static unsigned int GetFade			(int col, int a);
		static unsigned int GetRandColour	(unsigned int max);
};

#endif