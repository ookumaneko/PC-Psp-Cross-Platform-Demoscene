#include "Maths.h"
#include <stdlib.h>
#include "Vector3.h"

//-------------------Both Version----------------//

float Maths::RandFloat(float min, float max)
{
	return min + (max - min) * ( (float)rand()) / ((float)RAND_MAX );
}

void Maths::RandUnitVector(Vector3& out)
{
	out.X() = RandFloat( -1.0f, 1.0f );
	out.Y() = RandFloat( -1.0f, 1.0f );
	out.Z() = RandFloat( -1.0f, 1.0f );
}

#ifdef _PSP_VER

//-------------------PSP Version----------------//

#include <libgu.h>
#include <libvfpu.h>

float Maths::DegreeToRadian(float degree)
{
	return SCEGU_RAD( degree );
}

float Maths::RandFloat(float max)
{
	return sceVfpuRandFloat( max );
}

unsigned int Maths::RandColour(unsigned int max)
{
	int col = RandFloat( 0x00FFFFFF );
	return ( ( (0xc0 + (rand() % 0x40) ) << 16 ) | col );
}

int Maths::Abs(float val)
{
	return sceVfpuScalarAbs( val );
}

float Maths::Cos(float radian)
{
	return sceVfpuScalarCos( radian );
}

float Maths::Sin(float radian)
{
	return sceVfpuScalarSin( radian );
}

#else


//------------------PC Version---------------//
#include <D3dx9math.h>

float Maths::DegreeToRadian(float degree)
{
	return D3DXToRadian( degree );
}

float Maths::RandFloat(float max)
{
	return 0.0f + (max - 0.0f) * ( (float)rand()) / ((float)RAND_MAX );
}

unsigned int Maths::RandColour(unsigned int max)
{
	unsigned int col = RandFloat( max );
	return ( ( (0xc0 + (rand() % 0x40) ) << 2 ) | col );
}

int Maths::Abs(float val)
{
	return abs( val );
}

float Maths::Cos(float radian)
{
	return cosf( radian );
}

float Maths::Sin(float radian)
{
	return sinf( radian );
}

#endif