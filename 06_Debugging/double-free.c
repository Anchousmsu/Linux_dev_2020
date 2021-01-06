#include <stdlib.h>


int main()
{
    double *x = malloc(5 * sizeof(double));
    free(x);
    free(x);
    return 0;
}
