#include <iostream>
#include <windows.h>
#include <stdlib.h>

using namespace std;

const int N = 1024;
double a[N];
double sum;


void init() {
    for (int i = 0; i < N; ++i) {
        a[i] = i + 1; 
    }
}

// 链式累加
void chainAddition() {
    long long freq, head, tail;
    QueryPerformanceFrequency((LARGE_INTEGER*)&freq); 
    QueryPerformanceCounter((LARGE_INTEGER*)&head); 

    sum = 0;
    for (int i = 0; i < N; ++i) {
        sum += a[i];
    }

    QueryPerformanceCounter((LARGE_INTEGER*)&tail);  // 结束计时
    cout << "Chain Addition Time: "
        << (tail - head) * 1000.0 / freq << " ms, N: " << N << endl;
}

// 多链路式累加
void multiChainAddition() {
    long long freq, head, tail;
    QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
    QueryPerformanceCounter((LARGE_INTEGER*)&head); 

    double sum1 = 0, sum2 = 0;
    for (int i = 0; i < N; i += 2) {
        sum1 += a[i];
        if (i + 1 < N) {
            sum2 += a[i + 1];
        }
    }
    sum = sum1 + sum2;

    QueryPerformanceCounter((LARGE_INTEGER*)&tail); 
    cout << "Multi-Chain Addition Time: "
        << (tail - head) * 1000.0 / freq << " ms,  N: " << N << endl;
}

// 递归累加（方式1）
void recursiveAddition(int n) {
    if (n == 1) {
        sum = a[0];
        return;
    }
    for (int i = 0; i < n / 2; ++i) {
        a[i] += a[n - i - 1];
    }
    recursiveAddition(n / 2);
}

void recursiveAdditionWrapper() {
    long long freq, head, tail;
    QueryPerformanceFrequency((LARGE_INTEGER*)&freq); 
    QueryPerformanceCounter((LARGE_INTEGER*)&head);  

    recursiveAddition(N);

    QueryPerformanceCounter((LARGE_INTEGER*)&tail);
    cout << "Recursive Addition (Function) Time: "
        << (tail - head) * 1000.0 / freq << " ms, N: " << N << endl;
}

// 递归累加（方式2：二重循环）
void iterativeRecursiveAddition() {
    long long freq, head, tail;
    QueryPerformanceFrequency((LARGE_INTEGER*)&freq); 
    QueryPerformanceCounter((LARGE_INTEGER*)&head);  

    int m = N;
    while (m > 1) {
        for (int i = 0; i < m / 2; ++i) {
            a[i] = a[i * 2] + a[i * 2 + 1]; 
        }
        m /= 2;
    }
    sum = a[0];

    QueryPerformanceCounter((LARGE_INTEGER*)&tail);  
    cout << "Iterative Recursive Addition Time: "
        << (tail - head) * 1000.0 / freq << " ms, N: " << N << endl;
}
template<int N>
struct UnrollSum {
    static void compute(const double* a, double& sum) {
        UnrollSum<N - 1>::compute(a, sum);
        sum += a[N - 1]; // 计算最后一个元素
    }
};

// 递归终止条件
template<>
struct UnrollSum<0> {
    static void compute(const double* a, double& sum) {} // 空操作
};


int main() {

 
    //请您每次只执行一个函数，来获得它的缓存命中率
    init();
    chainAddition();
    init();
    multiChainAddition();

    init();
    iterativeRecursiveAddition();

    return 0;
}
