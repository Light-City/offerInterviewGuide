# 剑指offer 07与09

## 1.[面试题07. 重建二叉树](https://leetcode-cn.com/problems/zhong-jian-er-cha-shu-lcof/)

### 1.1 中序+前序(本题)

回顾：二叉树四种遍历方式

例如一个二叉树层次遍历顺序为[1,2,3,4,5,6,7],那么：

前：[1, 2, 4, 5, 3, 6, 7]

中：[4, 2, 5, 1, 5, 3, 7]

后：[4, 5, 2, 6, 7, 3, 1]

层：[1, 2, 3, 4, 5, 6, 7]

- 前序遍历：先访问根结点，再访问左子结点，最后访问右子结点。
- 中序遍历：先访问左子结点，再访问根结点，最后访问右子结点。
- 后序遍历：先访问左子结点，再访问右子结点，最后访问根结点。

回到这个题目，我们知道中序+前序可以构建一颗二叉树，而本题就是通过这个方式来构建，当然后序+中序也可以构建，但是前序+后序是不可以的。举个例子：

```
	D
  /
E
```

前序遍历：DE, 后序遍历：ED

则下面树的结构也满足前序和后序遍历的序列。

```
D
  \
	E
```

即这种情况，不能唯一确定一棵树。

当前这个题目(前序+中序)解决方案如下：

- **不使用原数组**
- **使用原数组-采用左节点个数构建**
- **使用原数组-采用右节点个数构建**

**（1）不使用原数组**

思路很简单，对比中序列与前序：

```
前序：[1, 2, 4, 5, 3, 6, 7]
		
中序：[4, 2, 5, 1, 5, 3, 7]
	       i
```

首先构建根，其次递归构建自己的左右孩子，最后返回根就可以了。

每次在中序遍历中找到根节点位置，然后划分左右孩子。

```cpp
TreeNode *reConstructBinaryTree(vector<int> pre, vector<int> vin) {
    if (pre.empty() || vin.empty()) return NULL;
    TreeNode *root = new TreeNode(pre[0]);
    vector<int> lpre, lvin, rpre, rvin;

    for (int i = 0; i < vin.size(); i++) {
        if (vin[i] == pre[0]) {
            lpre = vector<int>(pre.begin() + 1, pre.begin() + i + 1);
            lvin = vector<int>(vin.begin(), vin.begin() + i);
            rpre = vector<int>(pre.begin() + i + 1, pre.end());
            rvin = vector<int>(vin.begin() + i + 1, vin.end());
            root->left = reConstructBinaryTree(lpre, lvin);
            root->right = reConstructBinaryTree(rpre, rvin);
        }
    }
    return root;
}
```

这种方法非常好理解，缺点是并不是在原来的数组上操作。

下面这种方法是直接在原来的数组上操作的，但是下标边界直接看不是很明白，需要配合画图才能理解。

再看下面这个：

```
前序：[1, 2, 4, 5, 3, 6, 7]
   pStart              pEnd	
中序：[4, 2, 5, 1, 5, 3, 7]
   vStart      i       vEnd
```

中序遍历得出如下结论：

- 左子结点长度 = i - vStart
- 右子结点长度 = vEnd - i

> 所以对于左子树来说：

前序遍历下标范围  = [pStart+1,pStart+i-vStart]

中序遍历下标范围  = [vStart,i-1]

> 对于右子树来说

前序遍历下标范围  = [pStart+i-vStart+1,pEnd]

中序遍历下标范围  =  [i+1,vEnd]

于是第二种方法出来了。

**（2）使用原数组-采用左节点个数构建**

```cpp
TreeNode *preForConstructBinaryTree(vector<int> pre, vector<int> vin) {
    return preAndVin(pre, 0, pre.size() - 1, vin, 0, vin.size() - 1);
}
// 前序+中序
TreeNode *preAndVin(const vector<int> &pre, int pStart, int pEnd, const vector<int> &vin,int vStart, int vEnd) {
    // 递归终止条件
    if (pStart > pEnd || vStart > vEnd) return NULL;
    TreeNode *root = new TreeNode(pre[pStart]);  // 重建根节点
    // 重建左右子树
    for (int i = vStart; i <= vEnd; i++) {
        if (vin[i] == pre[pStart]) {
            root->left = preAndVin(pre, pStart + 1, pStart + i - vStart, vin, vStart, i - 1);
            root->right = preAndVin(pre, pStart + i - vStart + 1, pEnd, vin, i + 1, vEnd);
    }
    return root;
}
```

**（3）使用原数组-采用右节点个数构建**

另外，我们还可以使用右子结点长度来构建。

> 所以对于左子树来说：

前序遍历下标范围  = [pStart+1,pEnd-(vEnd-i)]

中序遍历下标范围  =  [vStart,i-1]

> 对于右子树来说

前序遍历下标范围  = [pEnd-(vEnd-i)+1,pEnd]

中序遍历下标范围  = [i+1,vEnd]

只需要将上述左右子树构建改为：

```
root->left = preAndVin(pre, pStart + 1, pEnd - (vEnd - i), vin, vStart, i - 1);
root->right = preAndVin(pre, pEnd - (vEnd - i) + 1, pEnd, vin, i + 1, vEnd);
```

### 1.2 中序+后序

既然这道题是前序+中序，那么我们在琢磨一下中序+后序呗，同样的道理，也是上面两种。

**（1）不使用原数组**

```cpp
TreeNode *reConstructBinaryTree1(vector<int> post, vector<int> vin) {
    if (post.empty() || vin.empty()) return NULL;
    TreeNode *root = new TreeNode(post[post.size() - 1]);
    vector<int> lpost, lvin, rpost, rvin;

    for (int i = 0; i < vin.size(); i++) {
        if (vin[i] == post[post.size() - 1]) {
            // 后序 左半边
            lpost = vector<int>(post.begin(), post.begin() + i);
            // 中序 左半边
            lvin = vector<int>(vin.begin(), vin.begin() + i);

            // 后序 右半边
            rpost = vector<int>(post.begin() + i, post.end() - 1);
            // 前序 右半边
            rvin = vector<int>(vin.begin() + i + 1, vin.end());
            root->left = reConstructBinaryTree1(lpost, lvin);
            root->right = reConstructBinaryTree1(rpost, rvin);
        }
    }
    return root;
}
```

**（2）使用原数组-采用左节点个数构建**

```
后：[4, 5, 2, 6, 7, 3, 1]
   pStart             pEnd	
中：[4, 2, 5, 1, 5, 3, 7]
   vStar     i        vEnd
```

- 左子结点长度 = i - vStart
- 右子结点长度 = vEnd - i

> 所以对于左子树来说：

后序遍历下标范围  = [pStart,pStart+i-vStart-1]

中序遍历下标范围  =  [vStart,i-1]

> 对于右子树来说

后序遍历下标范围  = [pStart+i-vStart,pEnd-1]

中序遍历下标范围  = [i+1,vEnd]

```
// 中序+后序
TreeNode *postAndVin(const vector<int> &post, int pStart, int pEnd, const vector<int> &vin,int vStart, int vEnd) {
        // 递归终止条件
        if (pStart > pEnd || vStart > vEnd) return NULL;
        int rootVal = post[pEnd];
        TreeNode *root = new TreeNode(rootVal);  // 重建根节点
        // 重建左右子树
        for (int i = vStart; i <= vEnd; i++) {
            if (vin[i] == rootVal) {
                root->left = postAndVin(post, pStart, pStart + i - vStart - 1, vin, vStart, i - 1);
               	root->right = postAndVin(post, pStart + i - vStart, pEnd - 1, vin, i + 1, vEnd);
            }
        }
        return root;
    }
};
```

**（3）使用原数组-采用右节点个数构建**

> 所以对于左子树来说：

前序遍历下标范围  = [pStart,pEnd - (vEnd - i) - 1]

中序遍历下标范围  =  [vStart,i-1]

> 对于右子树来说

后序遍历下标范围  = [pEnd-(vEnd-i),pEnd-1]

中序遍历下标范围  = [i+1,vEnd]

所以，上述代码改为：

```
// method 2
root->left = postAndVin(post, pStart, pEnd - (vEnd - i) - 1, vin, vStart, i - 1);
root->right = postAndVin(post, pEnd - (vEnd - i), pEnd - 1, vin, i + 1, vEnd);
```

## 2.[面试题09. 用两个栈实现队列](https://leetcode-cn.com/problems/yong-liang-ge-zhan-shi-xian-dui-lie-lcof/)

method1:两个栈分别作用如下：

- 一个入栈
- 一个出栈

入栈存入元素，出栈删除元素。当出栈为空，从入栈中取元素，如果还是没有，就说明没元素了，返回-1即可。

入栈操作O(1)，出栈操作最坏O(n)，最好O(1)。

```cpp
class CQueue {
private:
    stack<int> inStack;
    stack<int> outStack;
public:
    CQueue() {
    }
    
    void appendTail(int value) {
        inStack.push(value);
    }
    
    int deleteHead() {
        int res=-1;
        if(!outStack.empty()) {
            res=outStack.top();
            outStack.pop();
        } else if(!inStack.empty()) {
            while(!inStack.empty()) {
                outStack.push(inStack.top());
                inStack.pop();
            }
            res = outStack.top();
            outStack.pop();
        }
        return res;
    }
};
```

method2:vector模拟栈，牛客上可通过，leetcode不行。

入栈操作O(1)，出栈操作最坏O(n)，最好O(1)。

```cpp
class Solution
{
public:
    
    void push(int node) {
        stack1.push_back(node);
        stack2.push_back(cou++);
    }
 
    int pop() {
        int i = 0;
        while(stack2[i] == -1)
        {
            i++;
        }
        stack2[i] = -1;
        return stack1[i];
    }
 
private:
    int cou = 0;
    vector<int> stack1;//存数
    vector<int> stack2;//地址
};

```



