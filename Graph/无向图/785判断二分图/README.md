### [785. 判断二分图](https://leetcode-cn.com/problems/is-graph-bipartite/)

给定一个无向图graph，当这个图为二分图时返回true。

如果我们能将一个图的节点集合分割成两个独立的子集A和B，并使图中的每一条边的两个节点一个来自A集合，一个来自B集合，我们就将这个图称为二分图。

graph将会以邻接表方式给出，graph[i]表示图中与节点i相连的所有节点。每个节点都是一个在0到graph.length-1之间的整数。这图中没有自环和平行边： graph[i] 中不存在i，并且graph[i]中没有重复的值。

**示例 1:**

```
输入: [[1,3], [0,2], [1,3], [0,2]]
输出: true
解释: 
无向图如下:
0----1
|    |
|    |
3----2
我们可以将节点分成两组: {0, 2} 和 {1, 3}。
```

此题需要判定，任意一组无向边（u, v），u包含的节点v集合中不能含有u所在集合的节点。

概括来说，任意一组(u,v) u 和 v所包含的节点都不相同

可以用一个color数组来标记当前u所在的集合的颜色，遍历v其所在集合颜色所有被标记的颜色要与u相反，否则return false;

迭代：

```c++
bool isBipartite(vector<vector<int>>& graph) {
         vector<int> col(graph.size());
         queue<int> q;
         for(int i = 0; i< graph.size(); ++i)
         {
             if(col[i]!= 0) continue;
             q.push(i);
             col[i] = 1;
             while(!q.empty())
             {
                 int n = q.front();
                 q.pop();
                 for(auto id : graph[n])
                 {
                     if(col[id] == col[n]) return false;
                     if(col[id] == 0)
                     {
                         q.push(id);
                         col[id] = -col[n];
                     }  
                 }
             }
         }
         return true;
     }
```

递归： 

```c++
     vector<int> col;
     bool isBipartite(vector<vector<int>>& graph) {
         int len = graph.size();
         col = vector<int>(len);
         for(int i = 0; i < len; ++i)
         {
             if(col[i]!=0) continue;
             if(!col[i] && !dfs(graph,i,1)) return false;
         }
         return true;
     }
     bool dfs(vector<vector<int>>& graph, int pos, int color)
     {
         col[pos] = color;
         for(auto n : graph[pos])
         {
            if(col[pos] == col[n])return false;
            if(!col[n] && !dfs(graph, n, -color)) return false;
         }
         return true;
     }
```

