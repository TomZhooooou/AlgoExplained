### [133. 克隆图](https://leetcode-cn.com/problems/clone-graph/)

给你无向 **[连通](https://baike.baidu.com/item/连通图/6460995?fr=aladdin)** 图中一个节点的引用，请你返回该图的 [**深拷贝**](https://baike.baidu.com/item/深拷贝/22785317?fr=aladdin)（克隆）。

图中的每个节点都包含它的值 `val`（`int`） 和其邻居的列表（`list[Node]`）。

```
class Node {
    public int val;
    public List<Node> neighbors;
}
```

提示：

节点数不超过 100 。
每个节点值 Node.val 都是唯一的，1 <= Node.val <= 100。
无向图是一个简单图，这意味着图中没有重复的边，也没有自环。
由于图是无向的，如果节点 p 是节点 q 的邻居，那么节点 q 也必须是节点 p 的邻居。
图是连通图，你可以从给定节点访问到所有节点。

示例1:

<img src="https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/02/01/133_clone_graph_question.png" alt="preview" style="zoom:20%;" />

````
输入：adjList = [[2,4],[1,3],[2,4],[1,3]]
输出：[[2,4],[1,3],[2,4],[1,3]]
解释：
图中有 4 个节点。
节点 1 的值是 1，它有两个邻居：节点 2 和 4 。
节点 2 的值是 2，它有两个邻居：节点 1 和 3 。
节点 3 的值是 3，它有两个邻居：节点 2 和 4 。
节点 4 的值是 4，它有两个邻居：节点 1 和 3 。
````

要深度拷贝，则需要遍历每个节点。可以采用dfs/bfs遍历

#### 递归：

```c++
Node* visited[101];
Node* cloneGraph(Node* node) {
        if(!node) return node;//若节点不存在直接返回本身
        if(visited[node->val]) return visited[node->val]; //如果已经遍历过，直接返回已经靠背过的节点
        Node* root= new Node(node->val);
        visited[node->val] = root; //将节点设置为已遍历
        for(int i = 0; i< node->neighbors.size();i++)
        {
            //将本root的neighbors添加上
            root->neighbors.push_back(cloneGraph(node->neighbors[i]));
        }
        return root;
    }
```

#### 迭代：

bfs

```c++
Node* cloneGraph(Node* node)
{
  if(!node) return node;
  unordered_map<int, Node*> m;//使用map记录，节点编号，以及对应的复制节点
  queue<Node*> q;
  q.push(node);
  Node* res= new Node(node->val);
  m[node->val] = res;
  while(!q.empty())
  {
    Node* point = q.front();
    q.pop();
    Node* root= m[point->val]; //新的节点
    if(!res) res= root;
    for(auto p : point->neighbors)
    {
      if(!m[p->val])
      {
        q.push(p);
        m[p->val] =  new Node(p->val); //如果没遍历过。将新的节点添加到map中
      }
      root->neighbors.push_back(m[p->val]);//将本轮的root节点neighbors进行填充
    }
  }
  return res;
}
```

