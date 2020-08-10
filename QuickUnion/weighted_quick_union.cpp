//
// Created by Tom on 10/08/2020.
//

#include "weighted_quick_union.h"
#include <bits/stdc++.h>

class QuickUnionUF
{
private:
    vector<int> id;
    vector<int> sz;

public:
    QuickUnionUF(int N) //初始化
    {
        id = new vector<int>(N);
        sz = new vector<int>(N, 1);//初始化一个size 数组储存每个对象的🌲大小
        for(int i = 0; i< N; i++)
        {
            id[i] = i; // 先将各对象id指向自己
        }
    }
    int root(int i ){ // 找到root并返回
        while(i!= id[i]) i = id[i];
        return i;
    }
    bool connected(int p, int q) //判断是否同根
    {
        return root(p) == root(q);
    }
    void union(int p, int q)
    {
        int i = root(p);
        int j = root(q);
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

};