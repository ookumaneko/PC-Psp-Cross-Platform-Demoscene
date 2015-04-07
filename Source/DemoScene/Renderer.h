#ifndef _RENDERER_H
#define _RENDERER_H
#include "BaseRenderer.h"

class Vector3;
class Vector4;
class Matrix4;

class Renderer : public BaseRenderer
{
	// constructor and destrutor
	public:
		Renderer(void);
		~Renderer(void);

	// Accessor
	public:
		static Renderer* GetInstance(void);

	// Enums
	public:
		enum CullMode
		{
			Clock,
			CClock,
		};

	// Framework Methods
	public:
		void Initialize	(CullMode cull);
		void Shutdown	(void);
		void Draw		(float delta);

	// Render Methods
	public:
		void Clear	(void);
		void Begin	(void);
		void End	(void);

	// World Transform
	public:
		void BeginTransform	(void);
		void Translate		(const Vector3& trans);
		void Rotate			(const Vector3& rot);
		void RotateX		(float degree);
		void RotateY		(float degree);
		void RotateZ		(float degree);
		void RotateWorld	(const Vector3& rot);
		void Scale			(const Vector3& scale);
		void EndTransform	(void);

		void	SetTransform(const Matrix4& world);
		Matrix4 GetCurrentTransform(void);
	
	// setup methods
	public:
		void SetProjection	(float fov, float aspectRatio, float nearZ, float farZ);

	// Draw Shape
	public:
		void DrawSphere(unsigned int colour, int val);

	// members
	private:
		static Renderer*	_instance;
		unsigned int		_clearColour;
};

#endif