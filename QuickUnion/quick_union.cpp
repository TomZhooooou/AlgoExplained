//
// Created by Tom on 10/08/2020.
//

#include "quick_union.h"
#include <bits/stdc++.h>
class QuickUnionUF
{
private:
    vector<int> id;

public:
    QuickUnionUF(int N) //初始化
    {
        id = new vector<int>(N);
        for(int i = 0; i< N; i++) id[i] = i; // 先将各对象id指向自己
    }
    int root(int i ){ // 找到root并返回
        while(i!= id[i])
        {
            id[i] = id[id[i]]; // 只通过这个就能 变相实现
            i = id[i];
        }
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
        id[i] = j; // 直接将p的root设置为q的root 实现连接
    }

};