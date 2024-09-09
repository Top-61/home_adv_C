#include <stdio.h>
#include <math.h>
#include <string.h>

//Структура для точки с двумя координатами
typedef struct point 
{
    float x;
    float y;            
} point;                

float Func1(float x);
float Func2(float x);
float Func3(float x);
int Sign(float x);

float root(float (*f1)(float), float (*f2)(float), float xl, float xr, float eps, int *counter);
int calc_points(float xl, float xr, float eps, float (*f1)(float), float (*f2)(float), point* obj);
float integral(float xl, float xr, float eps, float (*f)(float));