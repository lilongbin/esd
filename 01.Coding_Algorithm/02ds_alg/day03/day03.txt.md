二叉树




+--------+
| 二叉树 |
+--------+
树也是一种链式存储结构,从树中的每个节点可以走到另外多个节点;
如果树中的所有节点都最多只能走到另外两个节点则这个树叫二叉树;
所有的树都可以转换成二叉树;
所有树都从一个起点节点开始,这个起点节点叫做根节点;
通常使用一个记录根节点地址的指针记录整棵树,这个指针叫根指针;
两个直接相连的节点间有父子关系,靠近根节点的叫父节点;另外一个叫子节点;
树中任何节点都有且只能有一个父节点(根节点除外),一个父节点可以有二个子节点;
在二叉树中任何一个节点最多有两个子节点,我们用左右来区分他们;
树中任何一个节点都可以被看成一棵树的根,这颗树由它自身及它下面的节点构成;
如果某个节点B是另一个节点A的左子节点,那么以节点B为根的树叫节点A的左子树;

struct tree;//先声明有tree结构体,否则编译无法通过
typedef struct node {//node节点结构体(圆圈)
    int num;
    struct tree *p_left;
    struct tree *p_right;
} node;
typedef struct tree {//tree树结构体(方块)
    node *p_root;
} tree;

对树中的所有节点依次进行处理必须要使用递归;
/*
 * 02tree.h
 */
#ifndef __02TREE_H__
#define __02TREE_H__
struct tree;
typedef struct node {
    int num;
    struct tree *p_left;
    struct tree *p_right;
} node;
typedef struct tree {
    node *p_root;
} tree;
#endif //__02TREE_H__
/*
 * 二叉树演示
 * 02tree.c
 */
#include <stdio.h>
#include "02tree.h"
//将树中所有节点的数据打印出来
//这样的问题最适合使用递归来处理
//递归函数必须要有参数,否则递归无法实现
void print(tree *p_tree) {
    /* 不可再分的情况 */
    if (!p_tree || !(p_tree->p_root)) {
        return;
    }
    printf("The former sequence traversal: %d\n", p_tree->p_root->num); //前序遍历

    /* 递归拆分 */
    print(p_tree->p_root->p_left);
    /* printf("In the sequence traversal: %d\n", p_tree->p_root->num); //中序遍历 */
    print(p_tree->p_root->p_right);
    /* printf("After the sequence traversal: %d\n", p_tree->p_root->num); //后序遍历 */
}

/*
 * 静态树的模拟
 * 02main.c
 */
#include <stdio.h>
#include "02tree.h"
int main() {
    tree tr1 = {}, tr2 = {}, tr3 = {};
    node nd1 = {}, nd2 = {}, nd3 = {};
    tr1.p_root = &nd1; //建立如图所示的关系
    tr2.p_root = &nd2;
    tr3.p_root = &nd3;
    nd1.num = 1;
    nd1.p_left = &tr2;
    nd1.p_right = &tr3;
    nd2.num = 2;
    nd3.num = 3;
    print(&tr1);
    return 0;
}

根据对根节点处理的顺序是在左右子节点前/中/后;
将对树的处理分为3种
    前序遍历; //首先处理根节点,再处理左右子节点;
    中序遍历; //首先处理左/右节点,再处理根节点,再处理另一个;
    后序遍历; //首先处理左右节点,再处理根节点;


/*
 * 03tree.h
 */
#ifndef __03TREE_H__
#define __03TREE_H__
struct node;
typedef struct tree {
    struct node *p_root;
} tree;
typedef struct node {
    int num;
    tree left; //直接把结构体塞到节点里面
    tree right; //将tree的定义挪到前面,否则报错incomplete type 
} node;
#endif //__03TREE_H__
/*
 * 二叉树演示
 * 03tree.c
 */
#include <stdio.h>
#include "03tree.h"

void print(tree *p_tree) {
    /* 递归结束的条件 */
    if (!(p_tree->p_root)) {
        return;
    }

    /* 递归拆分 */
    printf("%d\n", p_tree->p_root->num); //前序遍历
    print(&(p_tree->p_root->left));
    print(&(p_tree->p_root->right));
}

/*
 * 树的模拟
 * 03main.c
 */
#include <stdio.h>
#include "03tree.h"

int main() {
    tree tr1 = {};
    node nd1 = {}, nd2 = {}, nd3 = {};

    tr1.p_root = &nd1; //建立如图所示的关系
    nd1.num = 1;
    nd1.left.p_root = &nd2;
    nd1.right.p_root = &nd3;
    nd2.num = 2;
    nd3.num = 3;

    print(&tr1);
    return 0;
}

/*
 * 04tree.h
 */
#ifndef __04TREE_H__
#define __04TREE_H__
struct node;
typedef struct tree {
    struct node *p_root;
} tree;
typedef struct node {
    int num;
    tree left; //直接把结构体塞到节点里面
    tree right; //将tree的定义挪到前面,否则报错incomplete type 
} node;
void print(tree *);
void deinit(tree *);
#endif //__04TREE_H__
/*
 * 二叉树演示
 * 04tree.c
 */
#include <stdio.h>
#include <stdlib.h>
#include "04tree.h"

void print(tree *p_tree) {
    if (!(p_tree->p_root)) {
        return;
    }
    print(&(p_tree->p_root->left));
    print(&(p_tree->p_root->right));

    printf("%d\n", p_tree->p_root->num); //前序遍历
}

void deinit(tree *p_tree) {
    /* 不可再分的情况 */
    if (!(p_tree->p_root)) {
        return;
    }

    /* 递归拆分 */
    deinit(&(p_tree->p_root->left));
    deinit(&(p_tree->p_root->right));

    /* 最后处理root */
    /* 需要采用后序遍历 */
    printf("删除节点: %d\n", p_tree->p_root->num);
    free(p_tree->p_root);
    p_tree->p_root = NULL;
}

/*
 * 树的模拟
 * 04main.c
 */
#include <stdio.h>
#include <stdlib.h>
#include "04tree.h"

int main() {
/*
 *     tree tr1 = {};
 *     node nd1 = {}, nd2 = {}, nd3 = {};
 * 
 *     tr1.p_root = &nd1; //建立如图所示的关系
 *     nd1.num = 1;
 *     nd1.left.p_root = &nd2;
 *     nd1.right.p_root = &nd3;
 *     nd2.num = 2;
 *     nd3.num = 3;
 */
    tree root = {};
    root.p_root = (node*)malloc(sizeof(node));
    if (root.p_root) {
        tree *p_tmp = NULL;
        root.p_root->num = 1;
        root.p_root->left.p_root = NULL;
        root.p_root->right.p_root = NULL;

        /* 左子树 */
        p_tmp = &(root.p_root->left);
        p_tmp->p_root = (node*)malloc(sizeof(node));
        if (p_tmp->p_root) {
            p_tmp->p_root->num = 2;
            p_tmp->p_root->left.p_root = NULL;
            p_tmp->p_root->right.p_root = NULL;
        }

        /* 右子树 */
        p_tmp = &(root.p_root->right);
        p_tmp->p_root = (node*)malloc(sizeof(node));
        if (p_tmp->p_root) {
            p_tmp->p_root->num = 3;
            p_tmp->p_root->left.p_root = NULL;
            p_tmp->p_root->right.p_root = NULL;
        }
    }

    print(&root);
    deinit(&root);
    return 0;
}

/*
 * 05tree.h
 */
#ifndef __05TREE_H__
#define __05TREE_H__
struct node;
typedef struct tree {
    struct node *p_root;
} tree;
typedef struct node {
    int num;
    tree left; //直接把结构体塞到节点里面
    tree right; //将tree的定义挪到前面,否则报错incomplete type 
} node;

void print(tree *);
void deinit(tree *);
tree *search(tree *, int);
#endif //__05TREE_H__
/*
 * 二叉树演示
 * 05tree.c
 */
#include <stdio.h>
#include <stdlib.h>
#include "05tree.h"

void print(tree *p_tree) {
    if (!(p_tree->p_root)) {
        return;
    }
    print(&(p_tree->p_root->left));
    print(&(p_tree->p_root->right));

    printf("%d\n", p_tree->p_root->num); //前序遍历
}

//初始化函数
void init(tree *p_tree) {
    p_tree->p_root = NULL;
}

//删除函数
void deinit(tree *p_tree) {
    if (!(p_tree->p_root)) {
        return;
    }
    deinit(&(p_tree->p_root->left));
    deinit(&(p_tree->p_root->right));

    printf("删除节点: %d\n", p_tree->p_root->num);
    free(p_tree->p_root);
    p_tree->p_root = NULL;
}

//查找某一个数字所在的树
tree *search(tree *p_tree, int num) {
    /* 不可再拆分的情况 */
    if (!(p_tree->p_root)) {
        return NULL;
    }

    tree *p_tmp = NULL;
    /* 如果找到了直接返回 */
    if ((p_tree->p_root->num == num)) {
        /* printf("find out: %d\n", num); */
        return p_tree;
    }
    /* 首先在左子树查找,如果查找结果不为NULL,直接返回结果; */
    /* 否则继续 */
    p_tmp = search(&(p_tree->p_root->left), num);
    if (p_tmp) {
        return p_tmp;
    }
    /* 可以直接返回右子树的查找结果 */
    return search(&(p_tree->p_root->right), num);
}
/*
 * 树的模拟
 * 05main.c
 */
#include <stdio.h>
#include <stdlib.h>
#include "05tree.h"

int main() {
    tree root = {};
    root.p_root = (node*)malloc(sizeof(node));
    if (root.p_root) {
        tree *p_tmp = NULL;
        root.p_root->num = 1;
        root.p_root->left.p_root = NULL;
        root.p_root->right.p_root = NULL;

        /* 左子树 */
        p_tmp = &(root.p_root->left);
        p_tmp->p_root = (node*)malloc(sizeof(node));
        if (p_tmp->p_root) {
            p_tmp->p_root->num = 2;
            p_tmp->p_root->left.p_root = NULL;
            p_tmp->p_root->right.p_root = NULL;
        }

        /* 右子树 */
        p_tmp = &(root.p_root->right);
        p_tmp->p_root = (node*)malloc(sizeof(node));
        if (p_tmp->p_root) {
            p_tmp->p_root->num = 3;
            p_tmp->p_root->left.p_root = NULL;
            p_tmp->p_root->right.p_root = NULL;
        }
    }

    print(&root);

    tree *p_tree = NULL;
    p_tree = search(&root, 2);
    if (p_tree) {
        printf("find out: %d\n", p_tree->p_root->num);
    }
    p_tree = search(&root, 4);
    if (p_tree) {
        printf("find out: %d\n", p_tree->p_root->num);
    } else {
        printf("not find out: 4\n");
    }
    deinit(&root);
    return 0;
}

有序二叉树中任何一个节点左子树上的数字都比它小,而右子树上的所有数字都比它大. 
/*
 * 06tree.h
 */
#ifndef __06TREE_H__
#define __06TREE_H__
struct node;
typedef struct tree {
    struct node *p_root;
} tree;
typedef struct node {
    int num;
    tree left; //直接把结构体塞到节点里面
    tree right; //将tree的定义挪到前面,否则报错incomplete type 
} node;

void print(tree *);
void deinit(tree *);
tree *search(tree *, int);
tree *search_in_order(tree *, int);
#endif //__06TREE_H__
/*
 * 有序二叉树演示
 * 06tree.c
 */
#include <stdio.h>
#include <stdlib.h>
#include "06tree.h"

void print(tree *p_tree) {
    if (!(p_tree->p_root)) {
        return;
    }
    print(&(p_tree->p_root->left));
    printf("%d\n", p_tree->p_root->num); //中序遍历,顺序打印
    print(&(p_tree->p_root->right));
}

//初始化函数
void init(tree *p_tree) {
    p_tree->p_root = NULL;
}

//删除函数
void deinit(tree *p_tree) {
    if (!(p_tree->p_root)) {
        return;
    }
    deinit(&(p_tree->p_root->left));
    deinit(&(p_tree->p_root->right));

    printf("删除节点: %d\n", p_tree->p_root->num);
    free(p_tree->p_root);
    p_tree->p_root = NULL;
}

//查找某一个数字所在的树
tree *search(tree *p_tree, int num) {
    /* 不可再拆分的情况 */
    if (!(p_tree->p_root)) {
        return NULL;
    }

    tree *p_tmp = NULL;
    /* 如果找到了直接返回 */
    if ((p_tree->p_root->num == num)) {
        /* printf("find out: %d\n", num); */
        return p_tree;
    }
    /* 首先在左子树查找,如果查找结果不为NULL,直接返回结果; */
    /* 否则继续 */
    p_tmp = search(&(p_tree->p_root->left), num);
    if (p_tmp) {
        return p_tmp;
    }
    /* 可以直接返回右子树的查找结果 */
    return search(&(p_tree->p_root->right), num);
}

//在有序二叉树中查找
//要求,如果没有查询到返回最后一个查找的tree
tree *search_in_order(tree *p_tree, int num) {
    /* 不可再分的情况 */
    if (!(p_tree->p_root)) {
        return p_tree;
    }

    /* 递归拆分 */
    if (num == p_tree->p_root->num) {
        /* printf("find out: %d\n", num); */
        return p_tree;
    } else if (num < p_tree->p_root->num) {
        return search_in_order(&(p_tree->p_root->left), num);
    } else {
        return search_in_order(&(p_tree->p_root->right), num);
    }
}

/*
 * 有序二叉树
 * 06main.c
 */
#include <stdio.h>
#include <stdlib.h>
#include "06tree.h"

int main() {
    tree root = {};
    root.p_root = (node*)malloc(sizeof(node));
    if (root.p_root) {
        tree *p_tmp = NULL;
        root.p_root->num = 5;
        root.p_root->left.p_root = NULL;
        root.p_root->right.p_root = NULL;

        /* 左子树 */
        p_tmp = &(root.p_root->left);
        p_tmp->p_root = (node*)malloc(sizeof(node));
        if (p_tmp->p_root) {
            p_tmp->p_root->num = 3;
            p_tmp->p_root->left.p_root = NULL;
            p_tmp->p_root->right.p_root = NULL;
        }

        /* 右子树 */
        p_tmp = &(root.p_root->right);
        p_tmp->p_root = (node*)malloc(sizeof(node));
        if (p_tmp->p_root) {
            p_tmp->p_root->num = 9;
            p_tmp->p_root->left.p_root = NULL;
            p_tmp->p_root->right.p_root = NULL;
        }
    }

    print(&root);

    tree *p_tree = NULL;
    p_tree = search_in_order(&root, 3);
    /* 由于没有找到时返回也不为NULL;不能在用p_tree判断; */
    if (p_tree->p_root) {
        printf("find out: %d\n", p_tree->p_root->num);
    }

    deinit(&root);
    return 0;
}

/*
 * 07tree.h
 */
#ifndef __07TREE_H__
#define __07TREE_H__
struct node;
typedef struct tree {
    struct node *p_root;
} tree;
typedef struct node {
    int num;
    tree left; //直接把结构体塞到节点里面
    tree right; //将tree的定义挪到前面,否则报错incomplete type 
} node;

void print(tree *);
void deinit(tree *);
tree *search(tree *, int);
tree *search_in_order(tree *, int);
void insert_in_order(tree *, int);
#endif //__07TREE_H__
/*
 * 有序二叉树演示
 * 07tree.c
 */
#include <stdio.h>
#include <stdlib.h>
#include "07tree.h"

void print(tree *p_tree) {
    if (!(p_tree->p_root)) {
        return;
    }
    print(&(p_tree->p_root->left));
    printf("%d\n", p_tree->p_root->num); //中序遍历才会打印有序结果
    print(&(p_tree->p_root->right));
}

//初始化函数
void init(tree *p_tree) {
    p_tree->p_root = NULL;
}

//删除函数
void deinit(tree *p_tree) {
    if (!(p_tree->p_root)) {
        return;
    }
    deinit(&(p_tree->p_root->left));
    deinit(&(p_tree->p_root->right));

    printf("删除节点: %d\n", p_tree->p_root->num);
    free(p_tree->p_root);
    p_tree->p_root = NULL;
}

//查找某一个数字所在的树
tree *search(tree *p_tree, int num) {
    if (!(p_tree->p_root)) {
        return NULL;
    }

    tree *p_tmp = NULL;
    if ((p_tree->p_root->num == num)) {
        return p_tree;
    }
    p_tmp = search(&(p_tree->p_root->left), num);
    if (p_tmp) {
        return p_tmp;
    }
    return search(&(p_tree->p_root->right), num);
}

//在有序二叉树中查找
//要求,如果没有查询到返回最后一个查找的tree
tree *search_in_order(tree *p_tree, int num) {
    /* 不可再分的情况 */
    if (!(p_tree->p_root)) {
        return p_tree;
    }

    /* 递归拆分 */
    if (num == p_tree->p_root->num) {
        /* printf("find out: %d\n", num); */
        return p_tree;
    } else if (num < p_tree->p_root->num) {
        return search_in_order(&(p_tree->p_root->left), num);
    } else {
        return search_in_order(&(p_tree->p_root->right), num);
    }

    /*
     * 也可以将上面的return替换为一个变量,
     * 然后在最后一句调用return返回变量的值;
     */
}

//按顺序插入新数字
void insert_in_order(tree *p_tree, int num) {
    //查找插入位置
    tree *p_pos = search_in_order(p_tree, num);

    //数字不存在时插入
    if (!(p_pos->p_root)) {
        node *p_tmp = (node *)malloc(sizeof(node));
        p_pos->p_root = p_tmp;
        if (p_tmp) {
            p_tmp->num = num;
            p_tmp->left.p_root = NULL;
            p_tmp->right.p_root = NULL;
        }
    }
}
/*
 * 有序二叉树
 * 07main.c
 */
#include <stdio.h>
#include <stdlib.h>
#include "07tree.h"

int main() {
    tree root = {};
    insert_in_order(&root, 9);
    insert_in_order(&root, 5);
    insert_in_order(&root, 7);
    insert_in_order(&root, 3);
    insert_in_order(&root, 1);
    insert_in_order(&root, 8);

    print(&root);

    tree *p_tree = NULL;
    p_tree = search_in_order(&root, 3);
    /* 由于没有找到时返回也不为NULL;不能在用p_tree判断; */
    if (p_tree->p_root) {
        printf("find out: %d\n", p_tree->p_root->num);
    }

    deinit(&root);
    return 0;
}

统计二叉树的节点数及高度;
/*
 * binary_tree.h
 */
#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__
struct node;
typedef struct tree {//tree树干结构体(方块)
    struct node *p_root;
} tree;
typedef struct node {//node节点结构体(圆圈)
    int num;
    tree left;
    tree right;
} node;

void deinit(tree *);
tree *search(tree *, int);
tree *search_in_order(tree *, int);
void insert_in_order(tree *, int);
int count(tree *);
int height(tree *);
#endif //__BINARY_TREE_H___
/*
 * 二叉树演示
 * binary_tree.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"

void print(tree *p_tree) {
    if (!(p_tree->p_root)) {
        /* printf("递归结束一次\n"); */
        return;
    }

    /* printf("前序遍历%d\n", p_tree->p_root->num); */
    print(&(p_tree->p_root->left));
    printf("中序遍历%d\n", p_tree->p_root->num);
    print(&(p_tree->p_root->right));
    /* printf("后序遍历%d\n", p_tree->p_root->num); */
}

//初始化函数
void init(tree *p_tree) {
    p_tree->p_root = NULL;
}

//清理函数
void deinit(tree *p_tree) {
    if (!(p_tree->p_root)) {
        return;
    }
    deinit(&(p_tree->p_root->left));
    deinit(&(p_tree->p_root->right));

    printf("删除节点%d\n", p_tree->p_root->num);
    free(p_tree->p_root);
    p_tree->p_root = NULL;
}

//查找某一个数字为根的树的结构体变量
tree *search(tree *p_tree, int num) {
    if (!(p_tree->p_root)) {
        return NULL;
    }

    tree *p_tmp = NULL;
    if (p_tree->p_root->num == num) {
        return p_tree;
    }
    p_tmp = search(&(p_tree->p_root->left), num);
    if (p_tmp) {
        return p_tmp;
    }
    return search(&(p_tree->p_root->right), num);
}

//在有序二叉树中查找函数
tree *search_in_order(tree *p_tree, int num) {
    //不可再分的情况
    if (!(p_tree->p_root)) {
        return p_tree;
    }

    //递归拆分
    if (p_tree->p_root->num == num) {
        return p_tree;
    } else if (num < p_tree->p_root->num) {
        return search_in_order(&(p_tree->p_root->left), num);
    } else {
        return search_in_order(&(p_tree->p_root->right), num);
    }
}

//按顺序在有序二叉树中插入新数字
void insert_in_order(tree *p_tree, int num) {
    //查找插入的位置;
    tree *p_inpos = search_in_order(p_tree, num);

    //数字不存在时插入
    if (!(p_inpos->p_root)) {
        node *p_tmp = (node *) malloc(sizeof(node));
        if (p_tmp) {
            p_tmp->num = num;
            p_tmp->left.p_root = NULL;
            p_tmp->right.p_root = NULL;
            p_inpos->p_root = p_tmp;
            printf("insert: %d\n", num);
        }
    }
}

//统计节点个数
int count(tree *p_tree) {
    int cnt = 0;
    if (!(p_tree->p_root)) {
        return 0;
    }

    cnt = count(&(p_tree->p_root->left));
    cnt += count(&(p_tree->p_root->right));
    cnt ++; //最后再加上根节点
    return cnt;
}

//计算树的高度
//只需要分别求出左右子树的高度,然后选择较大的那个+1即可;
int height(tree *p_tree) {
    int lheight = 0, rheight = 0;
    /* 不可拆分的情况 */
    if (!(p_tree->p_root)) {
        return 0;
    }

    /* 递归拆分 */
    lheight = height(&(p_tree->p_root->left));
    rheight = height(&(p_tree->p_root->right));
    return (lheight > rheight ? lheight : rheight) + 1;
}

/*
 * 树的测试
 * main.c
 */
#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"

int main() {
    tree root = { };
    insert_in_order(&root, 9);
    insert_in_order(&root, 5);
    insert_in_order(&root, 7);
    insert_in_order(&root, 3);
    insert_in_order(&root, 1);
    insert_in_order(&root, 8);
    print(&root);

    printf("节点个数是: %d\n", count(&root));
    printf("树的高度是: %d\n", height(&root));

    tree *p_tree = NULL;
    p_tree = search_in_order(&root, 3);
    if (p_tree->p_root) {
        printf("找到的数字: %d\n", p_tree->p_root->num);
    }

    deinit(&root);
    return 0;
}

重点及难点
    处理二叉树的递归方法;
    有序二叉树的查找和顺序插入;
    统计二叉树的节点数及高度;

作业
    给树的数据结构增加统计节点个数及统计树的高度的函数(层);见上例;

