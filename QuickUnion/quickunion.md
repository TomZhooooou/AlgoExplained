| algorithm   | initialise | union | find |
| ----------- | ---------- | ----- | ---- |
| quick-find  | N          | N     | 1    |
| quick-union | N          | N†    | N    |

​													worst case				† includes cost of finding roots

##### quick-find 

只储存元素共有的root，因此find复杂度为1。

tree形状会很平坦

##### quick-union (代码见quick_union.cpp)

find开销大

tree形状可能很高

#### 提高

##### weighted quick-union加权

将每个tree的大小记录下来，避免树过高

将小树与大树的root相连接，(大树在上面)

实现深度是总叶子树N的lg(N)大小(当包含x的树t1深度+1时，两个tree 的权重t2>=t1，因此tree最多double lg(N)次 e.p.:  1 + 1 = 2 double 1次 )

| algorithm   | initialise | union  | find  |
| ----------- | ---------- | ------ | ----- |
| weighted QU | N          | lg(N)+ | lg(N) |

Path compression：

每找一个object 将它的root 设置为它root的root，相当于连向它的grandfather node，这样能扁平化tree

##### M个union find ops + N个元素 复杂度：

| algorithm                      | worst-case time |
| ------------------------------ | --------------- |
| quick-find                     | MN              |
| quick-union                    | MN              |
| weighted QU                    | N + M log N     |
| QU + path compression          | N + M log N     |
| weighted QU + path compression | N + M lg* N     |