

# 剑指offer 17与18

## 1.[面试题17. 打印从1到最大的n位数](https://leetcode-cn.com/problems/da-yin-cong-1dao-zui-da-de-nwei-shu-lcof/)

method1：使用pow函数。

```cpp
class Solution {
public:
    vector<int> printNumbers(int n) {
        vector<int> res;
        for (int i=1;i<pow(10,n);i++) {
            res.push_back(i);
        }
        return res;
    }
};
```

method2：快速幂。

```cpp
class Solution {
public:
    vector<int> printNumbers(int n) {
        vector<int> res;
        int result = 1;
        int x = 10;
        
        // 快速幂
        while (n!=0) {
            if(n & 1 == 1) {
                result *= x;
            }
            n >>= 1;
            x *= x;
        }

        for (int i=1;i<result;i++) {
            res.push_back(i);
        }
        return res;
    }
};
```

## 2.[面试题18. 删除链表的节点](https://leetcode-cn.com/problems/shan-chu-lian-biao-de-jie-dian-lcof/)

method1：使用dummyHead。

- 时间复杂度：O(N)。N 为链表的长度，最坏情况下，要删除的结点位于链表末尾，这时我们需要遍历整个链表。
- 空间复杂度：O(1)。仅使用了额外的 dummy。

```cpp
class Solution {
public:
    ListNode* deleteNode(ListNode* head, int val) {
        ListNode* dummyHead = new ListNode(-1);
        dummyHead->next = head;
        ListNode* p = dummyHead;
        while (p->next) {
            if (p->next->val == val) {
                ListNode* q = p->next;
                p->next = q->next;
                break;
            }
            p=p->next;
        }

        p = dummyHead->next;
        delete dummyHead;
        return p;
    }
};
```

method2：递归删除节点。

四个动作：

- 链表为空或者到达末尾
- 找到待删除节点，返回当前节点的后一个
- 当前节点的next连接后续节点
- 返回当前节点

```cpp
class Solution {
public:
    ListNode* deleteNode(ListNode* head, int val) {
        if(!head) return NULL;
        if(head->val == val) return head->next;
        head->next = deleteNode(head->next,val);
        return head;
    }
};
```

method3：信息交换法，时间复杂度O(1)，由于leetcode的参数为int val，所以只能采取前面两种，当int val改为ListNode的时候，就可以这样做了。把删除的节点的下一个节点值填充到删除的节点上，让其指向下一个节点的下一个节点。我们发现，如果删除节点为前面的 n-1 个节点，时间复杂度均为 O(1)，只有删除节点为最后一个时，时间复杂度才会变成 O(n)。平均时间复杂度为：(O(1)\times(n-1) + O(n))/n = (O(1)×(n−1)+O(n))/n=O(1)，仍然为 O(1)。

```cpp
class Solution {
public:
    ListNode* deleteNode(ListNode* head, ListNode* deleteNode) {
    	if(head==nullptr||deleteNode==nullptr) return nullptr;
       if(head == NULL || deleteNode == NULL) return NULL;
        if(deleteNode->next != NULL){
            deleteNode->val = deleteNode->next->val;
            deleteNode->next = deleteNode->next->next;
        }
        //头尾结点相同
        else if(head == deleteNode) return NULL;
        else{
            ListNode* cur = head;
            //找到倒数第二结点
            while(cur->next != NULL && cur->next->next != NULL){
                cur = cur->next;
            }
            cur->next = NULL;
        }
        return head;
    }        
};
```

## 3.删除链表中重复的节点

使用dummyHead,注意判空。

```cpp
/*
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};
*/
class Solution {
public:
    ListNode* deleteDuplication(ListNode* pHead)
    {
        ListNode* dummyHead = new ListNode(-1);
        dummyHead->next = pHead;
        ListNode* pre=dummyHead,*last = dummyHead->next;
        while(last!=NULL) {
            if(last->next!=NULL && last->val == last->next->val) {
                while(last->next!=NULL && last->val == last->next->val) {
                    last = last->next;
                }
                pre->next = last->next;
                last = last->next;
            } else {
                pre = pre->next;
                last = last->next;
            }
        }
        pre = dummyHead->next;
        delete dummyHead;
        return pre;
    }
};
```

递归实现：

```cpp
/*
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};
*/
class Solution {
public:
    ListNode* deleteDuplication(ListNode* pHead)
    {
        if(pHead == NULL) return NULL;
        if(pHead->next==NULL) return pHead;
        // 重复结点处理
        if (pHead->val == pHead->next->val) {
            ListNode* p = pHead->next->next;
            while(p!=NULL && p->val == pHead->val) {
                p = p->next;
            }
            return deleteDuplication(p);
        }
        pHead->next = deleteDuplication(pHead->next); 
        return pHead;
    }
};
```

