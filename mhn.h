#include <stdlib.h>
#include <math.h>

#ifndef N
#define N 2
#endif

#ifndef P
#define P 1
#endif

#ifndef BETA
#define BETA 8.0f
#endif

void net_softmax(float arr[P][1]) {
    const float e = 2.71828;

    float mx = arr[0][0];
    for (int i = 1; i < P; i++) {
        if (mx < arr[i][0]) mx = arr[i][0];
    }

    float sum = 0;
    for (int i = 0; i < P; i++) {
        arr[i][0] = pow(e, arr[i][0]-mx);
        sum += arr[i][0];
    }

    for (int i = 0; i < P; i++) {
        arr[i][0] /= sum;
    }
}

void net_scalarmul(float arr[P][1], float v) {
    for (int i = 0; i < P; i++) {
        arr[i][0] *= v;
    }
}

void net_transpose(float X[P][N], float T[N][P]) {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < N; j++) {
            T[j][i] = X[i][j];
        }
    }
}

void net_update_rule(float X[P][N], float T[N][P], float eps[N][1]){
    float res[P][1];

    // matmul
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < N; j++) {
            res[i][0] += X[i][j]*eps[j][0];
        }
    }

    net_scalarmul(res, BETA);
    net_softmax(res);
    
    //matmul
    for (int i = 0; i < N; i++) {
        eps[i][0] = 0;
        for (int j = 0; j < P; j++) {
            eps[i][0] += T[i][j]*res[j][0];
        }
    }

}

int net_equals(float arr1[N][1], float arr2[N][1]) {
    for (int i = 0; i < N; i++) {
        if (arr1[i][0] != arr2[i][0]) return 0;
    }

    return 1;
}

void net_copy(float arr1[N][1], float arr2[N][1]) {
    for (int i = 0; i < N; i++) {
        arr1[i][0] = arr2[i][0];
    }
}

void net_converge(float X[P][N], float eps[N][1]) {
    float T[N][P];   
    net_transpose(X, T);

    float pre[N][1];
    for (int i = 0; i < N; i++) pre[i][0] = 0;
    

    while (!net_equals(pre, eps)) {
        net_copy(pre, eps);
        net_update_rule(X, T, eps);
    }
}
