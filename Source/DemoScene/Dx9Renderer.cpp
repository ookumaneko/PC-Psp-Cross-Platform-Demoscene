#if !defined(_PSP_VER)
#include "Renderer.h"
#include "Game.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Maths.h"

//initialize static members
IDirect3DDevice9*		BaseRenderer::_gd3dDevice	= 0;
IDirect3D9*				BaseRenderer::_d3dObject	= 0;
DWORD					BaseRenderer::_requestedVP	= 0;

//--------Start of Framework Methods----------//

void Renderer::Initialize(CullMode cull)
{
	_requestedVP = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	_devType = D3DDEVTYPE_HAL;
	_hWnd = Game::GetInstance()->_hWnd;
	_isDrawing = false;
	float _width = 480;	//Game::GetInstance()->GetScreenWidth();
	float _height = 272;	//Game::GetInstance()->GetScreenHeight();

	// Step 1: Create the IDirect3D9 object.

    _d3dObject = Direct3DCreate9(D3D_SDK_VERSION);
	if( !_d3dObject )
	{
		MessageBox(0, "Direct3DCreate9 FAILED", 0, 0);
		PostQuitMessage(0);
	}


	// Step 2: Verify hardware support for specified formats in windowed and full screen modes.
	
	D3DDISPLAYMODE mode;
	_d3dObject->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &mode);
	_d3dObject->CheckDeviceType(D3DADAPTER_DEFAULT, _devType, mode.Format, mode.Format, true);
	_d3dObject->CheckDeviceType(D3DADAPTER_DEFAULT, _devType, D3DFMT_X8R8G8B8, D3DFMT_X8R8G8B8, false);

	// Step 3: Check for requested vertex processing and pure device.

	D3DCAPS9 caps;
	_d3dObject->GetDeviceCaps(D3DADAPTER_DEFAULT, _devType, &caps);

	DWORD devBehaviorFlags = 0;
	if( caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
		devBehaviorFlags |= _requestedVP;
	else
		devBehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	// If pure device and HW T&L supported
	if( caps.DevCaps & D3DDEVCAPS_PUREDEVICE &&
		devBehaviorFlags & D3DCREATE_HARDWARE_VERTEXPROCESSING)
			devBehaviorFlags |= D3DCREATE_PUREDEVICE;

	// Step 4: Fill out the D3DPRESENT_PARAMETERS structure.

	_d3dPP.BackBufferWidth            = 0; 
	_d3dPP.BackBufferHeight           = 0;
	_d3dPP.BackBufferFormat           = D3DFMT_UNKNOWN;
	_d3dPP.BackBufferCount            = 1;
	_d3dPP.MultiSampleType            = D3DMULTISAMPLE_NONE;
	_d3dPP.MultiSampleQuality         = 0;
	_d3dPP.SwapEffect                 = D3DSWAPEFFECT_DISCARD; 
	_d3dPP.hDeviceWindow              = _hWnd;
	_d3dPP.Windowed                   = true;
	_d3dPP.EnableAutoDepthStencil     = true; 
	_d3dPP.AutoDepthStencilFormat     = D3DFMT_D24S8;
	_d3dPP.Flags                      = 0;
	_d3dPP.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	_d3dPP.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;

	// Step 5: Create the device.

	HR(_d3dObject->CreateDevice(
		D3DADAPTER_DEFAULT, // primary adapter
		_devType,           // device type
		_hWnd,				// window associated with device
		devBehaviorFlags,   // vertex processing
	    &_d3dPP,            // present parameters
	    &_gd3dDevice));     // return created device

	//initialize view matrix
    D3DXVECTOR3 vEyePt( 0.0f, 0.0f, 0.1f );
    D3DXVECTOR3 vLookatPt( 0, 0, 0 );// 0.0f, 0.0f, 0.0f );
    D3DXVECTOR3 vUpVec( 0, 1.0f, 0); //0.0f, 1.0f, 0.0f );
	//D3DXMatrixLookAtLH( &_viewMatrix.GetMatrix(), &vEyePt, &vLookatPt, &vUpVec );
	D3DXMatrixLookAtRH( &_viewMatrix.GetMatrix(), &vEyePt, &vLookatPt, &vUpVec );

	HR( D3DXCreateSphere( _gd3dDevice, 0.8f, 8, 8, &_sphere, 0 ) );

	// Turn on culling
	if ( cull == CullMode::Clock )
		_gd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW );
	else if ( cull == CullMode::CClock )
		_gd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
	else
		_gd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW );

	// Turn on D3D lighting
    _gd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
	
	//disable z-buffer
	_gd3dDevice->SetRenderState( D3DRS_ZENABLE, FALSE );

	//set wireframe
	_gd3dDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );	// D3DFILL_SOLID 

	//setup lights
	//_gd3dDevice->SetRenderState( D3DRS_AMBIENT, 0xff4c4c4c );
	
	//set up lights
	D3DXVECTOR3 dir;
	D3DLIGHT9 light;
	ZeroMemory( &light, sizeof( D3DLIGHT9 ) );
	
	//create white directional light
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.a = 1.0f;
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	light.Position = D3DXVECTOR3(0,0,0);
	//light.Ambient.a = 1.0f;
	light.Ambient.r = 1.0f;
	light.Ambient.g = 1.0f;
	light.Ambient.b = 1.0f;
	light.Specular.r = 1.0f;
	light.Specular.g = 1.0f;
	light.Specular.b = 1.0f;
	light.Specular.a = 1.0f;
	light.Position.y = 20;

	dir = D3DXVECTOR3( 0.0f, -1.0f, 0.0f );
	D3DXVec3Normalize( ( D3DXVECTOR3* )&light.Direction, &dir );

	light.Range = 1000.0f;
	_gd3dDevice->SetLight( 0, &light );
	_gd3dDevice->LightEnable( 0, TRUE );
}

void Renderer::Shutdown()
{
	if ( _d3dObject )	ReleaseCOM( _d3dObject );
	if ( _gd3dDevice )	ReleaseCOM( _gd3dDevice );
	//if ( _sphere )		ReleaseCOM( _sphere );

	//_sphere = 0;
	_d3dObject = 0;
	_gd3dDevice = 0;
}

void Renderer::Draw(float delta)
{

}


//----------End of Framework Methods----------//



//------------Start of Setup Methods----------//


void Renderer::SetProjection(float fov, float aspectRatio, float nearZ, float farZ)
{
	//D3DXMatrixPerspectiveFovRH( &_projectionMatrix.GetMatrix(), Maths::DegreeToRadian( fov ), aspectRatio, nearZ, farZ  );
	D3DXMatrixPerspectiveFovLH( &_projectionMatrix.GetMatrix(), Maths::DegreeToRadian( fov ), aspectRatio, nearZ, farZ );
}


//-------------End of Setup Methods-----------//



//--------Start of Transform Methods----------//

void Renderer::BeginTransform()
{
	Matrix4 temp; // = _transformStack.top();
	
	if ( !_transformStack.empty() )
	{
		 temp = _transformStack.top();
	}

	//_prevTransform = _worldTransform;
	_transformStack.push( temp );
}

void Renderer::EndTransform()
{
	//_worldTransform = _prevTransform;
	if ( !_transformStack.empty() )
	{
		_transformStack.pop();
	}
}

void Renderer::SetTransform(const Matrix4& world)
{
	//_worldTransform = world;
	if ( !_transformStack.empty() )
	{
		_transformStack.pop();
	}

	_transformStack.push( world );
}

Matrix4 Renderer::GetCurrentTransform()
{
	return _transformStack.top();
}

void Renderer::Translate(const Vector3 &trans)
{
	//_worldTransform.Translate( trans.X(), trans.Y(), trans.Z() );
	if ( !_transformStack.empty() )
	{
		Matrix4 temp = _transformStack.top();
		_transformStack.pop();

		temp.Translate( trans.X(), trans.Y(), trans.Z() );
		//temp.SetTranslate( Vector4( trans.X(), trans.Y(), trans.Z(), 1 ) );
		_transformStack.push( temp );
	}
}

void Renderer::Rotate(const Vector3 &rot)
{
	Vector4 r( rot.X(), rot.Y(), rot.Z(), 1 );
	//_worldTransform.RotateXYZ( r );

	if ( !_transformStack.empty() )
	{
		Matrix4 temp = _transformStack.top();
		_transformStack.pop();
		temp.RotateXYZ( r );
		_transformStack.push( temp );
	}
}

void Renderer::RotateX(float degree)
{
	//_worldTransform.RotateX( Maths::DegreeToRadian( degree ) );
	if ( !_transformStack.empty() )
	{
		Matrix4 temp = _transformStack.top();
		_transformStack.pop();
		temp.RotateX( Maths::DegreeToRadian( degree ) );
		_transformStack.push( temp );
	}
}

void Renderer::RotateY(float degree)
{
	//_worldTransform.RotateY( Maths::DegreeToRadian( degree ) );
	if ( !_transformStack.empty() )
	{
		Matrix4 temp = _transformStack.top();
		_transformStack.pop();
		temp.RotateY( Maths::DegreeToRadian( degree ) );
		_transformStack.push( temp );
	}
}

void Renderer::RotateZ(float degree)
{
	//_worldTransform.RotateZ( Maths::DegreeToRadian( degree ) );
	if ( !_transformStack.empty() )
	{
		Matrix4 temp = _transformStack.top();
		_transformStack.pop();
		temp.RotateZ( Maths::DegreeToRadian( degree ) );
		_transformStack.push( temp );
	}
}

void Renderer::RotateWorld(const Vector3& rot)
{
    D3DXVECTOR3 vEyePt( 0.0f, 0.0f, 0.1f );
    D3DXVECTOR3 vLookatPt( 0, 0, 0 );
    D3DXVECTOR3 vUpVec( 0, 1.0f, 0); 

	vEyePt.x = 0.1f * sinf( D3DXToRadian( rot.Y() ) );
	vEyePt.z = 0.1f * cosf( D3DXToRadian( rot.Y() ) );
	//vEyePt.y = 0.1f * D3DXToRadian( rot.X() );
	//vLookatPt.y = 0.1f * D3DXToRadian( rot.X() );
	D3DXMatrixLookAtLH( &_viewMatrix.GetMatrix(), &vEyePt, &vLookatPt, &vUpVec );

	RotateY( rot.Y() );
}

void Renderer::Scale(const Vector3 &scale)
{
	if ( !_transformStack.empty() )
	{
		Matrix4 temp = _transformStack.top();
		_transformStack.pop();
		temp.Scale( scale.X() , scale.Y(), scale.Z() );
		_transformStack.push( temp );
	}
}


//----------End of Transform Methods----------//


//----------Start of Render Methods-----------//


void Renderer::Clear()
{
	_gd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, _clearColour, 1.0f, 0 );
}

void Renderer::Begin()
{
	if ( SUCCEEDED( _gd3dDevice->BeginScene() ) )
	{
		_isDrawing = true;
		
		//tranforms
		_gd3dDevice->SetTransform( D3DTS_VIEW, &_viewMatrix.GetMatrix() );
		_gd3dDevice->SetTransform( D3DTS_PROJECTION, &_projectionMatrix.GetMatrix() );
	}
}

void Renderer::End()
{
	if ( _isDrawing )
	{
		_gd3dDevice->EndScene();
		_isDrawing = false;
	}

	_gd3dDevice->Present( NULL, NULL, NULL, NULL );
}

void Renderer::DrawSphere(unsigned int colour, int val)
{
	if ( _sphere )
	{
		D3DMATERIAL9 mtr;
		ZeroMemory( &mtr, sizeof( D3DMATERIAL9 ) );
		
		D3DXCOLOR c( colour );
		c.r *= ( c.a * c.a );// * c.a );// * 0.5f );
		c.g *= ( c.a * c.a ); //* c.a ); //* 0.5f );
		c.b *= ( c.a * c.a ); //* c.a ); //* 0.5f );

		mtr.Ambient = c;
		mtr.Diffuse = c;
		mtr.Specular = c;
		_gd3dDevice->SetMaterial( &mtr );

		Matrix4 temp = _transformStack.top();
		_gd3dDevice->SetTransform( D3DTS_WORLD, &temp.GetMatrix() );
		//_gd3dDevice->SetTransform( D3DTS_WORLD, &_transformStack.top().GetMatrix() );

		_sphere->DrawSubset(0);
	}
}


//------------End of Render Methods-----------//
#endif