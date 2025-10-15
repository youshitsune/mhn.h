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
    float X[P][N] = {{-1, 1, 1, 1}, {1, 1, 1, -1}, {1, -1, -1, 1}};
    float eps[N] = {1, -1, 1, 1};
    
    // to_pointer is macro for turning pointer to matrix to simple pointer
    Net net = net_init(P, N, 8.0f, to_pointer(X), eps);
    net_converge(net);
    
    for (int i = 0; i < N; i++) {
        printf("%f ", eps[i]);
    }
    printf("\n");
}
```
