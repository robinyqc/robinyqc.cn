### 期望小 trick

若随机变量 $x$ 的取值范围是 $[1,m]$，那么：
$$
\begin{align}
E(x) &= \sum _{i=1}^m i\cdot P(x=i) \\
	 &= \sum_{i=1}^m\sum_{j=1}^m\ [j\leq i]\ P(x=i) \\
	 &= \sum_{j=1}^m\sum_{i=1}^m\ [j\leq i]\ P(x=i) \\
	 &= \sum_{j=1}^m\sum_{i=j}^m\ P(x=i)
\end{align}
$$
因为：
$$
\sum_{i=1}^n P(A_i)=P(\bigcup_{i=1}^n {A_i})
$$
那么：
$$
\bigg(\sum _{i=j}^m P(x=i)\bigg)=P(x\geq j)
$$
因而：
$$
\begin{align}
E(x) &= \sum_{j=1}^m\sum_{i=j}^m\ P(x=i) \\ 
	 &= \sum_{j=1}^m P(x\geq j) \\
	 &= \sum_{i=1}^m P(x\geq i)
\end{align}
$$
