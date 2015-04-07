#ifndef _BASE_COLOUR_H
#define _BASE_COLOUR_H

#if defined (_PSP_VER)
	#include <libgum.h>	
#else
	#include <d3d9.h>
	#include <d3dx9.h>
#endif

class BaseColour
{
	// constructor and destrutor
	protected:
		BaseColour(void) {}
	public:
		~BaseColour(void) {}

	//platform specific members
	protected:
	
	#if defined (_PSP_VER)

	#else

	#endif
};

#endif