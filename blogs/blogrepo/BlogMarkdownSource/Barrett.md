# Barrett

今天(2023/8/31)靠 Barrett 算法 $\log^2$ 效率超过了某些单 $\log$ 算法，也是赛时代码在 CWOI 上唯一过的一份，小记一下。

这个算法的目的是，在固定模数 $P$ 的情况下，对任意的 $a$，计算 $a\bmod P$。要比 `%` 更快。

这个算法的精髓是估算。首先问题可以转化成 $a-\left\lfloor \dfrac ap \right\rfloor \cdot p$。我们算 $\left\lfloor \dfrac ap \right\rfloor$ 有点慢，那我估算一个近似的是不是也可以？Barrett 算法就是要找一个数 $m$ 使得 $\dfrac m{2^k}\approx \dfrac 1p$，或者说 $m\approx \dfrac {2^k}p$。不妨令 $m=\left\lfloor \dfrac {2^k} p\right\rfloor$，那么 $m= \dfrac {2^k}p -e$，其中 $0\leq e<1$。

为什么是 $2^k$？因为方便算除法，直接右移即可。

现在用这个近似值估算：

$$
\left\lfloor \frac ap\right\rfloor\approx \left\lfloor\frac {am}{2^k}\right\rfloor= \left\lfloor a(\frac 1p -\frac e{2^k})\right\rfloor= \left\lfloor\frac ap -\frac {ae}{2^k}\right\rfloor
$$

假设这个 $k$ 足够大（比如 $k=10000$），那么有，

$$
\left\lfloor\frac ap -\frac {ae}{2^k}\right\rfloor=\left \{\begin{aligned}
&\left\lfloor \frac ap\right\rfloor ,&\frac ap -\frac {ae}{2^k}\geq\left\lfloor \frac ap\right\rfloor\\
&\left\lfloor \frac ap\right\rfloor-1,&\frac ap -\frac {ae}{2^k}<\left\lfloor \frac ap\right\rfloor
\end{aligned}
\right.
$$

最后算答案：

$$
a-p\left\lfloor\frac ap -\frac {ae}{2^k}\right\rfloor=\left \{\begin{aligned}
&a-p\left\lfloor \frac ap\right\rfloor=a\bmod p ,&\frac ap -\frac {ae}{2^k}\geq\left\lfloor \frac ap\right\rfloor\\
&a-p(\left\lfloor \frac ap\right\rfloor-1)=(a\bmod p)+p,&\frac ap -\frac {ae}{2^k}<\left\lfloor \frac ap\right\rfloor
\end{aligned}
\right.
$$

特判一下就好了，多做一个减法而已。

当然我们找不到那么大的 $k$，所以得找一个合理的。显然只要 $\dfrac {ae}{2^k}\leq 1$ 就可以了。通常 $P< 2^{31}$，所以，取 $k=64$ 就可以了。注意会爆 unsigned long long，所以中间要强转 __uint128_t（__uint128）。

### 代码

```cpp
#define ull unsigned long long 
#define ui128 __uint128_t
struct Barrett {
    ull d;
    ui128 m;
    Barrett(ull _d):d(_d),m((((ui128)(1)<<64)/d)) {}
    ull operator ()(ull a) {
        ull w=(m*a)>>64;
        w=a-w*d;
        if(w>=d) w-=d;
        return w;
    }
};
```