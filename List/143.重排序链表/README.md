### [143. 重排链表](https://leetcode-cn.com/problems/reorder-list/)

给定一个单链表 L：L0→L1→…→Ln-1→Ln ，
将其重新排列后变为： L0→Ln→L1→Ln-1→L2→Ln-2→…

你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。

示例1:

```
给定链表 1->2->3->4, 重新排列为 1->4->2->3.
```

首先我们需要将链表断成两部分，一部分是0-(n+1)/2 注意奇数时前半部分长一个节点，和后半部分。

可以通过快慢指针完成。

```c++
void reorderList(ListNode* head) {
  if(!head) return;
  ListNode* secondHalf = cut(head);// 获取后半部分的head
  secondHalf = reverse(secondHalf);//翻转后半部分链表
  ListNode* cur = head; 
  ListNode* sec = secondHalf; 
  while(sec)
  {
    ListNode* nxt = cur->next;//记录下一个cur
    ListNode* secNext = sec->next;//记录下一个sec 
    cur->next = sec;//当前cur连接sec
    sec->next = nxt;//sec的next连接nxt
    cur = nxt;//同时往右推进一个节点
    sec = secNext;
  }
}
ListNode* cut(ListNode* head)
{
  ListNode* fast = head;
  ListNode* slow = head;
  while(fast && fast->next)
  {
    fast = fast->next->next;
    slow = slow->next;
  }
  ListNode* second = slow->next; 
  slow->next = nullptr;
  return second;
}
ListNode *reverse(ListNode* head)
{
  if(!head || !head->next) return head;
  ListNode* tail = reverse(head->next);
  head->next->next = head;
  head->next = nullptr;
  return tail;
}
```

