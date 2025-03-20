#include "avl.h"

int getHeight(TreeNode* root) {
    if(root == NULL) return 0;
    return max(getHeight(root->left), getHeight(root.right));
}