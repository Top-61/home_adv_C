#include <stdio.h>
#include <inttypes.h>

/*На вход программе подается беззнаковое 32-битное целое число N.
 Требуется найти количество единичных битов в
 двоичном представлении данного числа.
*/


int main(int argc, char **argv)
{
    uint32_t N;
    uint8_t cnt = 0;
    scanf("%d", &N);
    while (N!=0)
    {
        cnt++;
        N &= N - 1;
        //printf("%" PRIu32" " , N);
    }
    printf("\n" "%" PRIu8"\n", cnt);
    return 0;
}

