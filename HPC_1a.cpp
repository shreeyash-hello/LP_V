#include <iostream>
#include <queue>

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

    bfs(root);

    return 0;
}
