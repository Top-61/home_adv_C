#include "func.h"

//Заданные функции
float Func1(float x)    
{
    return 0.6*x+3;
}
float Func2(float x)
{
    x-=2;
    return x*x*x-1;
}
float Func3(float x)
{
    return (3/x);
}

//Проверка знака
int Sign(float x)   
{
    if (x<0)
        return 0;
    else
        return 1;
}
//Расчет методом деления прямоугольника
float root(float (*f1)(float), float (*f2)(float), float xl, float xr, float eps, int *counter)
{
    float xm;
    while (fabs(xl-xr)>eps)
    {
        *counter += 1;                  
        xm=(xl+xr)/2;                                  
        if(f1(xr)-f2(xr)==0)                          
            return xr;
        if(f1(xl)-f2(xl)==0)
            return xl;
        if(Sign(f1(xl)-f2(xl))!= Sign(f1(xm)-f2(xm)))
            xr=xm;
        else
            xl=xm;
    }
    return (xl+xr)/2;
}
//Рассчет координат точек пересечения
int calc_points(float xl, float xr, float eps, float (*f1)(float), float (*f2)(float), point* obj)
{
    int counter;                                             
    float x,y;                                          
    x = root(f1,f2,xl,xr,eps,&counter);           
    y = (f1(x) + f2(x))/2;
    obj->x=x;
    obj->y=y;
    return counter;
}

//Расчет значения интеграла методом трапеций
float integral(float xl, float xr, float eps, float (*f)(float))
{
    float sum = 0;
    for(float x=xl+eps; x<xr-eps; x+=eps)              
    {
        sum += 0.5*eps*(f(x)+f(x+eps));
    }
    return sum;
}