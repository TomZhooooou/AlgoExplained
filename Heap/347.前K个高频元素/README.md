### [347. 前 K 个高频元素](https://leetcode-cn.com/problems/top-k-frequent-elements/)

给定一个非空的整数数组，返回其中出现频率前 **k** 高的元素。

示例1:

```
输入: nums = [1,1,1,2,2,3], k = 2
输出: [1,2]
```

复杂度限制 nlogn

此题最开始想到的就是用堆来解决，维护大小为k的符合条件的元素。

关于维持大顶堆还是小顶堆，因为需要频率最大，因此堆顶需要是k个最大中的最小值，这样才方便更新。选小顶堆。

采用pair记录元素与其对应的频率，pair在priority queue中会默认比较第一个元素`first`。

```c++
typedef pair<int,int> pii; //缩写
struct cmp{
    bool operator() (const pii &p1,const pii &p2)
    {
        return p1.second > p2.second; //堆顶元素最小
    }
};
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        priority_queue<pii,vector<pii>, cmp> q; 
        unordered_map<int, int>m;
        vector<int> res(k);
        for(const auto& n : nums)
        {
            m[n]++;
        }
        for(auto& map : m)
        {
            q.push(make_pair(map.first, map.second));
            if(q.size() > k) q.pop(); 
        }
        for(int i = k-1; !q.empty(); i--) //k-1是为了满足频率从大到小排列
        {
            res[i] = q.top().first;
            q.pop();
        }
        return res;
    }
};
```

方法二：采用排序

```c++
typedef pair<int,int> pii;
struct cmp{
    bool operator() (const pii &p1,const pii &p2)
    {
        return p1.second > p2.second;
    }
};
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> m;
        vector<int> res(k);
        for(const auto& n : nums)
        {
            m[n]++;
        }
        vector<pii> pairs(m.begin(), m.end());
        sort(pairs.begin(),pairs.end(), cmp());//cmp要是一个value，从左到右依次递减
        for(int i = 0; i< k; i++)
        {
            res[i] = pairs[i].first;
        }
        return res;
    }
};
```

方法三：桶排序

用桶来记录数的出现频率，从高到低。

再从高到低遍历取出元素，放入答案

```c++
vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int>m;
        vector<int> res;
        for(const auto& n : nums)
        {
            m[n]++;
        }
        vector<vector<int>> buckets(nums.size()+1);
        for(auto iter = m.begin(); iter!=m.end(); iter++)
        {
            buckets[iter->second].push_back(iter->first);
        }
        for(int i = nums.size(); i>=0 ; i--)
        {
            if(buckets[i].size() > 0)
            {
                for(int j = 0; j < buckets[i].size(); j++)
                {
                    res.push_back(buckets.at(i).at(j));
                    k--;
                    if(k == 0) return res;
                }
            }
        }
        return res;
    }
```

