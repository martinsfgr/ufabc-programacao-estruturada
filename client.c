#include <stdio.h>
#include <stdlib.h>
#include "bignumber.h"

int main() {
    BigNumber* x = create_big_number("-134");
    BigNumber* y = create_big_number("-133");

    int comparison_big_numbers = return_largest_big_number(x, y);
    printf("A comparação entre os Big Numbers retornou: %d\n", comparison_big_numbers);

    BigNumber* sum = sum_big_numbers(x, y);
    BigNumber* subtraction = subtraction_big_numbers(x, y);

    print_big_number(sum);
    printf("\n");
    print_big_number(subtraction);

    free_big_number(x);
    free_big_number(y);
    free_big_number(sum);

    printf("\n");

    return 0;
}