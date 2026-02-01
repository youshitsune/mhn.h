#include <math.h>

#define to_pointer(arr) &arr[0][0]

typedef struct{
    int p;
    int n;
    float beta;
    float *X;
    float *eps;
} Net;

Net net_init(int p, int n, float beta, float *X);
void net_update_rule(Net net);
void net_converge(Net net, float* eps);

// Helper functions
void net_softmax(float *arr, int p);
void net_scalarmul(float *arr, int n, float v);
static inline void net_copy(float *arr1, float *arr2, int n);
static inline int net_equals(float *arr1, float *arr2, int n);


Net net_init(int p, int n, float beta, float *X) {
    Net net = {
        .p = p,
        .n = n,
        .beta = beta,
        .X = X,
    };
    
    return net;
}

void net_softmax(float *arr, int p) {
    float mx = arr[0];
    for (int i = 1; i < p; i++) {
        if (mx < arr[i]) mx = arr[i];
    }

    float sum = 0;
    for (int i = 0; i < p; i++) {
        arr[i] = exp(arr[i]-mx);
        sum += arr[i];
    }

    for (int i = 0; i < p; i++) {
        arr[i] /= sum;
    }
}

void net_scalarmul(float *arr, int n, float v) {
    for (int i = 0; i < n; i++) {
        arr[i] *= v;
    }
}

void net_update_rule(Net net){
    float res[net.p];

    // matmul
    for (int i = 0; i < net.p; i++) {
        for (int j = 0; j < net.n; j++) {
            res[i] += net.X[i*net.n+j]*net.eps[j];
        }
    }

    net_scalarmul(res, net.p, net.beta);
    net_softmax(res, net.p);
    
    //matmul
    for (int i = 0; i < net.n; i++) {
        net.eps[i] = 0;
        for (int j = 0; j < net.p; j++) {
            net.eps[i] += net.X[j*net.n+i]*res[j];
        }
    }
}

static inline int net_equals(float *arr1, float *arr2, int n) {
    for (int i = 0; i < n; i++) {
        if (arr1[i] != arr2[i]) return 0;
    }

    return 1;
}

static inline void net_copy(float *arr1, float *arr2, int n) {
    for (int i = 0; i < n; i++) {
        arr1[i] = arr2[i];
    }
}

void net_converge(Net net, float* eps) {
    net.eps = eps;
    float pre[net.n];
    for (int i = 0; i < net.n; i++) pre[i] = 0;
    
    while (!net_equals(pre, net.eps, net.n)) {
        net_copy(pre, net.eps, net.n);
        net_update_rule(net);
    }
}
