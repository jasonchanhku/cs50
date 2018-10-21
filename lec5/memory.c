//using valgrind to prevent overflow

#include <stdlib.h>

void f(void)
{
    int *x = malloc(10*sizeof(int));
    // out of bound assignment
    //x[10] = 0;
    x[9] = 0;
    free(x);
}

int main (void){

    f();

}