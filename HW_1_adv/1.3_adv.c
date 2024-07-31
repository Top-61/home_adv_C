#include <stdio.h>
#include <inttypes.h>

/*На вход программе подается беззнаковое 32-битное целое число N и
  натуральное число K (1 ≤ K ≤ 31).
  Требуется циклически сдвинуть биты числа N вправо на K битов и
  вывести полученное таким образом число.*/



int main(int argc, char **argv)
{
    uint32_t N, K;
    scanf("%d %d", &N, &K);
    uint32_t res =( N >> K ) | ( N << (32 - K));
    printf("%u\n", res);
    return 0;
}
