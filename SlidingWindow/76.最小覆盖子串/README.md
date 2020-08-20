### [76. 最小覆盖子串](https://leetcode-cn.com/problems/minimum-window-substring/)

给你一个字符串 S、一个字符串 T 。请你设计一种算法，可以在 O(n) 的时间复杂度内，从字符串 S 里面找出：包含 T 所有字符的最小子串。

示例：

```
输入：S = "ADOBECODEBANC", T = "ABC"
输出："BANC"
```

此题可以采用滑动窗口解答，首先我们需要维护一个windows，这个windows里面应该含有T集合里面的所有元素。之后从左边开始缩小窗口，同时剔除windows里面元素，更新最短的字串的起始点，以及长度。若windows不满足，则退出，直到下一个满足。



```c++
string minWindow(string s, string t) {
  int left = 0, right = 0, minLeft;
  int dic[128];
  unordered_map<char,int> count;//记录windows里面元素的频率
  int winSize = 0; // winSize 记录我们的滑动窗口大小
  int res = INT_MAX;//初始化子字符串长度
  for(auto& w : t) //记录windows里面的字母 数量 
  {
    count[w]++;
  }
  memset(dic, 0, sizeof(dic));
  while(right < s.size())
  {
    if(count.find(s[right])!= count.end())
    {
      dic[s[right]]++;
      if(dic[s[right]] == count[s[right]])//如果满足则windows size++，注意必须等于，如果是大于等于可能会多加
      {
        winSize++;
      }

      while(winSize == count.size())//当windows满足的时候，就可以开始计算最短的长度了
      {
        if(count.find(s[left])!= count.end())//如果遇见了target中的字符，需要同步的从windows中取出
        {
          if(res > right - left + 1)
          {
            res = right - left +1;//记录短的长度
            minLeft = left;//最短的起始点
          }
          if(dic[s[left]] == count[s[left]] )//如果等于证明windows需要缩小
            winSize--;
          dic[s[left]]--;
        }
        left++;
      }
    }
    right++;
  }
  return res ==INT_MAX ? "" : s.substr(minLeft, res);//如果res没变化，证明没有符合条件的，因此应该
}
```

