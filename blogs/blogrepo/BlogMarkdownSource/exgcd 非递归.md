# exgcd 非递归

exgcd 大家都会，gcd 的非递归写法（甚至 binary gcd,基于值域的 gcd）大家也都会。但为什么 exgcd 的非递归写法我没听说过呢？原来大家也都会，只是我孤陋寡闻罢了。

***

考虑方程组：

$$
\left\{
\begin{aligned}
ax+by=c\\
dx+ey=f
\end{aligned}
\right.
$$

或者说（以下都用这种方式表示）：

$$
\begin{pmatrix}
a&b&c\\
d&e&f\\
\end{pmatrix}
$$

用你最喜欢的消项法解方程：

$$
\begin{pmatrix}
a&b&c\\
d&e&f\\
\end{pmatrix}
\Longrightarrow
 \begin{pmatrix}
a&b&c\\
d-pa&e-pb&f-pc\\
\end{pmatrix}
$$

令 $p=\lfloor \dfrac fc\rfloor$，则：
$$
 \begin{pmatrix}
a&b&c\\
d-pa&e-pb&f-pc\\
\end{pmatrix}
=
 \begin{pmatrix}
a&b&c\\
d-pa&e-pb&c\bmod f\\
\end{pmatrix}
$$

发现常数项就是 gcd 的过程。那么对任一方程组 $\begin{pmatrix}
a&b&c\\
d&e&f\\
\end{pmatrix}
$，必可以通过若干变换变成 $
 \begin{pmatrix}
n&m&\gcd(c,f)\\
i&j& 0\\
\end{pmatrix}
$。

***

那么对应 exgcd 的过程就是：

原问题：求解 $ax+by=\gcd(a,b)$。

我们把 $a,b$ 当成主元。初始方程：
$
\begin{pmatrix}
1&0&a\\
0&1& b\\
\end{pmatrix}
$

根据上面的变换方式，必能得到等价矩阵 $
 \begin{pmatrix}
n&m&\gcd(a,b)\\
i&j& 0\\
\end{pmatrix}
$。就解出来了，因为矩阵的第一个行向量，就是表示的 $na+mb=\gcd(a,b)$。答案就是 $x=n,y=m$。

***
代码：

```cpp
int exgcd(int a,int b,int &x,int &y) {
    x=1,y=0;
    int n=0,m=1,t;
    while(b) {
        t=n,n=x-a/b*n,x=t;
        t=m,m=y-a/b*m,y=t;
        t=b,b=a%b,a=t;
    }
    return a;
}
```