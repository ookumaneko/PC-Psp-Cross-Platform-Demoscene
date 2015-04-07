#include "MyDemo.h"
#include "Maths.h"
#include "Renderer.h"
#include <stdlib.h>
#include "Colour.h"

const float MyDemo::GRAV = 0.0025f;
const float MyDemo::TOP = 10.0f;
const float MyDemo::LEFT = -6.0f;
const float MyDemo::RIGHT = 6.0f;

//-----------------Csontructor and Destructor-------------//


MyDemo::MyDemo(void)
{

}

MyDemo::~MyDemo(void)
{

}

//----------------End of constructors-------------//

//---------------Start of Framework Mthods-------------//

int MyDemo::Run()
{
	return Game::Run();
}

void MyDemo::Initialize()
{
	srand(0);
	Game::Initialize();
	_renderer->Initialize( Renderer::Clock );

	//initialize renderer
	float w = 480.0f;
	float h = 272.0f;
	_renderer->SetProjection( 45.0f, w / h, 0.1f, 100.0f ); 

	fin = 0;
	viewT = 0;
	this->zInc= 0;
	isBalls = 0;
	frames = 0;
	isSpark = 0;

	num_of_rockets = MAX_ROCKETS;
	num_of_balls = 3;
	num_of_starts = 2;

	this->pos.X() =  0.0f;
	this->pos.Y() =  -4.0f;
	this->pos.Z() =  -20.0f;
	rot.Zero();
	
	stPos = this->pos;
	airPos.X() = 0;
	airPos.Y() = -9.25f;
	airPos.Z() = -13.5f;
	airRot.X() = 13;
	airRot.Y() = 0;
	airRot.Z() = 0;

	//intiialize sparks
	sparkPos[0].X() = -3;
	sparkPos[0].Y() = 0;
	sparkPos[0].Z() = 5;
	sparkPos[1].X() = 3;
	sparkPos[1].Y() = 0;
	sparkPos[1].Z() = 5;

	//initialize mid spherer
	midSpherer.pos.X() = 0;
	midSpherer.pos.Y() = TOP;
	midSpherer.pos.Z() = 0;

	currentScene = Intro;
	rocketState = NONE;
}

void MyDemo::Shutdown()
{
	Game::Shutdown();
}

void MyDemo::Update(float delta)
{
	frames++;
	this->UpdateState();
	this->UpdateScene();
	Game::Update( delta );
}

void MyDemo::Draw(float delta)
{
	_renderer->Begin();
	_renderer->Clear();

	_renderer->BeginTransform();

	_renderer->Translate( pos );
	rot.X() = 0;
	_renderer->RotateWorld( rot );
	//_renderer->RotateX( rot.X() );
	//_renderer->RotateY( rot.Y() );

	this->DrawScene();

	_renderer->EndTransform();

	_renderer->End();
	Game::Draw( delta );
}

//--------------End of Framework Mthods---------------//


//-------------Start of Application Mthods------------//


void MyDemo::DrawScene()
{
	GRAIN_DAT	*p;
	int			i, j, c;

	//draw balls
	if ( isBalls == 1 )
	{
		for ( i = 0; i < num_of_balls; i++) 
		{
			p = &balls[i];
			_renderer->BeginTransform();

			Matrix4 m = _renderer->GetCurrentTransform();
			
			m.Translate( p->pos.X(), p->pos.Y(), p->pos.Z() );
			_renderer->SetTransform( m );

			DrawSphere( p->scale, p->c, p->t );

			_renderer->EndTransform();
		}
	}

	p = 0;
	//exploded flames
	for ( j = 0; j < num_of_balls; ++j )
	{
		if ( isFire[j] == 0 )
		{
			continue;
		}

		for ( i = 0; i < num_of_fire[j]; ++i ) 
		{
			p = &fire[j][i];

			_renderer->BeginTransform();
			_renderer->Translate( p->pos );

			c = p->c |( p->a << 24 );
			if ( p->a > 0 )
				DrawSphere( p->scale, c, p->t );

			_renderer->EndTransform();
		}
	}

	// draw sparks
	for ( i = 0; i < num_of_starts; ++i )
	{
		if ( isSpark == 0 )
			continue;

		for ( j = 0; j < num_of_sparks[i]; ++j )
		{
			p = &sparks[i][j];

			if ( p->w > 0 ) 
			{
				continue;
			}

			_renderer->BeginTransform();
			_renderer->Translate( p->pos );

			DrawSphere( p->scale, p->c, p->t );

			_renderer->EndTransform();
		}
	}

	//draw rockets
	if ( rocketState != NONE )
	{
		Rocket* r;
		for ( i = 0; i < num_of_rockets; ++i )
		{
			r = &rocket[i];
			_renderer->BeginTransform();
			_renderer->Translate( r->pos );
			
			DrawSphere( r->scale, r->colour, 1 );

			_renderer->EndTransform();
		}
	}

	//draw mid spherer
	if ( fin == 0 )
	{
		_renderer->Translate( midSpherer.pos );
		DrawSphere( midSpherer.scale, midSpherer.c, 1 );
		_renderer->EndTransform();
	}
}

void MyDemo::init_ball(int i)
{
	GRAIN_DAT	*p;
	p = &balls[i];

	p->pos.Y() =  0.0f;
	//set starting positions
	if ( i == 0 )
	{
		//left
		p->pos.X() = -5;
		p->pos.Z() = -5;	
	}
	else if ( i == 1 )
	{
		//middle
		p->pos.X() = 0;
		p->pos.Z() = 0;	
	}
	else
	{
		//right
		p->pos.X() = 5;
		p->pos.Z() = -5;
	}

	p->dpos.X() = 0;
	p->dpos.Y() = ( 0.024f * ( ( rand() % 10 ) + 7 ) );
	p->dpos.Z() = 0;
	p->scale = 0.1f;
	p->t = 0;
	p->c = Colour::White;
	p->w = Maths::Abs( Maths::RandFloat(100) );
}

void MyDemo::init_rocket(int i, int col)
{
	Rocket* r = &rocket[i];
	float z = 0;
	float x = LEFT;
	float spacing = 2;
	float tz = MAX_ROCKETS * 0.5f;
	float startZ = -tz; 
	
	if ( rocketState == Circle )
	{
		float radius = 12;
		float count = (float)( (float)360 / (float)num_of_rockets );
		float a = Maths::DegreeToRadian( i * count );
		
		x = radius * Maths::Cos( a );
		z = radius * Maths::Sin( a );	
		r->w = 0;
	}
	else
	{
		if ( i >= tz ) //MAX_ROCKETS * 0.5f )
			x = RIGHT;

		if ( x == LEFT )
			z = startZ + (i * spacing);
		else
			z = startZ + ( (i - tz) * spacing );//MAX_ROCKETS * 0.5f) * spacing); 

		r->w = MAX_ROCKETS - i;
	}

	if ( rocketState == SemiLine )
		r->w = 0;

	r->speed = 0.01f;
	r->pos.X() = x;
	r->pos.Y() = 0.0f;
	r->pos.Z() = z;
	r->start = r->pos;
	r->scale = 0.075f;
	r->t = 0;
	r->colour = col;
}

void MyDemo::init_spark(int num, int i, Vector3 &pos, int col)
{
	GRAIN_DAT	*p;
	p = &sparks[num][i];
	float r = Maths::RandFloat(360);

	p->pos = pos;
	p->dpos.X() = Maths::Cos(r) * ( 0.005f * ( Maths::RandFloat(10) ) );
	p->dpos.Y() = ( 0.15f * Maths::RandFloat(1) ); 
	p->dpos.Z() = Maths::Sin(r) * ( 0.005f * Maths::RandFloat(10) );

	p->scale = 0.03f;
	p->t = 0;
	p->c = col;
	p->w = Maths::RandFloat( 100 );
}

void MyDemo::UpdateScene()
{
	GRAIN_DAT	*p;
	int			i, j;
	float		newY;
	float friction = 0.98f;

	//move balls
	if ( isBalls == 1 )
	{
		for ( i = 0; i < num_of_balls; i++ ) 
		{
			p = &balls[i];

			//count down to start
			if ( p->w > 0 ) 
			{
				p->w--;
				continue;
			}

			p->t++;
			newY = p->dpos.Y() * p->t - GRAV * p->t * p->t;

			if ( newY > p->pos.Y() )
			{
				p->pos.Y() = newY;
				continue;
			}

			makeExplosion( p, i, 0, GetRandColour() );
			this->init_ball( i );
			//init_ball(i);
		}
	}

	//move fireworks
	for ( i = 0; i < num_of_balls; ++i )
	{
		//if firewoek is alive
		if ( isFire[i] == 0 )
		{
			continue;
		}

		for ( j = 0; j < num_of_fire[i]; ++j )
		{
			p = &fire[i][j];
			p->t++;
			p->a -= p->d;
			
			if ( p->a < 0 )
			{
				p->a = 0;
				continue;
			}

			//slow down velocity
			p->dpos.X() *= friction;
			p->dpos.Y() *= friction;
			p->dpos.Z() *= friction;
			
			//move
			Vector3::Add( p->pos, p->dpos, p->pos );
		}		

	}

	//move sparks
	for ( i = 0; i < num_of_starts; ++i )
	{
		if ( isSpark == 0 )
			continue;

		for ( j = 0; j < num_of_sparks[i]; ++j )
		{
			p = &sparks[i][j];

			if ( p->w > 0 ) 
			{
				p->w--;
				continue;
			}

			p->t++;
			p->pos.Add( p->dpos );
			p->pos.Y()  = p->dpos.Y() * p->t - GRAV * p->t * p->t;

			if ( p->pos.Y() <= 0 )
			{
				init_spark( i, j, sparkPos[i], Colour::Yellow );
			}
		}
	}

	// make mid sphere bigger
	midSpherer.scale += 0.0001f;

	//move rockets
	if ( rocketState == NONE )
	{
		return;
	}

	for ( i = 0; i < num_of_rockets; ++i )
	{
		move_rocket( i );
	}
}

void MyDemo::UpdateState()
{
	float camSpeed = 0.0075f;
	int i;

	if ( currentScene == Intro )
	{
		if ( isSpark == 0 )
		{
			zInc = 0;

			isSpark = 1;
			num_of_sparks[0] = MAX_SPARKS;
			num_of_sparks[1] = MAX_SPARKS;

			isBalls = 0;
			isFire[0] = 0;
			isFire[1] = 0;
			isFire[2] = 0;
			midSpherer.scale = 0.0001f;
			midSpherer.c = Colour::White;
		}

		else if ( frames == 120 )
		{
			isBalls = 1;
		}
		
		else if ( frames > 240 )
		{
			rot.Y()++;
			if ( rot.Y() == 360 )
			{
				currentScene = MidSpherer;
				rocketState = SemiLine;
				viewT = 0;
				frames = 0;
				for ( i = 0; i < num_of_rockets; ++i )
					init_rocket( i, Colour::White );
			}
		}
	}
	else if ( currentScene == MidSpherer )
	{
		Vector3 start, end;

		rot.Y()++;
		if ( rot.Y() > 360 )
			rot.Y() -= 360;

		viewT += camSpeed;
		if ( viewT >= 1 )
		{
			viewT = 1;
		}
		else
		{
			//position
			Vector3::Lerp( stPos, airPos, viewT, pos );

			//rotation
			start.X() = 0;
			end.Y() = start.Y() = rot.Y();
			end.X() = 26;
			start.Z() = end.Z() = 0;
			Vector3::Lerp( start, end, viewT, rot );
		}

		if ( frames > 960 && rocket[0].t == 0 )
		{
			currentScene = HighGround;
			rocketState = SemiLine;
			viewT = 0;
			frames = 0;
			return;
		}

		//change rocket type and change colours of it and mid spherer
		else if ( frames > 660 && rocketState == SemiLine && rocket[0].t == 0 )
		{
			midSpherer.c = Colour::Yellow;
			rocketState = Circle;
			return;
		}
	}

	else if ( currentScene == HighGround )
	{
		rot.Y()++;
		if ( rot.Y() > 360 )
			rot.Y() -= 360;

		viewT += camSpeed;
		Vector3 end;
		if ( viewT > 1 )
		{
			viewT = 1;
		}
		else
		{
			end.X() = -0.35f;
			end.Y() = -6;
			end.Z() = -27.5f;
			Vector3::Lerp( airPos, end, viewT, pos );
		}

		if ( frames > 480 && rocket[0].t == 0 )
		{
			viewT = 0;
			currentScene = DownToGround;
			airRot = rot;
			frames = 0;
			isBalls = 1;
			return;
		}
	}

	else if ( currentScene == DownToGround )
	{
		viewT += camSpeed;
		Vector3 start, end;
		if ( viewT >= 1 )
		{
			viewT = 1;
		}
		else
		{
			start.X() = -0.35f;
			start.Y() = -6;
			start.Z() = -27.5f;
			Vector3::Lerp( start, stPos, viewT, pos );

			//rotation
			start.X() = airRot.X();
			start.Y() = airRot.Y();
			start.Z() = 0;
			end.Zero();
			Vector3::Lerp( start, end, viewT, rot );
		}

		//stop rockets and sparks
		if ( frames == 145 )
		{
			rocketState = Spin;
			for ( i = 0; i < num_of_rockets; ++i )
			{
				init_rocket( i, Colour::White );
			}

			rocketState = NONE;
			isSpark = 0;
		}

		else if ( frames == 400 )
		{
			rocketState = Spin;
			return;
		}

		else if ( frames == 1000 )
		{
			isSpark = 1;
			return;
		}
		
		else if ( frames > 1500 && frames < 2500 )
		{
			rot.Y()++;
			if ( rot.Y() > 360 )
				rot.Y() -= 360;
		}

		else if ( frames > 2500 && rocket[0].t == 0 )
		{
			midSpherer.c = Colour::Red;
			rocketState = Circle;
			for ( i = 0; i < num_of_rockets; ++i )
				init_rocket( i, Colour::Red );
		}

		else if ( frames > 2740 )
		{
			currentScene = End;
			frames = 0;
			viewT = 0;
		}
	}

	else if ( currentScene == End )
	{
		Vector3 start, end;
		viewT += camSpeed;
		if ( viewT > 1 )
		{
			viewT = 1;
			isBalls = 0;
			isSpark = 0;
		}
		else
		{
			//position
			Vector3::Lerp( stPos, airPos, viewT, pos );
			
			//rotation
			start.Zero();
			end.X() = 26;
			end.Y() = start.Y() = rot.Y();
			start.Z() = end.Z() = 0;
			Vector3::Lerp( start, end, viewT, rot );
		}

		//explode
		if ( frames == 600 )
		{
			pos = stPos;
			rot.Zero();
			viewT = 0;
			frames = 0;
			currentScene = Intro;
			fin = 0;
		}

		else if ( frames > 360 && rocket[0].t == 0 && fin == 0 )
		{
			//return;
			rocketState = NONE;
			midSpherer.c = 0x00000000;
			GRAIN_DAT* p = &balls[0];
			p->pos = midSpherer.pos;
			makeExplosion( p, 0, 1, GetRandColour() );
			isFire[0] = 1;
			fin = 1;
		}
	}
}

void MyDemo::makeExplosion(GRAIN_DAT *p, int num, short big, int col)
{
	float temp;
	float div = 0.01f;
	int i;
	int numOfFire;

	if ( big == 1 )
		numOfFire = MAX_FINISH;
	else
		numOfFire = MAX_EXPLOSION;

	for ( i = 0; i < numOfFire; ++i )
	{
		fire[num][i].pos.X() = p->pos.X();
		fire[num][i].pos.Y() = p->pos.Y();
		fire[num][i].pos.Z() = p->pos.Z();

		Maths::RandUnitVector( fire[num][i].dpos );
		fire[num][i].dpos.Multiply( 0.1f );

		fire[num][i].t = 0;
		fire[num][i].a = 0xd0;											//life time
		fire[num][i].c = Maths::Abs( Maths::RandFloat( 0x00ffffff ) ); //GetRandColour(); //col; Maths::RandColour( 0x00ffffff );	//col; //( (0xc0 + (rand() % 0x40) ) << 16 )| col;		//colour
		
		if ( big == 0 )
		{
			fire[num][i].scale = 0.035f;
			fire[num][i].d = 4;
		}
		else
		{
			fire[num][i].scale = 0.03f;
			fire[num][i].d = 2;
		}
	}

	num_of_fire[num] = numOfFire;
	isFire[num] = 1;
}

int MyDemo::GetRandColour()
{
	float ran = Maths::RandFloat( 4.0f );

	if ( ran < 1.0f )
	{
		return Colour::SetFade( Colour::Red );
	}
	else if ( ran < 2.0f )
	{
		return Colour::SetFade( Colour::Green );
	}
	else if ( ran < 3.0f )
	{
		return Colour::SetFade( Colour::Yellow );
	}
	else if ( ran < 3.5f )
	{
		return Colour::SetFade( Colour::CornFlowerBlue );
	}
	else 
	{
		return Colour::SetFade( Colour::White );
	}

	return Colour::Red;
}

void MyDemo::move_rocket(int i)
{
	float t1, t2, t3;
	float z = 0;

	Rocket* r = &rocket[i];

	if ( r->w )
	{
		r->w--;
		return;
	}

	//set interpolatin point
	r->t += r->speed;
	if ( r->t >= 1 )
	{
		init_rocket( i, r->colour );
	}

	//quadratic bezier curve calculation
	t1 = 1 - r->t;
	t2 = t1 * t1;
	t3 = r->t * r->t;

	r->pos.X() = r->start.X() * t2 + 2 * r->start.X() * t1 * r->t + 0	* t3;
	r->pos.Y() = r->start.Y() * t2 + 2 * TOP		  * t1 * r->t + TOP * t3;
	r->pos.Z() = r->start.Z() * t2 + 2 * r->start.Z() * t1 * r->t + z	* t3;
}


void MyDemo::DrawSphere(float r, int colour, int t)
{
	Vector3	scal( r, r, r );

	_renderer->BeginTransform();	
	_renderer->Scale( scal );
	_renderer->DrawSphere( colour, t );
	_renderer->EndTransform();
}


//--------------End of Application Mthods-------------//