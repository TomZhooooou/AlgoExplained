#### 130. 被围绕的区域](https://leetcode-cn.com/problems/surrounded-regions/)

给定一个二维的矩阵，包含 `'X'` 和 `'O'`（**字母 O**）。

找到所有被 `'X'` 围绕的区域，并将这些区域里所有的 `'O'` 用 `'X'` 填充。

**示例:**

```
X X X X
X O O X
X X O X
X O X X
```

运行你的函数后，矩阵变为：

```
X X X X
X X X X
X X X X
X O X X
```

遇见这种题首先想到的 就是用dfs或bfs进行解决，但是直接找被包围的‘O’比较麻烦，因此可以逆向思维，寻找从边界开始连续连接的‘O’进行标记，未标记的则为被‘X’包围的字母

##### dfs递归做法:

深度优先遍历，递归：

```c++
class Solution {
  public:
  int rows, cols;
  void  dfs(vector<vector<char>>& board, int i , int j)
  {
    if(i>=0 && j>=0 && i<rows && j< cols && board[i][j] == 'O')
    {
      board[i][j] = '#';
      dfs(board, i-1, j);
      dfs(board, i+1, j);
      dfs(board, i, j-1);
      dfs(board, i, j+1);
    }
  }
  /* 方法2: 
  int directions[4][2] = {{-1, 0},{1, 0}, {0, 1}, {0, -1}};
  void  ddfs(vector<vector<char>>& board, int i , int j)
  {
    board[i][j] = '#';
    for(int k = 0; k< 4; k++)
    {

      int x = i+directions[k][0];
      int y = j+directions[k][1];
      if(x>=0 && y>=0 && x<rows && y< cols && board[x][y] == 'O')
      {
        board[x][y] = '#';
        ddfs(board, x, y);
      }
    }
    //  cout<<1<<endl;
  }
  */
  void solve(vector<vector<char>>& board) {
    int row = board.size();
    if(row == 0) return;
    int col = board[0].size();
    this->cols = col;
    this->rows = row;
    vector<vector<bool>> visited(row, vector<bool>(col, false));
    for(int i = 0; i< row; ++i)
      for(int j = 0; j < col; ++j)
      {
        if((i == row - 1|| j == col -1 || i == 0 || j == 0)  && board[i][j] =='O')
        {
          dfs(board, i, j);
        }
      }
    for(int i = 0; i< row; ++i)
      for(int j = 0; j < col ; ++j)
      {
        if(board[i][j] == '#')
        {
          board[i][j] ='O';
        }
        else if(board[i][j] == 'O')
        {
          board[i][j] = 'X';
        }

      }
  }
};
```

##### 非递归: bfs 直接创建一个queue

```c++
class Solution {
public:
int directions[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
    void solve(vector<vector<char>>& board) {
        int row = board.size();
        if(row == 0) return;
        int col = board[0].size();
        this->cols = col;
        this->rows = row;
        for(int i = 0; i< row; ++i)
            for(int j = 0; j < col; ++j)
            {
                if((i == row - 1|| j == col -1 || i == 0 || j == 0)  && board[i][j] =='O')
                {
                    queue<pair<int,int>> q; 
                    q.push(make_pair(i,j));
                    board[i][j] = '#';
                    while(!q.empty())
                    {   
                      auto pa = q.front();
                      //q.pop(); 两个位置均可
                      for(int k = 0; k< 4; k++)
                      {
                        int x = pa.first+directions[k][0];
                        int y = pa.second+directions[k][1];
                        if(x>=0 && y>=0 && x<row && y< col && board[x][y] == 'O')
                        {
                          board[x][y] = '#';
                          q.push(make_pair(x, y));
                        }
                      }
                        q.pop();
                      
                    }
                }
            }
        for(int i = 0; i< row; ++i)
            for(int j = 0; j < col ; ++j)
            {
                if(board[i][j] == 'O')board[i][j] ='X';
                if(board[i][j] == '#')board[i][j] = 'O';
            }
    }
};
```

##### 非递归，采用栈 dfs

用栈记录遍历的某个方向，直到没有新的坐标入栈。

将上一个拿出来，换方向继续遍历。

```c++
class Solution {
public:
    int rows, cols;
    void  dfs(vector<vector<char>>& board, int i , int j)
        {
          stack<pair<int,int>> s;
          s.push(make_pair(i, j));
          board[i][j] = '#';
          while(!s.empty())
          {
              auto p = s.top();
              if(p.first-1 >= 0 
                 && board[p.first-1][p.second] =='O' )
              {
                  board[p.first-1][p.second] = '#';
                  s.push(make_pair(p.first-1, p.second));
                  continue;
              }
              if(p.first+1 < rows 
                 && board[p.first+1][p.second] =='O' )
              {
                  board[p.first+1][p.second] = '#';
                  s.push(make_pair(p.first+1, p.second));
                  continue;
              }
              if(p.second-1 >= 0 
                 && board[p.first][p.second-1] =='O' )
              {
                  board[p.first][p.second - 1] = '#';
                  s.push(make_pair(p.first, p.second - 1));
                  continue;
              }
              if(p.second+1 < cols 
                 && board[p.first][p.second+1] =='O' )
              {
                  board[p.first][p.second+1]  = '#';
                  s.push(make_pair(p.first, p.second + 1));
                  continue;
              }
              s.pop();
          }
        }

    void solve(vector<vector<char>>& board) {
        int row = board.size();
        if(row == 0) return;
        int col = board[0].size();
        this->cols = col;
        this->rows = row;
        for(int i = 0; i< row; ++i)
            for(int j = 0; j < col; ++j)
            {
                if((i == row - 1|| j == col -1 || i == 0 || j == 0)  && board[i][j] =='O')
                {
                    dfs(board, i, j);
                }
            }
        for(int i = 0; i< row; ++i)
            for(int j = 0; j < col ; ++j)
            {
                if(board[i][j] == 'O')board[i][j] ='X';
                if(board[i][j] == '#')board[i][j] = 'O';
            }
    }
};
```

##### 非递归，bfs:

不用continue：每次往四个方向探索一次，而不是先探索完某个方向

```c++
class Solution {
public:
    int rows, cols;
    void  dfs(vector<vector<char>>& board, int i , int j)
        {
          stack<pair<int,int>> s;
          s.push(make_pair(i, j));
          board[i][j] = '#';
          while(!s.empty())
          {
              auto p = s.top();
              s.pop();
              if(p.first-1 >= 0 
                 && board[p.first-1][p.second] =='O' )
              {
                  board[p.first-1][p.second] = '#';
                  s.push(make_pair(p.first-1, p.second));
                  //continue;
              }
              if(p.first+1 < rows 
                 && board[p.first+1][p.second] =='O' )
              {
                  board[p.first+1][p.second] = '#';
                  s.push(make_pair(p.first+1, p.second));
                 // continue;
              }
              if(p.second-1 >= 0 
                 && board[p.first][p.second-1] =='O' )
              {
                  board[p.first][p.second - 1] = '#';
                  s.push(make_pair(p.first, p.second - 1));
                  //continue;
              }
              if(p.second+1 < cols 
                 && board[p.first][p.second+1] =='O' )
              {
                  board[p.first][p.second+1]  = '#';
                  s.push(make_pair(p.first, p.second + 1));
                  //continue;
              }
             
          }
        }

    void solve(vector<vector<char>>& board) {
        int row = board.size();
        if(row == 0) return;
        int col = board[0].size();
        this->cols = col;
        this->rows = row;
        for(int i = 0; i< row; ++i)
            for(int j = 0; j < col; ++j)
            {
                if((i == row - 1|| j == col -1 || i == 0 || j == 0)  && board[i][j] =='O')
                {
                    dfs(board, i, j);
                }
            }
        for(int i = 0; i< row; ++i)
            for(int j = 0; j < col ; ++j)
            {
                if(board[i][j] == 'O')board[i][j] ='X';
                if(board[i][j] == '#')board[i][j] = 'O';
            }
    }
};
```

#### 并查集:

C++ 实现的 weighted union find+ pass compression

将当前为‘O’的点与四周的’O‘相连接，如果最外层有‘O’则直接与新设置的一个root相连接(设置一个额外的值)

当前的board可以从0-cols*rows-1编号

**WQUPC**实现：

```c++
class UF{
    private:
    vector<int> sz;
    vector<int> id;
    public: 
    UF(int N)
    {
        sz.resize(N);
        id.resize(N);
        for(int i = 0; i< N; ++i){
            id[i] = i;
            sz[i] = 1;
        }   
    }
    int root(int q)
    {
        while(q != id[q])
        {
            id[q] = id[id[q]];
            q = id[q];
        }
        return q;
    }
    void unionf(int p, int q)
    {
        int i = root(p);
        int j = root(q);
        if (i == j) return; 
        if(sz[i] < sz[j])
        {
            id[i] = j; // 小的连接大的
            sz[j] += sz[i]; // 并更新sz[j]的大小
        }
        else
        {
            id[j] = i;
            sz[i] += sz[j];
        }
    }
    bool connected(int q, int p)
    {
        return root(p) == root(q);
    }
};

```

##### 接下来就是代码主体：

```c++
class Solution {
public:
    int cols;
    inline int node(int i, int j) {return i*cols + j;}
    void solve(vector<vector<char>>& board) {
        int row = board.size();
        if(row == 0) return;
        int col = board[0].size();
        this->cols = col;
        int size = row * col;
        UF *uf = new UF(size+1);
        for(int i = 0; i< row; ++i)
            for(int j = 0; j < col ; ++j)
            {
                if(board[i][j] == 'O')
                {
                if(i == row - 1 || j == col -1 || i == 0 || j == 0){
                    uf->unionf(node(i,j), size);
                    }
                else{
                    if(i > 0 && board[i-1][j] == 'O') 
                        uf->unionf(node(i-1,j), node(i,j));
                    if(i < row - 1 && board[i+1][j] == 'O' ) 
                        uf->unionf(node(i+1,j), node(i,j));
                    if(j > 0 && board[i][j-1] == 'O') 
                        uf->unionf(node(i,j-1), node(i,j));
                    if(j < col - 1 && board[i][j+1] == 'O') 
                        uf->unionf(node(i,j+1), node(i,j));
                    }
                }
            }
         for(int i = 0; i< row; ++i)
            for(int j = 0; j < col ; ++j)
            {
                if(board[i][j] == 'O' && !uf->connected(node(i,j), size))
                {
                    board[i][j] = 'X';
                }
                
            }
        delete uf; 
    }
};
```



