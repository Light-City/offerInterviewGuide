# 剑指offer05与06

## 1.[面试题05. 替换空格](https://leetcode-cn.com/problems/ti-huan-kong-ge-lcof/)

在牛客上提交的C++风格代码：牛客上这道题有个坑，length表述不清晰，按照我的理解是length并非str的实际长度，因此在代码中判断应用`\0`判断。先统计一遍空格数量，从而计算出新字符串长度，从右至左，对原串进行修改。时间复杂度O(n)，空间复杂度O(1)。

```cpp
#include <iostream>
#include <string.h>

using namespace std;
class Solution {
public:
    void replaceSpace(char *str,int length) {
        int spaceNum=0;
        int originLen=0;
        for(int i=0;str[i]!='\0';i++){
            if(str[i]==' ')
                spaceNum++;
            originLen++;
        }
        int newL = originLen+2*spaceNum;
        int j=newL-1;
        str[newL]='\0';
        while(j>=0) {
            if(str[originLen-1]==' ') {
                str[j--]='0';
                str[j--]='2';
                str[j--]='%';
            } else {
                str[j--]=str[originLen-1];
            }
            originLen--;
        }
    }
};
```

另外，也可以用string解决掉：时间复杂度与空间复杂度均为O(n)。

```cpp
void replaceSpace1(char *str,int length) {
    string s;
    for (int i=0;str[i]!='\0';i++) {
        if(str[i]!=' ')
            s+=str[i];
        else
            s+="%20";
    }
    strcpy(str,s.c_str());
}
```

LeetCode上就比较简单了，直接使用string的`+=`即可。时间复杂度与空间复杂度均为O(n)。

```cpp
class Solution {
public:
    string replaceSpace(string s) {
        string t;
        for (int i=0;i<s.length();i++) {
            if(s[i]!=' ')
                t+=s[i];
            else
                t+="%20";
        }
        return t;
    }
};
```

## 2.[面试题06. 从尾到头打印链表](https://leetcode-cn.com/problems/cong-wei-dao-tou-da-yin-lian-biao-lcof/)

method1: 递归写法，时间复杂度与空间复杂度均为O(n)。

```cpp
class Solution {
public:
    vector<int> reversePrint(ListNode* head) {
        vector<int> res;
        Recursive(head,res);
        return res;
    }

    void Recursive(ListNode* head,vector<int> &res) {
        if(head==NULL) {
            return;
        }

        Recursive(head->next,res);
        res.push_back(head->val);
    }
};
```

method2:非递归写法，栈保存。

```cpp
class Solution {
public:
    vector<int> reversePrint(ListNode* head) {
        stack<int> st;
        while(head) {
            st.push(head->val);
            head=head->next;
        }
        vector<int> res;
        while(!st.empty()) {
            res.push_back(st.top());
            st.pop();
        }
        return res;
    }
};
```

