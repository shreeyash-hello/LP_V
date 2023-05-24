// g++ filename.cpp -o filename.exe -fopenmp ./filename.exe

#include <iostream>
#include <queue>
#include <omp.h>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* insert(Node* root, int data) {
    if (!root) {
        root = new Node;
        root->data = data;
        root->left = nullptr;
        root->right = nullptr;
        return root;
    }

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();

        if (!curr->left) {
            curr->left = new Node;
            curr->left->data = data;
            curr->left->left = nullptr;
            curr->left->right = nullptr;
            return root;
        }

        if (!curr->right) {
            curr->right = new Node;
            curr->right->data = data;
            curr->right->left = nullptr;
            curr->right->right = nullptr;
            return root;
        }

        q.push(curr->left);
        q.push(curr->right);
    }
}

void bfs(Node* head) {
    queue<Node*> q;
    q.push(head);

    while (!q.empty()) {
#pragma omp parallel for
        for (int i = 0; i < q.size(); i++) {
            Node* curr = q.front();
            q.pop();

            cout << curr->data << endl;

            if (curr->left) {
                q.push(curr->left);
            }

            if (curr->right) {
                q.push(curr->right);
            }
        }
    }
}

void dfs(Node* head) {
    if (!head) {
        return;
    }

#pragma omp parallel
    {
        Node* curr = head;
#pragma omp critical
        {
            cout << curr->data << endl;
        }

        if (curr->left) {
            dfs(curr->left);
        }

        if (curr->right) {
            dfs(curr->right);
        }
    }
}

void printTree(Node* root) {
    if (!root) {
        return;
    }

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();

        cout << "Node: " << curr->data;

        if (curr->left) {
            cout << ", Left Child: " << curr->left->data;
            q.push(curr->left);
        }

        if (curr->right) {
            cout << ", Right Child: " << curr->right->data;
            q.push(curr->right);
        }

        cout << endl;
    }
}

int main() {
    Node* root = nullptr;
    int data;
    char ans;

    do {
        cout << "Enter data: ";
        cin >> data;
        root = insert(root, data);
        cout << "Do you want to insert one more node? (y/n): ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');

    cout << "Binary Tree: " << endl;
    printTree(root);

    cout << "BFS: " << endl;
    bfs(root);

    cout << "DFS: " << endl;
    dfs(root);

    return 0;
}
