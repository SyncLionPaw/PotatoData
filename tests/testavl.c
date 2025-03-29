#include "avl.h"
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <stdlib.h>


int TestGetHeight01() {
    TreeNode one = {1, 1, NULL, NULL};
    if(getHeight(&one) == 1) {
        return 1;
    }
    return 0;
}

int TestGetHeight02() {
    TreeNode one = {1, 1, NULL, NULL};
    TreeNode two = {2, 2, NULL, &one};
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

int TestUpdateHeight01() {
    TreeNode one = {1, 1, NULL, NULL};
    TreeNode three = {3, 1, NULL, NULL};
    TreeNode two = {2, 999, &one, &three};
    updateHeight(&two);
    if(two.height == 2) {
        return 1;
    } return 0;
}

int TestUpdateHeight02() {
    TreeNode one = {1, 22, NULL, NULL}; // fake node
    TreeNode three = {3, 33, NULL, NULL}; // wrong depth
    TreeNode two = {2, -2, &one, &three};
    updateHeight(&two);
    if(two.height == 34) {
        return 1;
    } return 0;
}

int TestBalance01() {
    TreeNode one = {1, 1, NULL, NULL};
    TreeNode two = {2, 2, NULL, &one};
    if(balance(&one) == 0 && balance(&two) == -1) {
        return 1;
    }  return 0;
}

int TestSearch01() { // test search not found
    TreeNode* root = NULL;
    if(search(root, 1) == NULL) {
        return 1;
    }return 0;
}

int TestSearch02() { // search found
    TreeNode one = {1, 0, NULL, NULL};
    TreeNode three = {3, 0, NULL, NULL};
    TreeNode two = {2, 1, &one, &three};
    if(search(&two, 3) == &three) {
        return 1;
    } return 0;
}

int TestSearch03() { // search nt found, cause its not a valid avl tree
    TreeNode one = {1, 0, NULL, NULL};
    TreeNode three = {3, 0, NULL, NULL};
    TreeNode two = {2, 1, &three, &one}; // attention here! it a fake avl tree.
    if(search(&two, 3) == NULL) {
        return 1;
    } return 0;
}

int TestIsValidBst01() {
    TreeNode one = {1, 0, NULL, NULL};
    TreeNode three = {3, 0, NULL, NULL};
    TreeNode two = {2, 1, &three, &one}; // a fake avl tree.
    if(!isValidBst(&two, -INT_MAX, INT_MAX)) { // should be false
        return 1;
    }return 0;
}

int TestIsValidBst02() {
    TreeNode one = {1, 0, NULL, NULL};
    TreeNode three = {3, 0, NULL, NULL};
    TreeNode two = {2, 1, &one, &three}; // valid tree
    if(isValidBst(&two, -INT_MAX, INT_MAX)) {
        return 1;
    }return 0;
}

int TestLeftRotate01() {
    // test left rotate node(5)
    //     5
	//    /  \ 
	//   3    9
	//       / \ 
	//      6   14
    //            \ 
    //            17
    TreeNode seventeen = {17, 1, NULL, NULL};
    TreeNode fourteen = {14, 2, NULL, &seventeen};
    
    TreeNode six = {6, 1, NULL, NULL};

    TreeNode nine = {9, 3, &six, &fourteen};
    TreeNode three = {3, 1, NULL, NULL};
    TreeNode five = {5, 4, &three, &nine};
    TreeNode* newRoot = leftRotate(&five);
    if(newRoot == &nine && five.right == &six && five.height == 2) {
        return 1;
    }return 0;
}

// 正确的做法是对第一个失衡的节点（路径最下面的）进行旋转，这里只是为了测试，所以对7右旋之后还是不平衡
int TestRightRotate01() {
    //     7              3
	//    /  \           /  \ 
	//   3    9         0    7
	//  /\                  /  \ 
	// 0  5                5    9
    //     \                \  
    //      6                6
    TreeNode six = {6, 1, NULL, NULL};
    TreeNode five = {5, 2, NULL, &six};
    TreeNode zero = {0, 1, NULL, NULL};
    TreeNode three = {3, 3, &zero, &five};
    TreeNode nine = {9, 1, NULL, NULL};
    TreeNode seven = {7, 4, &three, &nine};
    TreeNode* newRoot = rightRotate(&seven);
    if(newRoot == &three && seven.height == 3 && three.height == 4) {
        return 1;
    } return 0;
}

int TestInsert01() {
    TreeNode* root = NULL;
    TreeNode* newRoot = insert(root, 1);
    if(newRoot->val == 1 && newRoot->height == 1) {
        freeTree(newRoot);
        return 1;
    }
    freeTree(newRoot);
    return 0;
}

int TestInsert02() {
    TreeNode* root = NULL;
    root = insert(root, 10);
    if (!(root->val == 10 && root->height == 1)) {
        return 0;
    }
    root = insert(root, 20);
    if (!(root->val == 10 && root->right->val == 20 && root->height == 2)) {
        return 0;
    }
    root = insert(root, 30);
    if (!(root->val == 20 && root->height == 2 && 
        root->left->val == 10 && root->right->val == 30)) {
        return 0;
    }
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 60);
#ifdef DEBUG
    preOrder(root);
#endif
}


int TestDelete01() {
    TreeNode* root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = delete(root, 70);
    
    if (isValidBst(root, -INT_MAX, INT_MAX) 
        && balance(root) <= 1 
        && balance(root) >= -1 
        && getHeight(root) == 2) {
        freeTree(root);
        return 1;
    }
    freeTree(root);
    return 0;
}

int TestDelete05() {
    TreeNode* root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);
    
    // 删除40引发双旋转
    root = delete(root, 40);
    
    assert(isValidBst(root, -INT_MAX, INT_MAX));
    assert(abs(balance(root)) <= 1);
    assert(getHeight(root) == 3);
    
    freeTree(root);
    return 1;
}

int TestDelete09() {
    TreeNode* root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    
    // 删除70验证高度更新
    root = delete(root, 70);
    
    assert(getHeight(root) == 3);
    assert(root->left->height == 2);
    freeTree(root);
    return 1;
}

int TestDelete010() {
    TreeNode* root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    
    // 删除不存在节点
    TreeNode* before = root;
    root = delete(root, 999);
    
    assert(root == before);
    assert(isValidBst(root, -INT_MAX, INT_MAX));
    freeTree(root);
    return 1;
}

int TestDelete06() {
    TreeNode* root = newTreeNode(100);
    root = delete(root, 100);
    
    assert(root == NULL);
    assert(isValidBst(root, -INT_MAX, INT_MAX));
    
    freeTree(root);
    return 1;
}

int TestDelete07() {
    TreeNode* root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    
    // 删除70验证高度更新
    assert(getHeight(root) == 3);

    root = delete(root, 70);
    
    assert(root->height == 2);
    freeTree(root);
    return 1;
}


int TestDelete02() {
    TreeNode* root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = delete(root, 30);

    int result = 1;
    
    // 分离每个断言条件
    if (root->val != 50) {
        printf("\nRoot value error! Expected 50, got %d", root->val);
        result = 0;
    }
    
    if (root->left == NULL || root->left->val != 20) {
        printf("\nLeft child error! Expected 20, got %d", root->left ? root->left->val : -1);
        result = 0;
    }
    
    if (root->left->height != 1) {
        printf("\nLeft height error! Expected 1, got %d", root->left->height);
        result = 0;
    }
    
    if (!isValidBst(root, -INT_MAX, INT_MAX)) {
        printf("\nBST validation failed!");
        result = 0;
    }
    
    if (balance(root) != 0) {
        printf("\nBalance factor error! Expected 0, got %d", balance(root));
        result = 0;
    }
    
    if (getHeight(root) != 2) {
        printf("\nTree height error! Expected 2, got %d", getHeight(root));
        result = 0;
    }

    freeTree(root);
    return result;
}

int TestDelete03() {
    TreeNode* root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);
    
    root = delete(root, 50);
    
    int result = 1;
    if (root->val != 60) result = 0;
    if (root->left->val != 30 || root->right->val != 70) result = 0;
    if (root->left->right->val != 40) result = 0;
    if (!isValidBst(root, -INT_MAX, INT_MAX)) result = 0;
    if (abs(balance(root)) > 1) result = 0;
    
    freeTree(root);
    return result;
}

int TestDelete04() {
    TreeNode* root = NULL;
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 10);
    root = insert(root, 25);
    root = insert(root, 35);
    root = insert(root, 50);
    
    root = delete(root, 10);
    root = delete(root, 50);
    
    int result = 1;
    if (root->val != 30) result = 0;
    if (root->left->val != 20 || root->right->val != 40) result = 0;
    if (root->left->right->val != 25) result = 0;
    if (root->right->left->val != 35) result = 0;
    if (getHeight(root) != 3) result = 0;
    
    freeTree(root);
    return result;
}

int TestDelete08() {
    TreeNode* root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    
    // 删除不存在节点
    TreeNode* before = root;
    root = delete(root, 999);
    
    assert(root == before);
    assert(isValidBst(root, -INT_MAX, INT_MAX));
    freeTree(root);
    return 1;
}

int main() {
    int (*testFuncs[])() = {
        TestBalance01,
        TestDelete01,
        TestDelete02,
        TestDelete03,
        TestDelete04,
        TestDelete05,
        TestDelete06,
        TestDelete07,
        TestDelete08,
        TestGetHeight01,
        TestGetHeight02,
        TestGetHeight03,
        TestInsert01,
        TestInsert02,
        TestIsValidBst01,
        TestIsValidBst02,
        TestLeftRotate01,
        TestRightRotate01,
        TestSearch01,
        TestSearch02,
        TestUpdateHeight01,
        TestUpdateHeight02,
    };
    int testCases = sizeof(testFuncs) / sizeof(testFuncs[0]);
    for(int i=0; i<testCases;i++) {
        int result = testFuncs[i]();
        if(result == 1) { // result == 1, means passed testcase.
            printf("\033[32m.\033[0m");
        } else {
            printf("\033[31m.\033[0m");
        }
    }
    printf("\n");
}