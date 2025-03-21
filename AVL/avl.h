#include<stdbool.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) <= (b) ? (a) : (b))

// #define DEBUG

typedef struct treeNode {
    int val;
    int height;
    struct treeNode *left, *right;
} TreeNode;

TreeNode* newTreeNode(int val);

// get height of tree node
int getHeight(TreeNode* root);

// update height after rotates
int updateHeight(TreeNode* root);

//get balance factor
int balance(TreeNode* root);

// check if root is an valid bst
bool isValidBst(TreeNode* root, int, int);

// free tree recursively
void freeTree(TreeNode* root);

// search val in root tree
TreeNode* search(TreeNode* root, int target);

// insert value into root avl tree
TreeNode* insert(TreeNode* root, int val);

// apply left rotate operation on root, return new root
TreeNode* leftRotate(TreeNode* root);

// apply right rotate operation on root, return new root
TreeNode* rightRotate(TreeNode* root);

void preOrder(TreeNode* root);

void inOrder(TreeNode* root);

// TODO: delete node from root

void printInOrder(TreeNode* root, void (*func)(TreeNode* root));
