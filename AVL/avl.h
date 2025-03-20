#include<stdbool.h>

typedef struct treeNode {
    int val;
    struct treeNode* left, right;
    int height;
} TreeNode;


// get height of tree node
int getHeight(TreeNode* root);

// check if root is an valid avl tree
bool isValidAVL(TreeNode* root);

// search val in root tree
TreeNode* search(TreeNode* root, int target);

// insert value into root avl tree
TreeNode* insert(TreeNode* root, int val);

// TODO: delete node from root
