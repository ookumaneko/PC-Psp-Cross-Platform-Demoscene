#ifndef _GAME_H
#define _GAME_H
#include "BaseGame.h"

class Renderer;

class Game : public BaseGame
{
	// constructor and destructor
	public:
		Game(void);
		virtual ~Game(void);

	// Accessor
	public:
		static Game* GetInstance(void);

	// framework methods
	public:
		virtual int	 Run		(void);
		virtual void Update		(float delta);
		virtual void Draw		(float delta);
		virtual void Initialize	(void);
		virtual void Shutdown	(void);

	// members
	protected:
		Renderer* _renderer;

	private:
		static Game* _instance;
};

#endif