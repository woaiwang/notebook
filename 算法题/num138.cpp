#include <iostream>
#include <unordered_map>
using namespace std;

// Definition for a Node.
class Node {
public:
    int val; // 节点的值
    Node* next; // 指向下一个节点的指针
    Node* random; // 指向随机节点的指针

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(head==NULL) {
            return NULL; // 如果链表为空，直接返回 NULL
        }

        // 第一步：在每个原节点后面创建一个新节点
        Node* cur = head;
        while(cur) {
            int t = cur->val; // 获取当前节点的值
            Node* x = cur->next; // 保存原链表的下一个节点
            Node* m = new Node(t); // 创建新节点
            cur->next = m; // 将新节点插入到当前节点后面
            m->next = x; // 新节点的 next 指向原链表的下一个节点
            cur = x; // 移动到下一个原节点
        }

        // 第二步：设置新节点的随机指针
        cur = head;
        while (cur) {
            if (cur->random) {
                cur->next->random = cur->random->next; // 新节点的 random 指向对应的复制节点
            } else {
                cur->next->random = NULL; // 如果原节点的 random 为 NULL，新节点的 random 也为 NULL
            }
            cur = cur->next->next; // 跳过新节点，移动到下一个原节点
        }

        // 第三步：分离原链表和复制链表
        cur = head;
        Node* dummy = new Node(0); // 创建一个虚拟头节点
        Node* copyCur = dummy; // 用于构建复制链表的指针
        
        while (cur) {
            Node* nextOriginal = cur->next->next; // 保存下一个原节点
            Node* copyNode = cur->next; // 提取新节点
            copyCur->next = copyNode; // 将新节点加入到复制链表
            copyCur = copyNode; // 移动复制链表的指针
            cur->next = nextOriginal; // 恢复原链表
            cur = nextOriginal; // 移动到下一个原节点
        }

        // 第四步：返回复制链表的头节点
        Node* newHead = dummy->next;
        delete dummy; // 释放虚拟头节点
        return newHead;
    }
};

// 辅助函数：打印链表
void printList(Node* head) {
    Node* cur = head;
    while (cur) {
        cout << "Node value: " << cur->val; // 打印节点值
        if (cur->random) {
            cout << ", Random points to: " << cur->random->val; // 打印随机指针指向的节点值
        } else {
            cout << ", Random points to: NULL"; // 随机指针为空
        }
        cout << endl;
        cur = cur->next; // 移动到下一个节点
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