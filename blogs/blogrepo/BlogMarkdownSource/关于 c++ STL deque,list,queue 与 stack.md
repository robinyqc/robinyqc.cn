## 关于 c++ STL deque,list,queue 与 stack

~~不关你 vector 的事~~

今天看了一篇[博客](https://www.luogu.com.cn/blog/chen-zhe/ti-xie-b3656-mu-ban-shuang-duan-dui-lie-1-post "博客")，意识到应该写一篇记一记。

我们知道 STL deque 的初始内存极大，因此广为诟病。据说有不少人因为 deque 挂了。总之，当要求**大量**双端队列时，应避免写 deque，考虑用 STL list 或手写。但是如果只有**少量**双端队列，或者要求随机访问，应当使用 deque。因为一旦单个 list 开大了，deque 的效率和内存都碾压它。

通过 `sizeof()` 函数，我们可以得知一个 deque 和 一个 list 的大小。

```cpp
printf("%d %d",sizeof(deque<int>),sizeof(list<int>));
```
结果是：`80 16`。显然 list 好。**deque 在大量双端队列的情况下太容易炸了！**

但是如果单个开大了呢？我们用下面的两段代码测试：

```cpp
//deque
deque<int>d;
for(int i=1;i<=1e7;i++) l.push_back(1);
```

```cpp
//list
list<int>d;
for(int i=1;i<=1e7;i++) l.push_back(1);
```

第一段代码占用的内存远远小于第二段。不信可以自己测测。

然后来测用时，只用看 `push_back()` 就可以了。代码如下：

```cpp
#include<time.h>
#include<queue>
#include<stack>
#include<list>
#include<cstdio>
using namespace std;
#define C CLOCKS_PER_SEC
const int N=1e6;
list<int>l;
deque<int>d;
double dur;
clock_t start;
int main(){
	puts("push:");
	start=clock();
	for(int i=1;i<=N;i++) l.push_back(1);
	dur=clock()-start;
	printf("List's time is %lfs\n",dur/C);
	start=clock();
	for(int i=1;i<=N;i++) d.push_back(1);
	dur=clock()-start;
	printf("Deque's time is %lfs\n",dur/C);
	return 0;
}
```
我这里的输出是：
```cpp
push:
List's time is 0.086062s
Deque's time is 0.018839s
```
deque 还是碾压。

### 关于 queue 和 stack
------------

为什么题目中还有 queue 和 stack 呢？这就要从 STL queue 和 stack 的定义说起。以下是模板 queue 的定义：

```cpp 
template<typename _Tp, typename _Sequence = deque<_Tp> >
    class queue
```
然后是 stack:
```cpp 
template<typename _Tp, typename _Sequence = deque<_Tp> >
    class stack
```

我们发现这两个模板有两个参数，第一个代表储存的数据类型，第二个代表容器，**默认为 deque**。

所以在代表容器的那一块我们还可以填 ```list<int>```！实现的功能却没有变化！实际上，这也是为什么 queue 和 stack 没有迭代器的原因：STL list 是双向迭代器，deque 则是随机访问迭代器，类型不统一，没法做迭代器。

例如：`queue<int,list<int> >` 和 `stack<char,list<char> >` 都是合法的。

和 deque 与 list 的比较一样，当要求**大量**队列或者栈时，应避免写默认的，应该写成例如：`queue<int,list<int> > q[1000005]`。但是如果只有**少量**队列或栈，就该用默认参数。因为一旦单个 list 开大了，deque 的效率和内存都碾压它。