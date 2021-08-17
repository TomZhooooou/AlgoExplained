### **3 perspectives**

**1.Data Structures**

* Linked List
* Tree
* Queue
* Stack
* HashMap
* Strings
* Arrays & Matrix
* Graph

* BitOps

  **Palindrome Permutation** determine if it string could form palindrome 

  <details>  

  <summary>Clink to expand </summary>

  ```
  Input: "tactcoa"
  Output: true（permutations: "tacocat"、"atcocta", etc.）
  ```

  **-** there is 128 chars in ASCII table, from 0 - 127, which could be represented by 128 bits in Binary

  - use bitset with 128 bits to store each char, if there is only one char with odd count or zero count, it should be a palindrome. 
  - if there is one char left there should be one bit that the value is 1, hence the total count of ones should not exceed 1;

  ```c++
  class Solution {
  public:
      bool canPermutePalindrome(string s) {
        bitset<128> result; 
        for(auto c : s) {
          result ^= bitset<128>(1) << c; //flip the unique bit representing the char
        }
        return result.count() <= 1; //only 1 bit should be left in the bitset result
      }
  };
  ```

  </details>



**2.LeetCode Questions**



**3.Algrithm Patterns**

- 1.Sliding window



- 2.Two pointers



- 3.Fast & Slow pointer



- 4.Merge intervals

  

  **56.Merge Intervals** **/ https://leetcode.com/problems/merge-intervals/**

  <details>

  <summary> click to expand </summary>

  **-** first sort the intervals by start time, which will help to merge then in order.

  

  ```c++
  class Solution {
  public:
      vector<vector<int>> merge(vector<vector<int>>& intervals) {
          vector<vector<int>> res;
          sort(intervals.begin(), intervals.end(), 
               [](const vector<int> &interval1, const vector<int> &interval2) {return interval1[0] < interval2[0]; });
          vector<int> last = intervals[0];//take the first interval as base
          for(int i = 1; i < intervals.size(); i++) {
              if(last[1] >= intervals[i][0]) { //since last[0] < intervals[i][0] the two interval must have overlap
                  last[1] = max(last[1], intervals[i][1]); // take the larger end
              } else {
                  res.push_back(last); //when there is no overlap with current interval
                  last = intervals[i]; // take current interval as base interval
              }
          }
          res.push_back(last); //important, the last base interval is never pushed into the res when the loop ends.
          return res;
      }
  };
  ```

  

  </details>

  **57. Insert Interval** **/ https://leetcode.com/problems/insert-interval/**

  <details>

  <summary> click to expand </summary>

  Given a set of *non-overlapping* intervals, insert a new interval into the intervals (merge if necessary).

  ```
  Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
  Output: [[1,5],[6,9]]
  ```

  ![image-20210818024606614](/Users/tomgreen/Library/Application Support/typora-user-images/image-20210818024606614.png)

  **-** we could first insert the intervals a head of the newInterval to the result array. Then we insert the newinterval, merge necessary intervals, and lastly insert the rest intervals to the result array.

  

  ```c++
  class Solution {
  public:
      vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
          vector<vector<int>> res;
          if(intervals.empty()) {
              return {newInterval};
          }
          int i = 0;
          for( ; i < intervals.size() && newInterval[0] > intervals[i][1]; i++) { // interset the intervals ahead of the newIntervals.
              res.push_back(intervals[i]);
          }
          //[1]
          //if (i < intervals.size()) newInterval[0] = min(newInterval[0], intervals[i][0]);
          for(; i < intervals.size() && newInterval[1] >= intervals[i][0]; i++) {// merge intervals in the middle
              newInterval[1] = max(newInterval[1], intervals[i][1]);
              newInterval[0] = min(newInterval[0], intervals[i][0]); // this could be taken out at [1]. since it could be only set once, and the minimal value will remain the same.
          }
          res.push_back(newInterval);//insert this newInterval
          for(; i < intervals.size(); i++) { // insert the rest intervals if there's any
              res.push_back(intervals[i]);
          }
          return res;
      }
  };
  ```

  </details>

  **986. Interval List Intersections** **/ https://leetcode.com/problems/interval-list-intersections/**

  <details>

  <summary> click to expand </summary>

  ```
  Input: firstList = [[0,2],[5,10],[13,23],[24,25]], secondList = [[1,5],[8,12],[15,24],[25,26]]
  Output: [[1,2],[5,5],[8,10],[15,23],[24,24],[25,25]]
  ```

  

  ```c++
  class Solution {
  public:
      vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList, vector<vector<int>>& secondList) {
          vector<vector<int>> res;
          if(firstList.empty() || secondList.empty()) {// if any list is empty there will be no intersections
              return res;
          }
          int index1 = 0, index2 = 0;
          while(index1 < firstList.size() && index2 < secondList.size()) {
              vector<int> first = firstList[index1], second = secondList[index2];
              if(second[0] <= first[1] && second[1] >= first[0]) { // if two interval intersects 
                  res.push_back({max(first[0], second[0]), min(second[1], first[1])});
              }             
              if(second[1] > first[1]) { // move the interval that has smaller end
                  index1++;
              } else {
                  index2++;
              }
          }
          return res;
      }
  };
  ```

  Another improved solution: it looks more clean

  ```c++
  class Solution {
  public:
      vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList, vector<vector<int>>& secondList) {
          vector<vector<int>> res;
          if(firstList.empty() || secondList.empty()) {// if any list is empty there will be no intersections
              return res;
          }
          int index1 = 0, index2 = 0;
          while(index1 < firstList.size() && index2 < secondList.size()) {
            	int start1 = firstList[index1][0], end1 = firstList[index1][1], start2 = secondList[index2][0], end2 = secondList[index2][1];
            	int start = max(start1, start2);//take the larger start if they overlap
              int end = min(end1, end2); 
              if(start <= end) {//if a valid interval could be formed
                res.push_back({start, end});
              }
              if(end2 > end1) { // move the interval that has smaller end
                  index1++;
              } else {
                  index2++;
              }
          }
          return res;
      }
  };
  ```

  </details>

  **253.Meeting Rooms** **/ https://leetcode.com/problems/meeting-rooms-ii/**

  <details>

  <summary> click to expand </summary>

  Given a list of intervals representing the start and end time of ‘N’ meetings, find the **minimum number of rooms** required to **hold all the meetings**.

  

  ```
  Input: intervals = [[0,30],[5,10],[15,20]]
  Output: 2
  ```

  **-** track the number of meeting rooms that are used at the same time.

  * sort the meetings by start time
  * when one meeting hasn't finish when the next meeting comes, these two meetings are hold simultaneously 
  * use min_heap to keep track of the meetings happen at the same time.
  * sort the min_heap by the end time, so that when the next meeting comes, we can determine if the previous meeting is finished or not

  

  ```c++
  class Solution {
  public:
      struct cmp {
          bool operator()(const vector<int> &interval1, const vector<int> &interval2) {//min_heap comparator
              return interval1[1] > interval2[1];
          }
      };
      int minMeetingRooms(vector<vector<int>>& intervals) {
          int numRoom = 0;
          sort(intervals.begin(), intervals.end(), [](const vector<int> &interval1, const vector<int> &interval2){return interval1[0] < interval2[0];});//sort meetings with starting time.
          priority_queue<vector<int>, vector<vector<int>>, cmp> pq;
          for(auto interval : intervals) {
              while(!pq.empty() && pq.top()[1] <= interval[0] ) {//pop out the finished meetings at current time
                  pq.pop();
              }
              pq.push(interval);
              numRoom = max((int)pq.size(), numRoom);
          }
          return numRoom;
      }
  };
  ```

  method 2:

  ```c++
  class Solution {
  public:
      struct cmp {
          bool operator()(const vector<int> &interval1, const vector<int> &interval2) {
              if(interval1[0] != interval2[0]) {
                  return interval1[0] < interval2[0];
              } else {
                  return interval1[1] < interval2[1];
              }
          }
      };
      int minMeetingRooms(vector<vector<int>>& intervals) {
          vector<vector<int>> schedules;
          int res = 0;
          
          for(auto interval : intervals) {
              schedules.push_back({interval[0], 1});
              schedules.push_back({interval[1], -1});
          }
          int curNum = 0;
          sort(schedules.begin(), schedules.end(), cmp());
          for(auto schedule : schedules) {
              curNum += schedule[1];
              res = max(curNum, res);
          }
          return res;
      }
  };
  ```

  </details>

  **759. Employee Free Time / https://leetcode.com/problems/employee-free-time/**

  <details>

  <summary> click to expand </summary>

  Solution 1: using priority_queue to sort the intervals and process them one by one

  ```c++
  /*
  // Definition for an Interval.
  class Interval {
  public:
      int start;
      int end;
  
      Interval() {}
  
      Interval(int _start, int _end) {
          start = _start;
          end = _end;
      }
  };
  */
  
  class Solution {
  public:
      struct cmp {
          bool operator ()(const Interval &interval1, const Interval &interval2) {
              return interval1.start > interval2.start;
          }
      };
      vector<Interval> employeeFreeTime(vector<vector<Interval>> schedule) {
          vector<Interval> res;
          priority_queue<Interval, vector<Interval>, cmp> pq;
          for(auto sche : schedule) {
              for(auto interval : sche) {
                  pq.push(interval);//put all elements into the priority_queue
              }
          }
          Interval previous = pq.top();//get the first interval
          pq.pop(); 
          while(!pq.empty()) {
              auto interval = pq.top();
              pq.pop();
              if(previous.end >= interval.start) { //if there is overlap
                  previous.end = max(previous.end, interval.end);
              } else {//if no overlap, we move on to the next interval;
                  res.push_back(Interval(previous.end, interval.start));// put the non-overlapping part into the result
                  previous = interval;
              }
          }
          return res;
      }
  };
  ```

  

  Solution 2: push the intervals into an array and produce a merged list. Then find out all the blank intervals		

  </details>

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

  

  **23.Merge k Sorted Lists / https://leetcode.com/problems/merge-k-sorted-lists/** 

  <details>

    <summary>Click to expand</summary>

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

  Time Complexity:O(N * logK), where N is the total number of elements, K is the number of lists.

  Space Complexity: O(K)

  

  Similar Question:merge the K sorted lists instead of linked-lists

  </details>

  **378.Kth Smallest Element in a Sorted Matrix**

  <details> 
    <summary>Click to expand</summary>

  **-** similar to question 23, we will store the first element of the array in the heap, and iterate through the whole matrix

  **-** in order to keep track of the position in each sub array, we need to store the **coordinates of the element** in a pair, and to compare the value of the element we need to store the value together with coordinates pair in another pair.

  

  ```c++
  typedef pair<int, pair<int,int>> pipii; //shorter alias
  class Solution {
  public:
      struct cmp {
          bool operator() ( pipii p1, pipii p2) { // define a comparator for the min-heap 
              return p1.first > p2.first;
          }
      };
      int kthSmallest(vector<vector<int>>& matrix, int k) {
          int n = matrix.size();
          priority_queue<pipii, vector<pipii>, cmp> q;
          for(int i = 0; i < n; i++) {
              if(matrix[i].size() > 0) {
                  q.push(make_pair(matrix[i][0], make_pair(i, 0)));
              }
          }
          while(!q.empty() && --k > 0) { //when k is equal to 1, we won't need to enter the loop
              auto pair = q.top();
              q.pop();
            	pair.second.second ++; //update the index of the sub-array 
              if(n > pair.second.second) {
                  pair.first = matrix[pair.second.first][pair.second.second]; //update the value for the sub-array
                  q.push(pair);
              }
          }
          return q.top().first;
      }
  };
  ```

  

  similar questions: find median of the matrix

  

  </details>

  **632. Smallest Range Covering Elements from K Lists  Hard**

  <details>

  <summary> click to expand </summary>

  You have `k` lists of sorted integers in **non-decreasing order**. Find the **smallest** range that includes at least one number from each of the `k` lists.

  **-** we need to cover at list one element in each array, hence we could insert one element from each array into a **min-heap**, keep track of the largest number in the heap, the difference between the largest value and the top element in the heap is the current range. We need to traverse throught the lists and get the smallest range. 

  

  ```c++
  typedef pair<int, pair<int,int>> pipii; //shorter alias
  
  class Solution {
  public:
      struct cmp {
          bool operator() ( pipii p1, pipii p2) { // define a comparator for the min-heap 
              return p1.first > p2.first;
          }
      };
      
      vector<int> smallestRange(vector<vector<int>>& nums) {
          int curMaxNum = 0, range = INT_MAX; 
          vector<int> result(2);
          priority_queue<pipii, vector<pipii>, cmp> pq;
          for(int i = 0; i < nums.size(); i++) {
              if(!nums[i].empty()) {
                  pq.push(make_pair(nums[i][0], make_pair(i, 0)));
                  curMaxNum = max(curMaxNum, nums[i][0]);
              }
          }
          while(!pq.empty()) {
              auto pair = pq.top();
              pq.pop();
              if(curMaxNum - pair.first < range) {
                  range = curMaxNum - pair.first;
                  result[0] = pair.first;
                  result[1] = curMaxNum;
              }
              pair.second.second++;
              if(nums[pair.second.first].size() > pair.second.second) {
                  pair.first = nums[pair.second.first][pair.second.second];
                  pq.push(pair);
                  curMaxNum = max(curMaxNum, pair.first);
              } else {
                  break;
              }
          }
          return result;
      }
  };
  ```

  

  

  </details>



- * Merge k Sorted Lists

  

  

- 15.0/1 knapsack DP



- 16.Topological Sort Graph



