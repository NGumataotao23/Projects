#include <iostream>

using namespace std;

struct node {
    int key;
    struct node* left;
    struct node* right;
};

struct node* newNode(int item);
struct node* insertBST(struct node* node, int key);
struct node* findBST(struct node* root, int key);
struct node* removeBST(struct node* root, int key);
void insertBSTMenu(struct node* root);
void deleteBSTMenu(struct node* root);
void findBSTMenu(struct node* root);
void displayTree(struct node* root);
void binarySearchTreeMenu(struct node* tree);
struct node* flatten(node* parent);
void revInorder(node* curr, node*& prev);

int main() {
    struct node* root = NULL;
    root = insertBST(root, 8);
    insertBST(root, 4);
    insertBST(root, 2);
    insertBST(root, 5);
    insertBST(root, 12);
    insertBST(root, 29);

    binarySearchTreeMenu(root);
    return 0;
}

void binarySearchTreeMenu(struct node* tree) {
    int input;
    cout << "Welcome to the Binary Search Tree manipulation module" << endl;
    cout << "Please Select an Option: " << endl;
    cout << "1-Find Element in Tree 2-Insert Element in Tree 3-Remove Element from Tree 4-Exit" << endl;
    cin >> input;
    while (input != 4) {
        switch (input) {
            case 1:
                findBSTMenu(tree);
                break;
            case 2:
                insertBSTMenu(tree);
                break;
            case 3:
                deleteBSTMenu(tree);
                break;
            default:
                cout << "Invalid input" << endl;
        }
        cout << "Please Select an Option: " << endl;
        cout << "1-Find Element in Tree 2-Insert Element in Tree 3-Remove Element from Tree 4-Exit" << endl;
        cin >> input;
    }
}

void findBSTMenu(struct node* root) {
    int key;
    cout << "Enter the element you want to find: ";
    cin >> key;
    struct node* result = findBST(root, key);
    if (result != NULL) {
        cout << "Element found in the tree." << endl;
    } else {
        cout << "Element not found in the tree." << endl;
    }
}

void insertBSTMenu(struct node* root) {
    int key;
    cout << "Enter the element you want to insert: ";
    cin >> key;
    insertBST(root, key);
    cout << "Element inserted into the tree." << endl;
}

void deleteBSTMenu(struct node* root) {
    int key;
    cout << "Enter the element you want to delete: ";
    cin >> key;

    removeBST(root, key);
    cout << "Element deleted from the tree." << endl;
}

struct node* insertBST(struct node* node, int key) {
    if (node == NULL) {
        return newNode(key);
    }

    if (key < node->key) {
        node->left = insertBST(node->left, key);
    } else if (key > node->key) {
        node->right = insertBST(node->right, key);
    }

    return node;
}

struct node* findBST(struct node* root, int key) {
    if (root == NULL || root->key == key) {
        return root;
    }

    if (root->key < key) {
        return findBST(root->right, key);
    }

    return findBST(root->left, key);
}

struct node* removeBST(struct node* root, int key) {
    if (root == NULL)
        return root;

    if (root->key > key) {
        root->left = removeBST(root->left, key);
        return root;
    } else if (root->key < key) {
        root->right = removeBST(root->right, key);
        return root;
    }

    if (root->left == NULL) {
        struct node* temp = root->right;
        delete root;
        return temp;
    } else if (root->right == NULL) {
        struct node* temp = root->left;
        delete root;
        return temp;
    } else {
        struct node* succParent = root;
        struct node* succ = root->right;

        while (succ->left != NULL) {
            succParent = succ;
            succ = succ->left;
        }

        if (succParent != root)
            succParent->left = succ->right;
        else
            succParent->right = succ->right;

        root->key = succ->key;
        delete succ;
        return root;
    }
}

struct node* newNode(int item) {
    struct node* temp = new struct node;
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}


