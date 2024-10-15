#include <math.h>
#include <stdio.h>
#include <string.h>
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>
//window specific usleep implementation
void usleep(__int64 usec) {
  HANDLE timer;
  LARGE_INTEGER ft;
  ft.QuadPart = -(10 * usec);
  timer = CreateWaitableTimer(NULL, TRUE, NULL);
  SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
  WaitForSingleObject(timer, INFINITE);
  CloseHandle(timer);
}
#endif

//rotation
float A = 0, B = 0, C = 0;
//screen size
int width =80, height =40;
char buffer[80 * 40];
float zBuffer[80 * 40];

//ASCII background
int backgroundASCII = ' ';

//camera distance
int distanceCam = 5;
float K1 = 15;

//inc for surface plot
float increment = 0.07;

float f(float x, float y, float z) {
    //heart shape implicit func
    float temp = x*x + (9.0f/4.0f)*y*y + z*z - 1;
    return temp*temp*temp - x*x*z*z*z - (9.0f/80.0f)*y*y*z*z*z;

}




