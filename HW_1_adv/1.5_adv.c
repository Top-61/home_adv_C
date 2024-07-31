#include <stdio.h>
#include <inttypes.h>

/*На вход программе подается беззнаковое 32-битное целое
 число N и натуральное число K (1 ≤ K ≤ 31). Требуется взять
  K подряд идущих битов числа N так, чтобы полученное число
  было максимальным. Программа должна вывести полученное число.
*/



int main(int argc, char **argv)
{
    uint32_t N, K, bin;
    uint32_t max = 0;
    scanf("%d%d", &N, &K);
    bin = (1 << K) - 1;
    for (int i = 0; i <= 31; ++i)
    {
        if ((N&bin) > max)
            max = N&bin;
        N=N>>1;
    }
    printf("%d\n", max);
    return 0;
}

