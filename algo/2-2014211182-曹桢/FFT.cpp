#include <complex>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
using namespace std ;
typedef complex<double> C ;
const int maxn = 1e5 + 5 ;
const double pi = acos(-1.0) ;

C a[maxn<<1] , b[maxn<<1] ;
char s[maxn] , t[maxn] ;
int ans[maxn<<1] ;

void change( C y[] , int len ) // 反转变换
{
    for( int i = 1 , j = len>>1 ; i+1 < len ; i++ )
    {
        if( i < j ) swap(y[i],y[j]) ;
        int k = len>>1 ;
        while( j >= k )
        {
            j -= k ;
            k >>= 1 ;
        }
        if( j < k ) j += k ;
    }
}

void FFT( C y[] , int len , int on ) // Radix-2算法 O(nlogn)
{
    change(y,len) ;
    for( int i = 2 ; i <= len ; i <<= 1 )
    {
        C wn(cos(-on*2*pi/i),sin(-on*2*pi/i)) ;
        for( int j = 0 ; j < len ; j += i )
        {
            C w(1,0) ; int o = i>>1 ;
            for( int k = j ; k < j+o ; k++ )
            {
                C u = y[k] , t = w*y[k+o] ;
                y[k] = u+t ;
                y[k+o] = u-t ;
                w *= wn ;
            }
        }
    }
    if( on == -1 )
    {
        for( int i = 0 ; i < len ; i++ ) y[i] /= len ;
    }
}

void show( C y[] , int len )
{
    for( int i = 0 ; i < len ; i++ ) cout << y[i] << ' ' ;
}

int main()
{
    while( ~scanf( "%s%s" , s , t ) )
    {
        int n = strlen(s) , m = strlen(t) , len = 1 ;
        while( len < n<<1 || len < m<<1 ) len <<= 1 ;
        // 计算长度 ，为2^n且不小于原序列长度2倍
        for( int i = 0 ; i < n ; i++ ) a[i] = C(s[n-i-1]-'0',0) ;
        for( int i = n ; i < len ; i++ ) a[i] = C(0,0) ;
        for( int i = 0 ; i < m ; i++ ) b[i] = C(t[m-i-1]-'0',0) ;
        for( int i = m ; i < len ; i++ ) b[i] = C(0,0) ;
        // 转换为复数，不足补0
        FFT(a,len,1) ;
        FFT(b,len,1) ;                                    // 快速傅里叶变换
        for( int i = 0 ; i < len ; i++ ) a[i] *= b[i] ;   // 时域卷积，频域乘积
        FFT(a,len,-1) ;                                   // 傅里叶反变换
        // 计算FFT
        for( int i = 0 ; i < len ; i++ ) ans[i] = int(a[i].real()+0.5) ;
        for( int i = 0 ; i < len ; i++ )
        {
            ans[i+1] += ans[i] / 10 ;
            ans[i] %= 10 ;
        }
        int p = n+m-1 ;
        while( ans[p] <= 0 && p > 0 ) p-- ;
        for( int i = p ; i >= 0 ; i-- ) putchar(ans[i]+'0') ;
        putchar('\n') ;
        // 转换为实数并输出
    }
    return 0 ;
}

