#include <math.h>
#include <stdio.h>

// double pr[n]	存放n个采样输入的实部，返回离散傅里叶变换的摸
// double pi[n]	存放n个采样输入的虚部
// double fr[n]	返回离散傅里叶变换的n个实部
// double fi[n]	返回离散傅里叶变换的n个虚部
// int n	采样点数
// int k	满足n = 2 k n=2^kn=2 k
// void kfft()	过程
void kfft(double *pr, double *pi, int n, int k, double *fr, double *fi)
{
    int it, m, is, i, j, nv, l0;
    double p, q, s, vr, vi, poddr, poddi;
    for (it = 0; it <= n - 1; it++) //将pr[0]和pi[0]循环赋值给fr[]和fi[]
    {
        m = it;
        is = 0;
        for (i = 0; i <= k - 1; i++)
        {
            j = m / 2;
            is = 2 * is + (m - 2 * j);
            m = j;
        }
        fr[it] = pr[is];
        fi[it] = pi[is];
    }
    pr[0] = 1.0;
    pi[0] = 0.0;
    p = 6.283185306 / (1.0 * n);
    pr[1] = cos(p); //将w=e^-j2pi/n用欧拉公式表示
    pi[1] = -sin(p);

    for (i = 2; i <= n - 1; i++) //计算pr[]
    {
        p = pr[i - 1] * pr[1];
        q = pi[i - 1] * pi[1];
        s = (pr[i - 1] + pi[i - 1]) * (pr[1] + pi[1]);
        pr[i] = p - q;
        pi[i] = s - p - q;
    }
    for (it = 0; it <= n - 2; it = it + 2)
    {
        vr = fr[it];
        vi = fi[it];
        fr[it] = vr + fr[it + 1];
        fi[it] = vi + fi[it + 1];
        fr[it + 1] = vr - fr[it + 1];
        fi[it + 1] = vi - fi[it + 1];
    }
    m = n / 2;
    nv = 2;
    for (l0 = k - 2; l0 >= 0; l0--) //蝴蝶操作
    {
        m = m / 2;
        nv = 2 * nv;
        for (it = 0; it <= (m - 1) * nv; it = it + nv)
            for (j = 0; j <= (nv / 2) - 1; j++)
            {
                p = pr[m * j] * fr[it + j + nv / 2];
                q = pi[m * j] * fi[it + j + nv / 2];
                s = pr[m * j] + pi[m * j];
                s = s * (fr[it + j + nv / 2] + fi[it + j + nv / 2]);
                poddr = p - q;
                poddi = s - p - q;
                fr[it + j + nv / 2] = fr[it + j] - poddr;
                fi[it + j + nv / 2] = fi[it + j] - poddi;
                fr[it + j] = fr[it + j] + poddr;
                fi[it + j] = fi[it + j] + poddi;
            }
    }
    for (i = 0; i <= n - 1; i++)
    {
        pr[i] = sqrt(fr[i] * fr[i] + fi[i] * fi[i]); //幅值计算
    }
    return;
}

#if 0

#define NPT 256
#define PI 3.1415926535
#define PI2 (PI*2)
int lBufInArray[NPT];
#define Fs 44800
/******************************************************************
函数名称:InitBufInArray()
函数功能:模拟采样数据，采样数据中包含3种频率正弦波(350Hz，8400Hz，18725Hz)
参数说明:
备    注:在lBufInArray数组中，每个数据的高16位存储采样数据的实部，
          低16位存储采样数据的虚部(总是为0)
作　　者:博客园 依旧淡然（http://www.cnblogs.com/menlsh/）
*******************************************************************/
void InitBufInArray()
{
    unsigned short i;
    float fx;
    for(i=0; i<NPT; i++)
    {
        fx = 1500 * sin(PI2 * i * 350.0 / Fs) +
             2700 * sin(PI2 * i * 8400.0 / Fs) +
             4000 * sin(PI2 * i * 18725.0 / Fs);
        lBufInArray[i] = ((signed short)fx) << 16;
    }
}


int main()
{
    int i, j;
    double pr[32], pi[32], fr[32], fi[32], t[32];
    for (i = 0; i <= 31; i++) //生成输入信号
    {
        t[i] = i * 0.001;
        pr[i] = 1.2 + 2.7 * cos(2 * PI * 33 * t[i]) + 5 * cos(2 * PI * 200 * t[i] + PI / 2);
        pi[i] = 0.0;
    }
    for (i = 0; i < 32; i++)
    {
        printf("pi: %d\t%lf\n", i, pi[i]); //输出结果
    }
    for (i = 0; i < 32; i++)
    {
        printf("pr: %d\t%lf\n", i, pr[i]); //输出结果
    }
    kfft(pr, pi, 32, 6, fr, fi); //调用FFT函数
    for (i = 0; i < 32; i++)
    {
        printf("%d\t%lf\n", i, pr[i]); //输出结果
    }


    
    return 0;
}
#endif