#include <iostream>
#include <windows.h>
#include <stdlib.h>
using namespace std;

const int SM = 16;  
const int N = 1024*2; // 测试矩阵维度
double A[N][N];
double B[N][N];
double C[N][N];

void init() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            A[i][j] = (i + j) * 0.1;
            B[i][j] = (i - j) * 0.1;
        }
    }
}

// 原始矩阵乘法（列访问不友好）
void matrixMulNaive() {
    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            double sum = 0;
            for (int k = 0; k < N; ++k) {
                sum += A[i][k] * B[k][j]; // B的列访问
            }
            C[i][j] = sum;
        }
    }

    QueryPerformanceCounter(&end);
    cout << "Naive Time: "
        << (end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart
        << "ms" << endl;
}

// 分块优化版本
void matrixMulBlocked() {
    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    const int BLOCK = SM; // 分块大小
    for (int ii = 0; ii < N; ii += BLOCK) {
        for (int jj = 0; jj < N; jj += BLOCK) {
            for (int kk = 0; kk < N; kk += BLOCK) {
                // 处理当前分块
                int i_end = min(ii + BLOCK, N);
                int j_end = min(jj + BLOCK, N);
                int k_end = min(kk + BLOCK, N);

                for (int i = ii; i < i_end; ++i) {
                    for (int k = kk; k < k_end; ++k) {
                        double a = A[i][k];
                        for (int j = jj; j < j_end; ++j) {
                            C[i][j] += a * B[k][j]; // B按列访问但局部化
                        }
                    }
                }
            }
        }
    }

    QueryPerformanceCounter(&end);
    cout << "Blocked Time: "
        << (end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart
        << "ms" << endl;
}

int main() {
    init();
    matrixMulNaive();
    matrixMulBlocked();
    return 0;
}