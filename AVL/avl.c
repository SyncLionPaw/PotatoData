#include "avl.h"
#include<stdio.h>
#include<assert.h>


int getHeight(TreeNode* root) {
    if(root == NULL) return 0;
    return MAX(getHeight(root->left), getHeight(root->right)) + 1;
}

int TestGetHeight01() {
    TreeNode one = {1, 0, NULL, NULL};
    if(getHeight(&one) == 1) {
        return 1;
    }
    return 0;
}

int TestGetHeight02() {
    TreeNode one = {1, 0, NULL, NULL};
    TreeNode two = {2, 1, NULL, &one};
    if(getHeight(&two) == 2) {
        return 1;
    }
    return 0;
}

int TestGetHeight03() {
    if(getHeight(NULL) == 0) {
        return 1;
    }
    return 0;
}

// check if root is an valid avl tree
bool isValidAVL(TreeNode* root, int llimit, int rlimit) {
    if(root == NULL) return true;
    if (!(llimit < root->val && root->val < rlimit)) {
        return false;
    }
    return isValidAVL(root->left, )
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

int TestSearch01() {
    TreeNode* root = NULL;
    if(search(root, 1) == NULL) {
        return 1;
    }return 0;
}

// insert value into root avl tree
TreeNode* insert(TreeNode* root, int val) {

}

#define TESTCASE 4

int main() {
    int (*testFuncs[TESTCASE])() = {
        TestGetHeight01,
        TestGetHeight02,
        TestGetHeight03,
        TestSearch01
    };
    for(int i=0; i<TESTCASE;i++) {
        int result = testFuncs[i]();
        if(result == 1) {
            printf("\033[32m.\033[0m");
        } else {
            printf("\033[31m.\033[0m");
        }
    }
    printf("\n");
}