#include "avl.h"
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>


int getHeight(TreeNode* root) {
    if(root == NULL) return 0;
    return root->height;
}

int updateHeight(TreeNode* root) {
    if(root == NULL) return 0;
    root->height = MAX(getHeight(root->left), getHeight(root->right)) + 1;
}

int balance(TreeNode* root) {
    return root == NULL ? 0: getHeight(root->left) - getHeight(root->right);
}

// check if root is an valid avl tree
bool isValidBst(TreeNode* root, int llimit, int rlimit) {
    if(root == NULL) return true;
    if (!(llimit < root->val && root->val < rlimit)) {
        return false;
    }
    return isValidBst(root->left, llimit, MIN(rlimit, root->val)) &&
        isValidBst(root->right, MAX(llimit, root->val), rlimit);
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

// post order free
void freeTree(TreeNode* root) {
    if(root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
    return;
}

TreeNode* newTreeNode(int val) {
    TreeNode* newRoot = (TreeNode*)malloc(sizeof(TreeNode));
    newRoot->val = val;
    newRoot->height = 1;
    newRoot->left = NULL;
    newRoot->right = NULL;
    return newRoot;
}

// insert value into root avl tree
TreeNode* insert(TreeNode* root, int val) {
    TreeNode* newRoot;
    if(root == NULL) {
        return newTreeNode(val); // always add new node at under leaf
    }
    if(root->val == val) { // no duplicated value
        return root;
    } else if (root->val < val) {
        root->right = insert(root->right, val);
    } else {
        root->left = insert(root->left, val);
    }
    updateHeight(root);
    int bf = balance(root);
    if(bf == 2) {
        int lbf = balance(root->left);
        if(lbf > 0 ) { // or == 1, LL
            newRoot = rightRotate(root);
        } else {      // LR, lrotate left child, then rrotate self
            root->left = leftRotate(root->left);
            newRoot = rightRotate(root);
        }
    } else if (bf == -2) {
        int rbf = balance(root->right);
        if(rbf < 0) { // or == -1, RR
            newRoot = leftRotate(root);
        } else { // RL, rrotate right child, thrn lrotate self
            root->right = rightRotate(root->right);
            newRoot = leftRotate(root);
        }
    } else {
        newRoot = root;
    }
#ifdef DEBUG
    printf("newRoot %d\n", newRoot->val);
#endif
    return newRoot;
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

// apply right rotate operation on root, return new root
TreeNode* rightRotate(TreeNode* root) {
    if(root == NULL) return root;
    
    TreeNode* lchild = root->left; // if operate leftRotate, rchild must not be null
    TreeNode* rOflchild = lchild->right;

    root->left = rOflchild;
    lchild->right = root;
    // update height of root and rChild, remember, root first update, then newroot
    updateHeight(root);
    updateHeight(lchild);
    return lchild;
}

void preOrder(TreeNode* root) {
    if(root == NULL)
        return;
    printf("|%3d  |%2d | %4d    |\n", root->val, root->height, balance(root));
    preOrder(root->left);
    preOrder(root->right);
}

void inOrder(TreeNode* root) {
    if(root == NULL)
        return;
    inOrder(root->left);
    printf("|%3d  |%2d | %4d    |\n", root->val, root->height, balance(root));
    inOrder(root->right);
}

void printInOrder(TreeNode* root, void (*func)(TreeNode* root)) {
    printf("+++ %s +++ \n", __func__);
    printf("+-------------------+\n");
    printf("| val | h | balance |\n");
    printf("+-------------------+\n");
    func(root);
    printf("+-------------------+\n");
}