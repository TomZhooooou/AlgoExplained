滑动窗口一般需要两个指针对窗口进行维护。

从left = 0开始，如果遇见满足条件的，直接right++，直到不满足条件，通过left++来缩小窗口。

```c++
int left = 0, right = 0;
while (right < s.size()) {
    // 增大窗口
    window.add(s[right]);
    right++;
    while (window needs shrink) {
        // 缩小窗口
        window.remove(s[left]);
        left++;
    }
}
```

### [剑指 Offer 57 - II. 和为s的连续正数序列](https://leetcode-cn.com/problems/he-wei-sde-lian-xu-zheng-shu-xu-lie-lcof/)

输入一个正整数 target ，输出所有和为 target 的连续正整数序列（至少含有两个数）。

序列内的数字由小到大排列，不同序列按照首个数字从小到大排列。

**示例1:**

```
输入：target = 9
输出：[[2,3,4],[4,5]]
```

此题可以通过暴力方法直接求解，但是暴力方法重复相加了从指针到临界点的值

因此可以维护一个滑动窗口，当满足条件right++，当sum超过target则从left开始缩小windows

```c++
vector<vector<int>> findContinuousSequence(int target) {
        int sum = 0;//维护窗口的和
        int left = 1;//窗口的左边界
        vector<vector<int>> res;
        for(int i = 1; left<(target+1)/2;)//i从1开始至少包含两个数，并且left肯定小于等于target的一半
        {
            if(sum < target) //窗口满足条件，扩大
            {
                sum += i;
                i++;
            }
            else if(sum == target)
            {
                vector<int> tmp;
                for(int k = left; k < i; ++k)
                {
                    tmp.push_back(k);
                }
                res.push_back(tmp);
                sum -= left;//弹出左边一个元素，避免重复
                left++;
            }
            else // 缩小窗口
            {
                sum -= left;
                left++;
            }
        }
        return res;
    }
```

