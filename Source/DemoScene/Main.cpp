#include "Vector3.h"
#include "MyDemo.h"


static MyDemo* demo = 0;

#ifdef _PSP_VER

#include <psptypes.h>
#include <kernel.h>
#include <displaysvc.h>
#include <ctrlsvc.h>
#include <libgu.h>
#include <libgum.h>
#include <libvfpu.h>

SCE_MODULE_INFO( Fireworks, 0, 1, 1 );

//use VFPU on the main thread
int sce_user_main_thread_attribute = SCE_KERNEL_TH_USE_VFPU;
//static 	char _disp_list[0x10000]__attribute__((aligned(64)));

int main(void)
{
	demo = new MyDemo();//MyDemo::GetInstance();
	demo->Run();

	delete demo;
	demo = 0;

	return 0;
}

#else
#include <windows.h>


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
				   PSTR cmdLine, int showCmd)
{
	// Enable run-time memory check for debug builds.
	//#if defined(DEBUG) | defined(_DEBUG)
	//	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//#endif
	
	//initialize application
	demo = new MyDemo();
	demo->_hInstance = hInstance;
	
	//run the application
	int ret = demo->Run();

	//finish application
	demo->Shutdown();
	delete demo;
	demo = 0;

	return ret;
}

#endif