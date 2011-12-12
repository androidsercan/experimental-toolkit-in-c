// $Id: timer.h 3755 2011-07-13 14:03:19Z haowu $

#ifndef _ETC_TIMER_H_
#define _ETC_TIMER_H_

//
//
//
#ifdef _WIN32
//
//
//

#ifdef _MSC_VER

#pragma comment(lib, "winmm.lib")
#include <windows.h>

class Timer
{
public:
  Timer()
  {
    Reset();
  }
  void Reset()
  {
    start_time = timeGetTime();
  }
  unsigned int GetTime()
  {
    DWORD stop_time = timeGetTime();
    return stop_time - start_time;
  }
protected:
  DWORD start_time;
};

#else

#include <ctime>
using namespace std;
class Timer
{
public:
  Timer()
  {
    Reset();
  }
  void Reset()
  {
    start_time = clock();
  }
  unsigned int GetTime()
  {
    return clock() - start_time;
  }
protected:
  clock_t start_time;
};

#endif

//
//
//
#else
//
//
//

#include <ctime>
using namespace std;
class Timer
{
public:
  Timer()
  {
    Reset();
  }
  void Reset()
  {
    clock_gettime(CLOCK_REALTIME, &start_time);
  }
  unsigned int GetTime()
  {
    struct timespec stop_time;
    clock_gettime(CLOCK_REALTIME, &stop_time);
    return   (stop_time.tv_sec - start_time.tv_sec) * 1000
      + (stop_time.tv_nsec - start_time.tv_nsec) / 1000000;
  }
protected:
  struct timespec start_time;
};

//
//
//
#endif
//
//
//

#endif
