//Fast Fourier Transform
//Here is an application: calculate sa*sb
#include <cmath>
#include <iostream>
using namespace std;

#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define lop(i, a, b) for (int i = (a); i < (b); i++)
#define dwn(i, a, b) for (int i = (a); i >= (b); i--)
#define ceil(a, b) (a + (b - 1)) / b
#define db double

constexpr int N = 4e6 + 10, M = 2e6 + 10;
const double PI = acos(-1), eps = 1e-8;

int T, n, m;

struct Complex
{
    double x, y;
    Complex operator+(const Complex& t) const
    {
        return { x + t.x, y + t.y };
    }
    Complex operator-(const Complex& t) const
    {
        return { x - t.x, y - t.y };
    }
    Complex operator*(const Complex& t) const
    {
        return { x * t.x - y * t.y, x * t.y + y * t.x };
    }

} a[N], b[N];

int rev[N], bit, tot, res[N];
void fft(Complex a[], int inv)
{
    for (int i = 0; i < tot; i++)
    {
        if (i < rev[i])
            swap(a[i], a[rev[i]]); //只需要交换一次就行了，交换两次等于没有换
    }
    for (int mid = 1; mid < tot; mid <<= 1)
    {
        auto w1 = Complex({ cos(PI / mid), inv * sin(PI / mid) });
        for (int i = 0; i < tot; i += mid * 2)
        {
            auto wk = Complex({ 1, 0 });                  //初始为w(0,mid),定义为w(k,mid)
            for (int j = 0; j < mid; j++, wk = wk * w1) //单位根递推式
            {
                auto x = a[i + j], y = wk * a[i + j + mid];
                a[i + j] = x + y, a[i + j + mid] = x - y;
            }
        }
    }
}

void workFFT(int n, int m)
{
    while ((1 << bit) < n + m + 1)
        bit++;
    tot = 1 << bit;
    for (int i = 0; i < tot; i++)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
    //递推(bit<<1)在bit之前，就已经被算出rev,最后一位是否为1
    fft(a, 1), fft(b, 1);
    for (int i = 0; i < tot; i++)
        a[i] = a[i] * b[i]; //点表示法直接运算
    fft(a, -1);//逆变换，点表示法转换为多项式表示法
    for (int i = 0; i <= n + m; i++)
        res[i] = (int)(a[i].x / tot + 0.5); //向上去整
}

// 一个大数看成多项式乘法，第i位 ai * 10 ^ i
int main()
{
    string sa, sb;
    cin >> sa >> sb;
    n = sa.length() - 1;
    m = sb.length() - 1;
    rep(i, 0, n)
        a[i].x = sa[n - i] - '0';
    rep(i, 0, m)
        b[i].x = sb[m - i] - '0';
    workFFT(n, m);
    int top = n + m;
    int i = 0;
    while (i <= top)
    {
        if (res[i] >= 10)
        {
            res[i + 1] += res[i] / 10;//进位
            top += i == top;
            res[i] %= 10;
        }
        i++;
    }
    while (!res[top] && top > 0) //去除掉最高位的0，同时确保答案=0的时候不会被抹除掉
        top--;
    dwn(i, top, 0)
        cout << res[i];
    return 0;
}
