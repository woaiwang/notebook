#include <iostream>
#include <unordered_map>
using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};


class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(head==NULL)
        {
            return NULL;
        }
        Node* cur=head;
        while(cur)
        {
            int t=cur->val;
            Node* x=cur->next;
            Node* m=new Node(t);
            cur->next=m;
            m->next=x;
            cur=x;
        }
        cur=head;
       
        while (cur) {
            if (cur->random) {
                cur->next->random = cur->random->next;
            } else {
                cur->next->random = NULL;  // 重要：处理NULL情况
            }
            cur = cur->next->next;
        }
        // 3. 分离两个链表
        cur = head;
        Node* dummy = new Node(0);
        Node* copyCur = dummy;
        
        while (cur) {
            // 记录下一个原节点
            Node* nextOriginal = cur->next->next;
            
            // 提取新节点
            Node* copyNode = cur->next;
            
            // 将新节点加入到新链表
            copyCur->next = copyNode;
            copyCur = copyNode;
            
            // 恢复原链表
            cur->next = nextOriginal;
            
            // 移动到下一个原节点
            cur = nextOriginal;
        }
        
        // 4. 返回新链表的头节点
        Node* newHead = dummy->next;
        delete dummy;  // 释放dummy节点
        return newHead;
    }
};

// 辅助函数：打印链表
void printList(Node* head) {
    Node* cur = head;
    while (cur) {
        cout << "Node value: " << cur->val;
        if (cur->random) {
            cout << ", Random points to: " << cur->random->val;
        } else {
            cout << ", Random points to: NULL";
        }
        cout << endl;
        cur = cur->next;
    }
}

// 测试函数
int main() {
    // 创建测试链表
    Node* node1 = new Node(1);
    Node* node2 = new Node(2);
    Node* node3 = new Node(3);

    node1->next = node2;
    node2->next = node3;

    node1->random = node3; // 1的随机指针指向3
    node2->random = node1; // 2的随机指针指向1
    node3->random = nullptr; // 3的随机指针为空

    cout << "Original list:" << endl;
    printList(node1);

    // 调用复制函数
    Solution solution;
    Node* copiedList = solution.copyRandomList(node1);

    cout << "\nCopied list:" << endl;
    printList(copiedList);

    // 释放内存
    delete node1;
    delete node2;
    delete node3;

    Node* cur = copiedList;
    while (cur) {
        Node* next = cur->next;
        delete cur;
        cur = next;
    }

    return 0;
}