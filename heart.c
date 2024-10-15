#include <math.h>
#include <stdio.h>
#include <string.h>
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>
//window specific usleep implementation
void usleep(unsigned int usec) {
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

void calculateSurface(float x0, float y0, float z0, int ch) {
    // rotate x axis
    float x1 = x0;
    float y1 = y0 * cos(A) - z0 * sin(A);
    float z1 = y0 * sin(A) + z0 * cos(A);
    // rotate y axis
    float x2 = x1 * cos(B) + z1 * sin(B);
    float y2 = y1;
    float z2 = -x1 * sin(B) + z1 * cos(B);
    // rotate z axis
    float x3 = x2 * cos(C) - y2 * sin(C);
    float y3 = x2 * sin(C) + y2 * cos(C);
    float z3 = z2 + distanceCam;


    //perspective
    float ooz = 1/z3;
    float xp = (int)(width / 2 + K1 * ooz * x3);
    int yp = (int)(height / 2 - K1 * ooz * y3);

    //calculate buffer

    int idx = xp + yp * width;
    if (idx >= 0 && idx < width * height) {
        //buffering
        if(ooz > zBuffer[idx]) {
            zBuffer[idx] = ooz;
            buffer[idx] = ch;
        }
    }
}

int main() {
    print("\x1b[2J");
    while (1) {
        //clear buffer
        memset(buffer, backgroundASCII, width * height);
        memset(zBuffer, 0, sizeof(zBuffer));

        //loop x and y
        for (float y = 1.5f; y >= -1.5f; y -= increment){
            for (float x = -1.5f; x <= 1.5f; x += increment) {
                float z = 0.0f;
                float v = f(x,y,z);
                if (v <= 0.0f) {
                    //solve for z using the Newton-Raphson method
                    float delta = 0.001f;
                    float z0 = 0.0f;
                    for (int i = 0; i < 10; i++) {
                        float fz = f(x, y, z0);
                        float fz1 = f(x, y, z0 + delta);
                        float derivative = (fz1 - fz) / delta;
                        if (derivative == 0) break;
                        z0 = z0 - fz / derivative;
                    }
                    calculateSurface(x, y, z0, '.');

                }
            }
        }
        // render
        printf("\x1b[H");
        for (int k = 0; k < width * height; k++){
            putchar(k % width ? buffer[k] : '\n');
        }
        //updated rotation
        A += 0.03f;
        B += 0.02f;
        C += 0.01f

        //sleep for short duration
        usleep(30000);
    }
    return 0;
}

