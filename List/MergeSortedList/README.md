### [剑指 Offer 25. 合并两个排序的链表](https://leetcode-cn.com/problems/he-bing-liang-ge-pai-xu-de-lian-biao-lcof/)

输入两个递增排序的链表，合并这两个链表并使新链表中的节点仍然是递增排序的。

示例1:

```
输入：1->2->4, 1->3->4
输出：1->1->2->3->4->4
```

base case 当任何一个链表到头，直接返回另外一个链表

递归：

```c++
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
  if(!l1) return l2;
  if(!l2) return l1;//base case
  if(l1->val < l2->val)//当右边的节点值大于左边 将左边的next与做节点的下一个与右节点继续比较 
    //1->2->2  3->3->4 
    //上面这种情况就需要迭代完所有的左链表直接将最后的2->next 指向 3 
  {
    l1->next = mergeTwoLists(l1->next, l2);
    return l1;
  }
  else 
  {
    l2->next =  mergeTwoLists(l1, l2->next);
    return l2;
  }
}
```

用一个dummy当头节点

每次将l1 与 l2中小一点的那个节点与dummy相连接

```c++
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
  ListNode* dummy = new ListNode(-1);//创建dummy头节点
  ListNode* cur = dummy;
  while(l1 && l2)
  { 
    // if(!l1) 
    // {
    //     cur->next = l2;
    //     break;
    // }
    // else if(!l2) 
    // {
    //     cur->next= l1;
    //     break;
    // }
    if(l1->val < l2->val) //cur 连接小的那个节点
    {
      cur->next = l1;
      l1 = l1->next;
    }
    else {
      cur->next= l2;
      l2= l2->next;
    }
    cur = cur->next;
  }
  cur->next = l1? l1 : l2; //l1, l2 中有一个为空的情况，或者其中一个更短，则直接将剩余部分进行连接
  return dummy->next;
}
```

