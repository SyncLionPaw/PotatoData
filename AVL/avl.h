#include<stdbool.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) <= (b) ? (a) : (b))

typedef struct treeNode {
    int val;
    int height;
    struct treeNode *left, *right;
} TreeNode;


// get height of tree node
int getHeight(TreeNode* root);

// update height after rotates
int updateHeight(TreeNode* root);

// check if root is an valid avl tree
bool isValidAVL(TreeNode* root, int, int);

// search val in root tree
TreeNode* search(TreeNode* root, int target);

// insert value into root avl tree
TreeNode* insert(TreeNode* root, int val);

// apply left rotate operation on root, return new root
TreeNode* leftRotate(TreeNode* root);

// TODO: delete node from root
