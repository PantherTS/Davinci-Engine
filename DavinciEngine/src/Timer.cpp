#include "LowLevelSystem.h"
#include "Timer.h"

#ifdef _WIN32
#include <Windows.h>
#pragma comment(lib, "winmm.lib")
#else
#include <sys/time.h>
#endif

using namespace DavinciEngine;

Timer *Timer::m_Timer = nullptr;

Timer::Timer()
{
	//Initialize the variables
	startTicks = 0;
	pausedTicks = 0;
	currentTicks = 0;
	previousTicks = 0;
	deltaTime = 0;
	paused = false;
	started = false;
	//timeBeginPeriod(1);
}

Timer::~Timer()
{

}

Timer *Timer::GetInstance ( void )
{
	if (!m_Timer) {
		m_Timer = new Timer();
		m_Timer->start();
	}

	return m_Timer;
}

void Timer::Destroy()
{
	if(m_Timer){
		delete m_Timer;
		m_Timer = nullptr;
	}
}

void Timer::start()
{
	//Start the timer
	started = true;
	//timeBeginPeriod(1);

	//Unpause the timer
	paused = false;

	//Get the current clock time
	startTicks = GetTicks();
}

void Timer::stop()
{
	//Stop the timer
	started = false;
	//timeEndPeriod(1);

	//Unpause the timer
	paused = false;    
}

void Timer::Update(){

	//If the timer is running
	if( started == true)
	{
		if(paused == false){
			currentTicks = GetTicks() - startTicks;
			deltaTime = MIN((((double)currentTicks - (double)previousTicks))/1000.0, MAX_DELTA_TIME);

			/*char buff[1024];
			sprintf(buff,"Current Ticks:%Ld - Previous Ticks:%Ld = DeltaTime:%Ld\n",currentTicks,previousTicks,deltaTime);
			OutputDebugString(buff);*/

			//Inject timepulse into GUI here
		}
		else{
			currentTicks = pausedTicks;
			deltaTime = 0;
		}
	}
}

long Timer::GetTicks()
{
	//If the timer is running
	if( started == true )
	{
		//If the timer is paused
		if( paused == true )
		{
			//Return the number of ticks when the timer was paused
			return pausedTicks;
		}
		else
		{
#ifdef _WIN32
			//Return the currentTicks.
			return (long)timeGetTime();
#else
			//Return time for linux
			struct timeval now;
			gettimeofday(&now, NULL);
			return now.tv_usec / 1000;
#endif
		}
	}

	//If the timer isn't running
	return 0;
}

void Timer::SetPreviousTicks()
{
	previousTicks = currentTicks;
}

void Timer::pause()
{
	//If the timer is running and isn't already paused
	if( ( started == true ) && ( paused == false ) )
	{
		Log("Timer: Game Paused.");
		//Set paused ticks
		pausedTicks = GetTicks() - startTicks;
		paused = true;
	}
}

void Timer::unpause()
{
	//If the timer is paused
	if( paused == true )
	{
		//Unpause the timer
		Log("Timer: Game Upaused");
		paused = false;

		//Reset the starting ticks
		startTicks = GetTicks() - pausedTicks;

		//Reset the paused ticks
		pausedTicks = 0;
	}
}

bool Timer::is_started()
{
	return started;
}

bool Timer::is_paused()
{
	return paused;
}