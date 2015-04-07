#ifndef _MATHS_H
#define _MATHS_H

class Vector3;

namespace Maths
{
	float DegreeToRadian(float degree);

	void		 RandUnitVector	(Vector3& out);
	float		 RandFloat		(float max);
	float		 RandFloat		(float min, float max);
	unsigned int RandColour		(unsigned int max);

	int	  Abs	(float val);
	float Cos	(float radian);
	float Sin	(float radian);
}

#endif