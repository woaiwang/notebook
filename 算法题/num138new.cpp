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
        if (head == NULL) {
            return NULL; // 如果链表为空，直接返回 NULL
        }

        // 使用哈希表存储原节点到新节点的映射
        unordered_map<Node*, Node*> mp;
        Node* cur = head;

        // 第一步：创建所有新节点并存储到哈希表中
        while (cur) {
            int t = cur->val; // 获取当前节点的值
            mp[cur] = new Node(t); // 创建新节点并存储映射
            cur = cur->next; // 移动到下一个节点
        }

        cur = head;

        // 第二步：设置新节点的 next 和 random 指针
        while (cur) {
            Node* m = mp[cur->next]; // 获取当前节点的 next 对应的新节点
            Node* r = mp[cur->random]; // 获取当前节点的 random 对应的新节点
            mp[cur]->next = m; // 设置新节点的 next
            mp[cur]->random = r; // 设置新节点的 random
            cur = cur->next; // 移动到下一个节点
        }

        cur = head;
        return mp[cur]; // 返回新链表的头节点
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