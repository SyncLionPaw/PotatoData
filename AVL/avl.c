#include "avl.h"
#include<stdio.h>
#include<assert.h>


int getHeight(TreeNode* root) {
    if(root == NULL) return 0;
    return root->height;
}

int updateHeight(TreeNode* root) {
    if(root == NULL) return 0;
    root->height = MAX(getHeight(root->left), getHeight(root->right)) + 1;
}

// check if root is an valid avl tree
bool isValidAVL(TreeNode* root, int llimit, int rlimit) {
    if(root == NULL) return true;
    if (!(llimit < root->val && root->val < rlimit)) {
        return false;
    }
    return isValidAVL(root->left, llimit, MIN(rlimit, root->val)) &&
        isValidAVL(root->right, MAX(llimit, root->val), rlimit);
}

// search val in root tree
TreeNode* search(TreeNode* root, int target) {
    if(root == NULL) return NULL;
    if(target == root->val) {
        return root;
    } else if (target < root->val) {
        return search(root->left, target);
    }
    return search(root->right, target);
}


// insert value into root avl tree
TreeNode* insert(TreeNode* root, int val) {

}


// apply left rotate operation on root, return new root
TreeNode* leftRotate(TreeNode* root) {
    if(root == NULL) return root;
    
    TreeNode* rchild = root->right; // if operate leftRotate, rchild must not be null
    TreeNode* lOfrchild = rchild->left;

    root->right = lOfrchild;
    rchild->left = root;
    // update height of root and rChild, remember, root first update, then newroot
    // update height, why we only need to update root and child?
    updateHeight(root);
    updateHeight(rchild);
    return rchild;
}