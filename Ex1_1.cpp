#include <iostream>
#include <windows.h>
#include <stdlib.h>

using namespace std;

const int N = 1024*16;

double b[N][N];
double a[N], sum[N];

// ��ʼ�����������
void init() {
    
    for (int i = 0; i < N; ++i) {
        a[i] = i; 
        for (int j = 0; j < N; ++j) {
            b[i][j] = i + j; 
        }
    }
}

// ƽ���㷨
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

// �Ż��㷨�����з��ʾ���Ԫ��
double optimizedAlgorithm() {
    long long freq, head, tail;

    QueryPerformanceFrequency((LARGE_INTEGER*)&freq); 
    QueryPerformanceCounter((LARGE_INTEGER*)&head);  

    for (int i = 0; i < N; ++i) {
        sum[i] = 0.0; // ��ʼ�� sum[i]
    }
    for (int j = 0; j < N; ++j) { // �����ȷ���
        for (int i = 0; i < N; ++i) {
            sum[i] += b[j][i] * a[j];
        }
    }

    QueryPerformanceCounter((LARGE_INTEGER*)&tail);  // ������ʱ
    
    return (tail - head) * 1000.0 / freq;
}

int main() {
    cout << "N=" << N << endl;
    
    double time=0.0;
    for (int i = 0; i < 10; i++)
    {// ����ƽ���㷨
        init();
        time += trivialAlgorithm();
    }
    cout << time/10 << endl;

    // �����Ż��㷨
    time = 0.0;
    for (int i = 0; i < 10; i++)
    {// ����ƽ���㷨
        init();
        time += optimizedAlgorithm();
    }
    cout << time/10 << endl;

    return 0;
}
