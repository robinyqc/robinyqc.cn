## 各类 OI 可用 priority_queue 评测

显然要用 g++ 编译器。

讲一下英文：

+ `std::priority_queue` - STL 的优先队列，不知道具体实现方法；
+ `__gnu_pbds::priority_queue` - PB_DS 库的优先队列，有以下几种实现：
	+ `binary_heap` - 二叉堆
   + `binomial_heap` - 二项堆
   + `pairing_heap` - 配对堆
   + `rc_binomial_heap` - 冗余计数二项堆
   + `thin_heap` - 除合并以外和斐波那契堆一样的堆

#### [实现代码](../BlogCodeSource/Priority_queue-Test/Priority_queue-Tester.cpp)

放在本机上编译运行就可以了。

在命令行里面运行你可以加一个参数，最终的评测结果会放到里面去。

这个程序是可以扩展的，说一下怎么用：

`PriorityQueueClock` 是一个模板类，有三个模板参数。第一个 `Tp` 填要维护的类型；第二个 `Cmp` 填堆里面用来比较维护元素的仿函数，要求这个仿函数比较的类型是 `Tp`；第三个 `RdMaker`填一个随机元素生成的仿函数。要求这个函数的返回值类型是 `Tp`。`Tp` 默认是 `int`，`Cmp` 默认是 `std::less<Tp>`，`RdMaker` 默认是代码中提供的 `RandomMaker`。

第 13 行定义了模板类 `RandomMaker`，它你可以仿照这个格式对它进行特化。代码中已经提供了对 `int` 和 `std::pair<int,int>` 的全特化。

你照着说的修改就可以评测了。不懂还可以私信我。