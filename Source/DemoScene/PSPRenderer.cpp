#if defined (_PSP_VER)
#include "Renderer.h"
#include "Vector3.h"
#include "Matrix4.h"
#include <stdlib.h>
#include "Maths.h"
#include <psptypes.h>
#include <kernel.h>
#include <displaysvc.h>
#include <ctrlsvc.h>
#include <libgu.h>
#include <libgum.h>
#include <libvfpu.h>

// static variables
char BaseRenderer::_disp_list[];
ScePspFMatrix4 BaseRenderer::_matrix_stack[];

const ScePspFVector3	BaseRenderer::sphere[] = 
{
	{ 0.000000f,  1.000000f,  0.000000f, },
	{ 1.333333f,  1.000000f,  0.000000f, },
	{ 1.333333f, -1.000000f,  0.000000f, },
	{ 0.000000f, -1.000000f,  0.000000f, },
	{ 0.000000f,  1.000000f,  0.000000f, },
	{ 1.333333f,  1.000000f, -1.777777f, },
	{ 1.333333f, -1.000000f, -1.777777f, },
	{ 0.000000f, -1.000000f,  0.000000f, },
	{ 0.000000f,  1.000000f,  0.000000f, },
	{-1.333333f,  1.000000f, -1.777777f, },
	{-1.333333f, -1.000000f, -1.777777f, },
	{ 0.000000f, -1.000000f,  0.000000f, },
	{ 0.000000f,  1.000000f,  0.000000f, },
	{-1.333333f,  1.000000f,  0.000000f, },
	{-1.333333f, -1.000000f,  0.000000f, },
	{ 0.000000f, -1.000000f,  0.000000f, },
	{ 0.000000f,  1.000000f,  0.000000f, },
	{-1.333333f,  1.000000f,  1.777777f, },
	{-1.333333f, -1.000000f,  1.777777f, },
	{ 0.000000f, -1.000000f,  0.000000f, },
	{ 0.000000f,  1.000000f,  0.000000f, },
	{ 1.333333f,  1.000000f,  1.777777f, },
	{ 1.333333f, -1.000000f,  1.777777f, },
	{ 0.000000f, -1.000000f,  0.000000f, },
	{ 0.000000f,  1.000000f,  0.000000f, },
	{ 1.333333f,  1.000000f,  0.000000f, },
	{ 1.333333f, -1.000000f,  0.000000f, },
	{ 0.000000f, -1.000000f,  0.000000f, },
};

//--------Start of Framework Methods----------//

void Renderer::Initialize(CullMode cull)
{
	const ScePspIMatrix4	dith = {
							{-4,  0, -3,  1},
							{ 2, -2,  3, -1},
							{-3,  1, -4,  0},
							{ 3, -1,  2, -2} };
	ScePspFVector3	vec;

	sceGuInit();
	sceGuStart( SCEGU_IMMEDIATE, _disp_list, sizeof( _disp_list ) );

	sceGuDrawBuffer( SCEGU_PF5551, SCEGU_VRAM_BP_0, SCEGU_VRAM_WIDTH );
	sceGuDispBuffer( SCEGU_SCR_WIDTH, SCEGU_SCR_HEIGHT,
					SCEGU_VRAM_BP_1, SCEGU_VRAM_WIDTH );
	sceGuDepthBuffer( SCEGU_VRAM_BP_2, SCEGU_VRAM_WIDTH );

	sceGuOffset( SCEGU_SCR_OFFSETX, SCEGU_SCR_OFFSETY );
	sceGuViewport( 2048, 2048, SCEGU_SCR_WIDTH, SCEGU_SCR_HEIGHT );
	sceGuDepthRange( 50000, 10000 );

	sceGuScissor( 0, 0, SCEGU_SCR_WIDTH, SCEGU_SCR_HEIGHT );
	sceGuEnable( SCEGU_SCISSOR_TEST );

	sceGuBlendFunc( SCEGU_ADD, SCEGU_SRC_ALPHA, SCEGU_ONE_MINUS_SRC_ALPHA, 0, 0 );
	sceGuEnable( SCEGU_BLEND );

	sceGuDepthFunc( SCEGU_GEQUAL );
	sceGuEnable( SCEGU_DEPTH_TEST );

	if ( cull == Clock )
		sceGuFrontFace( SCEGU_CW );
	else if ( cull == CClock )
		sceGuFrontFace( SCEGU_CCW );
	else
		sceGuFrontFace( SCEGU_CW );

	sceGuSetDither( &dith );
	sceGuEnable( SCEGU_DITHER );
	sceGuEnable( SCEGU_CLIP_PLANE );
	sceGuShadeModel( SCEGU_SMOOTH );

	vec.x=-1.0f;
	vec.y= 1.0f;
	vec.z= 1.0f;

	sceGuLightColor( 0, SCEGU_DIFFUSE, 0xffffffff );
	sceGuLightColor( 0, SCEGU_SPECULAR, 0xffffffff );
	sceGuLight( 0, SCEGU_LIGHT_DIRECTION, SCEGU_DIFFUSE_AND_SPECULAR, &vec );
	sceGuEnable( SCEGU_LIGHT0 );
	sceGuEnable( SCEGU_LIGHTING );

	sceGuAmbient( 0xffffffff );//0xff4c4c4c );
	sceGuColor( 0xffe0e0e0 );

	sceGumSetMatrixStack( &_matrix_stack[0], 8, 8, 32, 0 );

	sceGumMatrixMode( SCEGU_MATRIX_PROJECTION );
	sceGumLoadIdentity();
	sceGumPerspective( SCEGU_RAD(45.0f), SCEGU_SCR_ASPECT,
					0.1000000f, 100.000000f );

	sceGumMatrixMode( SCEGU_MATRIX_WORLD );

	sceGuClearColor( 0x00000000 );
	sceGuClearDepth(0);
	sceGuClearStencil(0);

	sceGuPatchPrim( SCEGU_PRIM_LINE_STRIP );

	sceGuFinish();
	sceGuSync( SCEGU_SYNC_FINISH, SCEGU_SYNC_WAIT );

	sceGuDisplay( SCEGU_DISPLAY_ON );
}

void Renderer::Shutdown()
{
	sceGuTerm();
}

void Renderer::Draw(float delta)
{

}


//----------End of Framework Methods----------//



//------------Start of Setup Methods----------//


void Renderer::SetProjection(float fov, float aspectRatio, float nearZ, float farZ)
{
	sceGumMatrixMode( SCEGU_MATRIX_PROJECTION );
	sceGumLoadIdentity();
	sceGumPerspective( SCEGU_RAD(fov), SCEGU_SCR_ASPECT, nearZ, farZ );
	sceGumMatrixMode( SCEGU_MATRIX_WORLD );
}


//-------------End of Setup Methods-----------//


//--------Start of Transform Methods----------//

void Renderer::BeginTransform()
{
	sceGumPushMatrix();
}

void Renderer::EndTransform()
{
	sceGumPopMatrix();
}

void Renderer::SetTransform(const Matrix4& world)
{
	sceGumLoadMatrix( &world.GetMatrix() );
}

Matrix4 Renderer::GetCurrentTransform()
{
	Matrix4 mat;
	
	// get the current matrix
	sceGumStoreMatrix( &mat.GetMatrix() );
	return mat;
}

void Renderer::Translate(const Vector3 &trans)
{
	sceGumTranslate( &trans.GetVector() );
}

void Renderer::Rotate(const Vector3 &rot)
{
	sceGumRotateXYZ( &rot.GetVector() );
}

void Renderer::RotateX(float degree)
{
	sceGumRotateX( Maths::DegreeToRadian( degree ) );
}

void Renderer::RotateY(float degree)
{
	sceGumRotateY( Maths::DegreeToRadian( degree ) );
}

void Renderer::RotateZ(float degree)
{
	sceGumRotateZ( Maths::DegreeToRadian( degree ) );
}

void Renderer::RotateWorld(const Vector3& rot)
{
	sceGumRotateX( Maths::DegreeToRadian( rot.X() ) );
	sceGumRotateY( Maths::DegreeToRadian( rot.Y() ) );
	sceGumRotateZ( Maths::DegreeToRadian( rot.Z() ) );
}

void Renderer::Scale(const Vector3 &scale)
{
	sceGumScale( &scale.GetVector() );
}


//----------End of Transform Methods----------//


//----------Start of Render Methods-----------//


void Renderer::Clear()
{
	sceGuClear( SCEGU_CLEAR_ALL );
}

void Renderer::Begin()
{
	sceGuStart( SCEGU_IMMEDIATE, _disp_list, sizeof(_disp_list) );
}

void Renderer::End()
{
	sceGuFinish();
	sceGuSync( SCEGU_SYNC_FINISH, SCEGU_SYNC_WAIT );

	sceDisplayWaitVblankStart();
	sceGuSwapBuffers();
}

void Renderer::DrawSphere(unsigned int colour, int val)
{
	int		d;

	if ( val < 30 )			d = 3;
	else if ( val < 60 )	d = 4;
	else if ( val < 90 )	d = 6;
	else					d = 8;

	// set divide
	sceGuPatchDivide(d, d);

	// set colour
	sceGuColor( colour );

	// draw
	//sceGumDrawArray( SCEGU_PRIM_LINE_STRIP , SCEGU_VERTEX_FLOAT, 28, 0, sphere );
	sceGumDrawBezier( SCEGU_VERTEX_FLOAT, 4, 7, 0, sphere );
}

//------------End of Render Methods-----------//

#endif