#include <stdio.h>
#include <inttypes.h>

/*На вход программе подается беззнаковое 32-битное целое число N
и натуральное число K (1 ≤ K ≤ 31).
Требуется взять K младших битов числа N и
 вывести полученное таким образом число.
Пример №1
.*/



int main(int argc, char **argv)
{
    uint32_t N, K;
    scanf("%d %d", &N, &K);
    uint32_t res =N &((1 <<K)-1);
    printf("%"PRIu32, res);
    return 0;
}
