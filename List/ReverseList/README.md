### [206. 反转链表](https://leetcode-cn.com/problems/reverse-linked-list/)

示例：

```
输入: 1->2->3->4->5->NULL
输出: 5->4->3->2->1->NULL
```



递归：

需要先递归到最后一个节点5，从5开始5的next为4返回5新的头节点

`1 2<-3<-4<-5` 最后是这样的

```c++
ListNode* reverseList(ListNode* head) {
	if(!head || !head->next) return head; //base case，找到最后那个节点
  ListNode* tail = reverseList(head->next);// tail 最开始等于 5, head = 4
  head->next->next = head; //将 5 指向 4 
  head->next = nullptr; //4 指向空
  return tail; //返回 5
}
```

迭代

```c++
ListNode* reverseList(ListNode* head) {
  if(!head) return head; //base case
  ListNode* pre = nullptr, *cur = head;
  while(cur)
  {
    ListNode* nxt = cur->next; //记录下一个点
    cur->next = pre;//将当前指向前一个
    pre = cur;
    cur = nxt; //最后为nullptr
  }
  return pre; //返回 5
}
```

