## STL 容器迭代器坑

### erase() 函数

不论是使用关联式容器还是序列式容器，使用 `iterator erase(const_iterator __position)` 成员函数时应注意写法。因为一旦 erase 掉，该迭代器就会失效，不能继续进行操作。下面示范了错误样例：

```cpp
map<int,int> MyMap;
//插入操作
for(map<int,int>::iterator it=MyMap.begin();it!=MyMap.end();it++)
	if(it->second%2) MyMap.erase(it);
```

直接会 RE。有两种改法：
**1.**
```cpp
//method one
for(map<int,int>::iterator it=MyMap.begin();it!=MyMap.end();it++)
	if(it->second%2) it=MyMap.erase(it);
```

这种改法基于 `erase()` 函数的返回值——返回被删除的下一个迭代器。仅 c++11 以上可用。c++11 以下无返回值。定义如下（这个是 map 的，其它的也差不多）：

```cpp
#if __cplusplus >= 201103L
      // _GLIBCXX_RESOLVE_LIB_DEFECTS
      // DR 130. Associative erase should return an iterator.
      /**
       *  @brief Erases an element from a %map.
       *  @param  __position  An iterator pointing to the element to be erased.
       *  @return An iterator pointing to the element immediately following
       *          @a position prior to the element being erased. If no such 
       *          element exists, end() is returned.
       *
       *  This function erases an element, pointed to by the given
       *  iterator, from a %map.  Note that this function only erases
       *  the element, and that if the element is itself a pointer,
       *  the pointed-to memory is not touched in any way.  Managing
       *  the pointer is the user's responsibility.
       */
	//这段话是说：删除传入的迭代器对应的元素（但如果元素是指针就什么都不会做。管理指针是用户的职责），返回被删除元素的下一个元素的迭代器。
      iterator
      erase(const_iterator __position)
      { return _M_t.erase(__position); }

      // LWG 2059
      _GLIBCXX_ABI_TAG_CXX11//这个是来判断兼容哪个版本的
      iterator
      erase(iterator __position)
      { return _M_t.erase(__position); }
#else
      /**
       *  @brief Erases an element from a %map.
       *  @param  __position  An iterator pointing to the element to be erased.
       *
       *  This function erases an element, pointed to by the given
       *  iterator, from a %map.  Note that this function only erases
       *  the element, and that if the element is itself a pointer,
       *  the pointed-to memory is not touched in any way.  Managing
       *  the pointer is the user's responsibility.
       */
      void//如果版本低了就没有返回值
      erase(iterator __position)
      { _M_t.erase(__position); }
#endif
```

------------
**2.**
```cpp
//method two
for(map<int,int>::iterator it=MyMap.begin();it!=MyMap.end();it++)
	if(it->second%2) MyMap.erase(it++);
```

这种改法新老版本都可以。

#### 范围删除

在研究的时候发现另一个成员函数 `iterator erase(const_iterator __first, const_iterator __last)`，可以范围删除元素。

### 迭代器的访问

对于序列式容器，我们可以直接修改迭代器对应元素。比如：

```cpp
vector<int>vec({1,2,3,4,5});
vector<int>::iterator it;
for(it=vec.begin();it!=vec.end();it++)printf("%d ",*it);
(*--it)=1;putchar('\n');
for(it=vec.begin();it!=vec.end();it++)printf("%d ",*it);
```

输出是：
```cpp
1 2 3 4 5
1 2 3 4 1
```

但是对于关联式容器，这是不合法的。比如：

```cpp
map<int,int>mp;
mp[1]=2,mp[2]=3;
map<int,int>::iterator it;
for(it=mp.begin();it!=mp.end();it++)printf("%d %d\n",it->first,it->second);
(--it)->first=3;putchar('\n');
for(it=mp.begin();it!=mp.end();it++)printf("%d %d\n",it->first,it->second);
```

编译器会报错，它会说 `(--it)->first` 是 read-only member。这很好理解：关联式容器是基于一定规律的，如果修改了就会打破规律！真要修改，我们只能先把这个元素 erase 掉再插入一个进去。比如：

```cpp
map<int,int>mp;
mp[1]=2,mp[2]=3;
map<int,int>::iterator it;
for(it=mp.begin();it!=mp.end();it++)printf("%d %d\n",it->first,it->second);
mp.erase(--it);mp.insert(make_pair(3,3));
putchar('\n');
for(it=mp.begin();it!=mp.end();it++)printf("%d %d\n",it->first,it->second);
```

这个在 map 上表现不明显，但是在 set 的情形下很有用。当然也有特殊情形：map 的第二关键字可以改，它不是 read-only member。