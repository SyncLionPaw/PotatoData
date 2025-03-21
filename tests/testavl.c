#include "avl.h"
#include<stdio.h>
#include<assert.h>
#include<limits.h>


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


int main() {
    int (*testFuncs[])() = {
        TestBalance01,
        TestGetHeight01,
        TestGetHeight02,
        TestGetHeight03,
        TestSearch01,
        TestSearch02,
        TestIsValidBst01,
        TestIsValidBst02,
        TestUpdateHeight01,
        TestUpdateHeight02,
        TestLeftRotate01,
        TestRightRotate01,
        TestInsert01,
        TestInsert02,
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