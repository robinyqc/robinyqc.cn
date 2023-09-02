# 闲谈 exCRT

我知道 exCRT 的步骤，但是没清楚为什么两个方程合并之后是模 lcm 的。

想了一下，没想明白。看了一下课件，tmd 真简单，记一下。

证明可能和解法有些不同。

有方程

$$
\left \{\begin {aligned}

&x\equiv a \pmod n\\
&x\equiv b \pmod m\\

\end{aligned}
\right.
$$

怎么合并。

设方程 $x\equiv a \pmod n$ 的通解是 $a+kn$。那么 $a+kn\equiv b\pmod m$，即 $kn\equiv b-a\pmod m$。设 $d=\gcd(n,m)$，根据 Bezout 定理我们知道这个方程有解当且仅当 $d\mid (b-a)$。

假设有解。那么 $\frac {kn}d \equiv \frac {b-a}d \pmod {\frac md}$。那么 $\frac {kn+a}d \equiv \frac bd \pmod {\frac md}$。尽管两边可能是小数，但反正根据运算法则它确实没有问题。那么就转成

$$
\left \{\begin {aligned}

&x\equiv a \pmod n\\
&\frac xd\equiv \frac bd \pmod {\frac md}\\

\end{aligned}
\right.
$$

结束了。 $\gcd(n,\frac md)=1$，根据 CRT 它在模 $n\cdot\frac md$ 下有唯一解。进一步的大家都会解了吧。