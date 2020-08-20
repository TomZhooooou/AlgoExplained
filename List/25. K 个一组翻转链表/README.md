### [25. K 个一组翻转链表](https://leetcode-cn.com/problems/reverse-nodes-in-k-group/)

给你一个链表，每 k 个节点一组进行翻转，请你返回翻转后的链表。

k 是一个正整数，它的值小于或等于链表的长度。

如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。

 

示例：

给你这个链表：1->2->3->4->5

当 k = 2 时，应当返回: 2->1->4->3->5

当 k = 3 时，应当返回: 3->2->1->4->5

**说明：**

- 你的算法只能使用常数的额外空间。
- **你不能只是单纯的改变节点内部的值**，而是需要实际进行节点交换。

按照本题要求，我们需要做到以下几个步骤:

1. 找到当前需要断链的链表的头节点尾节点
2. 进行reverse操作
3. 将dummy连接到翻转后的头节点，将翻转后的尾节点(之前的头节点)连接到下一个nxt节点
4. 此时完成了，k长度到链表的翻转以及与原来的链表进行连接。 

```c++
ListNode* reverseKGroup(ListNode* head, int k) {
  /*
  -1->1->2->3->4->5
  */
  ListNode* dummy = new ListNode(-1);
  dummy->next = head;
  ListNode* cur = dummy; //储存当前的头节点位置
  ListNode* pre = dummy; //储存翻转前的尾节点
  while(true)
  {
    for(int i = 0 ; i< k && cur; i++)//当前节点移动k长度
    {
      cur = cur->next;
    }
    if(!cur) return dummy->next;
    ListNode* nxt = cur->next;//当前翻转段的下一个节点
    ListNode* tail = pre->next;//翻转后的尾节点
    cur->next = nullptr; // 断掉当前这段 
    pre->next = reverse(tail);//翻转前尾节点与当前翻转后的头节点相连
    tail->next = nxt; //尾节点连接下一个节点
    pre = tail;//将pre 和 cur都置于当前翻转后的尾节点处。
    cur = tail;
  }
  return dummy->next;
}
ListNode* reverse(ListNode* head) {
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

