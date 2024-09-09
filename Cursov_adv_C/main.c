#include "func.h"
#define EPS 0.00001       //Точность вычисления 

int intersecting_points=0;                   
int iteration_counter=0;

//Аргументы командной строки
int main (int argc, char * argv[])
{
    if (argc>3)             
    {
        printf("Invalid number of arguments, use -help to get help");
        return 1;
    }
    if (argc>1)
    {
        if (!strcmp(argv[1], "-help"))
        {
            if (argc>2)
            {
                printf("Invalid number of arguments, use -help to get HELP");
                return 1;
            }
            printf("\nTo receive:\nCoordinates of the intersection points with the X and Y axes: -points");
            printf("\nThe number of iterations performed for the solution: -count");
            return 1;
        }
        for (int i = 1;i<argc;i++)
        {
            if (!strcmp(argv[i], "-points"))       
                intersecting_points++;             
            if (!strcmp(argv[i], "-count"))
                iteration_counter++;
        }
    }
    //Вычисление координат точек пересечения графиков функций и количества итераций 
    int counter = 0;
    point array[3] = {0};                                       
    counter+=calc_points(0.0001,5,EPS,Func1,Func3,&array[0]);    
    counter+=calc_points(0.0001,5,EPS,Func2,Func3,&array[1]);    
    counter+=calc_points(0.0001,5,EPS,Func1,Func2,&array[2]);    

    //Расчет интегралов методом трапеций
    float f1ac = integral(array[0].x, array[2].x, EPS, Func1); 
    float f3ac = integral(array[0].x, array[2].x, EPS, Func3);
    float f2bc = integral(array[1].x, array[2].x, EPS, Func2);
    float f3bc = integral(array[0].x, array[2].x, EPS, Func3);
    
    //Вычисление площади пересечения графиков функций
    float result = f1ac-f3ac-f2bc+f3bc; 
    if(intersecting_points)
    {
        printf("The points of intersection of the axes:\n");       
        printf("    X\t\t    Y\n");                           
        for (int i=0;i<3;i++)
            printf("%f\t%f\n",array[i].x,array[i].y);
    }
    if(iteration_counter)
        printf("\nThe calculation took  %d iterations\n",counter);   

    printf("\nThe area is %f\n",result);
    return 0;
}