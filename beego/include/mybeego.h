//=====================================================//
/*!
    @file mybeego.h
    @brief header for vxvtools
*/
//=====================================================//
//to use simulator, define the following line.
//#define USE_SIMULATOR
#ifdef WIN32
#ifdef USE_SIMULATOR//for simulator
	#pragma comment(lib, "SDL.lib")
	#pragma comment(lib, "SDLmain.lib")
	#pragma comment(lib, "SDL_net.lib")
	#pragma comment(lib, "SDL_ttf.lib")
	#pragma comment(lib, "vxv2_monitor.lib")
#else//for real robot
	#pragma comment(lib, "vxv2.lib")
#endif
#endif
//================header filed====================//
#ifdef USE_SIMULATOR//for simulator
	#include <mRunCtrl.h>
	#include <mURGCtrl.h>
	#include "vutils.h"

#else
	#include <vxv2/runCtrl.h>
	#include <vxv2/urgCtrl.h>
	#include <vxv2/pathUtils.h>
	#include <vxv2/vutils.h>
#endif

using namespace VXV;

//====================functions============================//

//======================================================//
/*!
   @brief apply velocity input
   @param run
   @param straight traslational velocity[mm/sec]
   @param Direction rotational velocity[rad/sec]
   @retval void
*/
//=======================================================//
static void setVelocityCtrl(RunCtrl& run,double straight, double rotate)
{

  enum { RIGHT = 0, LEFT = 1 };  
  int whl_mm_vel[2];
  int rotate_mm_vel = static_cast<int>(BODY_TREAD_MM/2 * rotate);
  whl_mm_vel[RIGHT] = straight + rotate_mm_vel;
  whl_mm_vel[LEFT] = straight - rotate_mm_vel;

  for (int i = 0; i < 2; ++i) {
    run.setWheelVel(i, whl_mm_vel[i]);
  }
}

