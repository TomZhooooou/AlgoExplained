### **3 perspectives**

1.Data Structures

* Linked List
* Tree
* Queue
* Stack
* HashMap
* Strings
* Arrays & Matrix
* Graph

* BitOps



2.Highlight LeetCode Questions



3.algrithm patterns

- 1.Sliding window



- 2.Two pointers



- 3.Fast & Slow pointer



- 4.Merge intervals



- 5.Cyclic Sort



- 6.In-place Reversal of a linked list



- 7.Tree BFS



- 8.Tree DFS



- 9.Two heaps



- 10.Subsets



- 11.Modified Binary Search



- 12.Bitwise XOR



- 13.TOP K element



- 14.K-way merge

  <details>

    <summary>Click to expand</summary>

  #### 23.Merge k Sorted Lists / https://leetcode.com/problems/merge-k-sorted-lists/ 

  

  You are given an array of `k` linked-lists `lists`, each linked-list is sorted in ascending order.

  *Merge all the linked-lists into **one sorted linked-list** and return it.*

  

  ```
  Input: lists = [[1,4,5],[1,3,4],[2,6]]
  Output: [1,1,2,3,4,4,5,6]
  Explanation: The linked-lists are:
  [
    1->4->5,
    1->3->4,
    2->6
  ]
  merging them into one sorted list:
  1->1->2->3->4->4->5->6
  ```

  

  **-** since we start from smallest number among these lists, **Heap** is most suitable Data Structure to handle it.

  - first insert the head of the lists into a Min Heap

  - then get the top element out, and link it to the result list

  ```c++
  class Solution {
  public:
      struct cmp {
          bool operator() (ListNode *l1, ListNode *l2) { // define a comparator for the min-heap 
              return l1->val > l2->val;
          }
      };
      ListNode* mergeKLists(vector<ListNode*>& lists) {
          if(lists.empty()) { // base case, return null when lists is empty
              return nullptr;
          }
          priority_queue<ListNode*, vector<ListNode*>, cmp>q;//define the priority queue with the comparator
          ListNode *head = new ListNode(-1); // create a dummy list for result
          ListNode *cur = head; //pointer to the header of dummy list
          for(auto head : lists) {
              if(head) {//when head is not nullptr
                  q.push(head);
              }
          }
          while(!q.empty()) {
              auto top = q.top(); //get the top element from the queue
              q.pop();
              cur->next = top; //link the element to the result list
              cur = cur->next; 
              if(top->next) { //when the node isn't the last element of the list
                  q.push(top->next);
              }
          }
          return head->next; 
      }
  }
  ```

  </details>

- * Merge k Sorted Lists

  

  

- 15.0/1 knapsack DP



- 16.Topological Sort Graph



