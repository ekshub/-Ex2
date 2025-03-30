#include <iostream>
#include <windows.h>
#include <stdlib.h>

using namespace std;

const int N = 1024*16;

double b[N][N];
double a[N], sum[N];

// 初始化矩阵和向量
void init() {
    
    for (int i = 0; i < N; ++i) {
        a[i] = i; 
        for (int j = 0; j < N; ++j) {
            b[i][j] = i + j; 
        }
    }
}

// 平凡算法
double trivialAlgorithm() {
    long long freq, head, tail;

    QueryPerformanceFrequency((LARGE_INTEGER*)&freq); 
    QueryPerformanceCounter((LARGE_INTEGER*)&head); 

    for (int i = 0; i < N; ++i) {
        sum[i] = 0.0; 
        for (int j = 0; j < N; ++j) {
            sum[i] += b[j][i] * a[j];
        }
    }

    QueryPerformanceCounter((LARGE_INTEGER*)&tail);
    
    return (tail - head) * 1000.0 / freq;
}

// 优化算法：逐行访问矩阵元素
double optimizedAlgorithm() {
    long long freq, head, tail;

    QueryPerformanceFrequency((LARGE_INTEGER*)&freq); 
    QueryPerformanceCounter((LARGE_INTEGER*)&head);  

    for (int i = 0; i < N; ++i) {
        sum[i] = 0.0; // 初始化 sum[i]
    }
    for (int j = 0; j < N; ++j) { // 行优先访问
        for (int i = 0; i < N; ++i) {
            sum[i] += b[j][i] * a[j];
        }
    }

    QueryPerformanceCounter((LARGE_INTEGER*)&tail);  // 结束计时
    
    return (tail - head) * 1000.0 / freq;
}

int main() {
    cout << "N=" << N << endl;
    
    double time=0.0;
    for (int i = 0; i < 10; i++)
    {// 测试平凡算法
        init();
        time += trivialAlgorithm();
    }
    cout << time/10 << endl;

    // 测试优化算法
    time = 0.0;
    for (int i = 0; i < 10; i++)
    {// 测试平凡算法
        init();
        time += optimizedAlgorithm();
    }
    cout << time/10 << endl;

    return 0;
}
