# mhn.h
C header-only implementation of mhn.

### Usage
```c
#include <stdio.h>
#include "mhn.h"

#define P 3
#define N 4

int main(void){
    // Values from [-1, 1]
    float X[P][N] = {{-1, 0.5, 0.5, 0.1}, {0.8, 0.2, 0.3, -1}, {-0.3, -0.2, 0, 0}};

    // Values in here that you don't know (or are trying to predict) should be zero
    float eps[N] = {0.8, 0.2, 0, 0};
    
    // to_pointer is macro for turning pointer to matrix to simple pointer
    Net net = net_init(P, N, 8.0f, to_pointer(X), eps);
    net_converge(net);
    
    for (int i = 0; i < N; i++) {
        printf("%f ", eps[i]);
    }
    printf("\n");
}
```
