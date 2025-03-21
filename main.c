#include <stdio.h>
#include "avl.h"

int main() {
    printf("请输入数据长度\n");
    int num;
    scanf("%d", &num);
    printf("请输入%d个数据\n", num);
    TreeNode* root = NULL;
    int tmp;
    for(int i=0; i<num; i++) {
        scanf("%d", &tmp);
        root = insert(root, tmp);
        // printInOrder(root, preOrder);
        // printInOrder(root, inOrder);
    }
    printInOrder(root, preOrder);
    printInOrder(root, inOrder);
    
    int target;
    TreeNode* node;
    while(1) {
        printf("请输入查找的关键字, -999 退出 \n"); {
            scanf("%d", &target);
            if(target == -999) {
                break;
            }
            node = search(root, target);
            if (node == NULL) {
                printf("not found\n");
            } else {
                printf("found, <%d|%d|%d>\n", node->val, node->height, balance(node));
            }
        }
    }
    freeTree(root);
}