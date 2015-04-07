#pragma once
#include "game.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "Vector4.h"

#if defined (_PSP_VER)
	#include <libgum.h>
#endif

class MyDemo : public Game
{
	// data structures
	protected:

		static const float GRAV;// = 0.0025f;
		static const int MAX_FINISH = 256;
		static const int MAX_EXPLOSION = 128;
		static const int MAX_SPARKS = 128;
		static const int MAX_ROCKETS = 25;
		
		static const float TOP;
		static const float LEFT;
		static const float RIGHT;

		struct GRAIN_DAT
		{
			Vector3			pos;
			Vector3			dpos;
			float			rot;
			float			scale;
			int				t;
			int				a;
			int				d;
			int				c;
			short			w;
		};

		struct Rocket
		{
			Vector3			pos;
			Vector3			start;
			float			speed;
			float			rot;
			float			scale;
			float			t;
			unsigned int	colour;
			short			w;
		};

		enum SceneType
		{
			Intro,
			MidSpherer,
			HighGround,
			DownToGround,
			BuildUp,
			End
		} currentScene;

		enum RocketState
		{
			SemiLine,
			Circle,
			Spin,
			NONE
		} rocketState;


	// constructor and destructor
	public:
		MyDemo(void);
		~MyDemo(void);

	// overridden framework methods
	public:
		int  Run		(void);
		void Update		(float delta);
		void Draw		(float delta);
		void Initialize	(void);
		void Shutdown	(void);

	// provate member fuunctions
	public:
		void init_ball(int i);
		void init_spark(int num, int i, Vector3& pos, int col);
		void init_rocket(int i, int col);

		void UpdateState(void);
		void UpdateScene(void);
		void move_rocket(int i);
		void makeExplosion(GRAIN_DAT *p, int num, short big, int col );
		int	 GetRandColour(void);
		void DrawScene();
		void DrawSphere(float r, int colour, int t);

	// members
	protected:
		Vector3			pos;
		Vector3			rot;
		GRAIN_DAT		balls[3];
		GRAIN_DAT		fire[3][ MAX_FINISH ];
		GRAIN_DAT		sparks[2][ MAX_SPARKS ];
		GRAIN_DAT		midSpherer;
		Vector3			sparkPos[2];
		Rocket			rocket[ MAX_ROCKETS ];

		Vector3			stPos;
		Vector3			airPos;
		Vector3			airRot;
		float			viewT;

		int				zInc, fin;
		int				num_of_fire[3], num_of_sparks[2]; 
		short			num_of_balls, num_of_starts;
		int				num_of_rockets, autoflag;
		short			isFire[3], isSpark, isBalls;
		int				frames;
};
