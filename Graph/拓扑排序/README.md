### [207. 课程表](https://leetcode-cn.com/problems/course-schedule/)

你这个学期必须选修 numCourse 门课程，记为 0 到 numCourse-1 。

在选修某些课程之前需要一些先修课程。 例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示他们：[0,1]

给定课程总量以及它们的先决条件，请你判断是否可能完成所有课程的学习？



示例1:

```
输入: 2, [[1,0]] 
输出: true
解释: 总共有 2 门课程。学习课程 1 之前，你需要完成课程 0。所以这是可能的。
```

示例2:

```
输入: 2, [[1,0],[0,1]]
输出: false
解释: 总共有 2 门课程。学习课程 1 之前，你需要先完成课程 0；并且学习课程 0 之前，你还应先完成课程 1。这是不可能的。
```

此题可简化为求图是否为有向无环图(DAG)

通过**拓扑排序**，对每个顶点，使得对于每条有向边(u,v)，均有u(在排序记录中)比v先出现。对v而言，只有当所有v的源点出现了，v才能出现。

通过前置条件列表`prerequisites`可以得到邻接表`near`降低算法时间复杂度。

#### 方法一：入度表(bfs)

设置一个入度`indegrees`

将所有入度为0的节点放进`queue`

当queue非空，依次从队首拿节点

将节点所有邻节点，入度降低1，表示从图中取出该节点。

当有新的节点`indegrees==0`则代表该节点前置都满足，将该节点放入`queue`

每当有节点满足num--，如果num==0 则表示所有的课程都满足。

```c++
bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
  queue<int> q;
  int indegrees[numCourses];
  int num = numCourses; //入度
  vector<vector<int>> near(numCourses);//邻接表
  memset(indegrees, 0 , sizeof(indegrees));
  for(int i = 0; i< prerequisites.size(); i++)
  {
    indegrees[prerequisites[i][0]]++;//初始化入度
    near[prerequisites[i][1]].push_back(prerequisites[i][0]);
  }
  for(int i = 0; i< numCourses; ++i)
  {
    if(indegrees[i]== 0) 
    {
      num--;
      q.push(i);//
    } 
  }
  while(!q.empty())
  {
    int n = q.front();
    q.pop();
    for(int i = 0; i< near[n].size(); i++)
    {
      indegrees[near[n][i]]--;
      if(indegrees[near[n][i]] == 0)  
      {
        q.push(near[n][i]);
        num--;//有入度为0，则‘取出’该节点，放入queue中
      }
    }
  }
  return num == 0;
}
```

#### 方法二：深度优先遍历

原理是通过 DFS 判断图中是否有环。

采用flag来标记某个节点是否已经被访问过 0表示没有，-1表示访问过，1表示正在当前访问中

每访问一个新的节点，将其设为1，如果在遍历过程中发现flag[j] == 1

说明当前节点有形成环，返回false

如果遇见-1则返回正确。

```c++
bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
  int flag[numCourses];
  memset(flag,0 , sizeof(flag));
  vector<vector<int>> adj(numCourses);
  for(auto p:prerequisites)
  {
    adj[p[1]].push_back(p[0]);
  }
  for(int i= 0; i< numCourses; ++i)
  {
    if(!dfs(adj, flag, i)) return false;
  }
  return true;
}
bool dfs(vector<vector<int>>& adj, int flag[], int j)
{
  if(flag[j] == 1) return false;
  if(flag[j] == -1) return true;
  flag[j] =1;
  for(int i = 0; i<  adj[j].size();++i)
  {
    if(!dfs(adj, flag, adj[j][i])) return false;
  }
  flag[j] = -1;
  return true;
}
```

