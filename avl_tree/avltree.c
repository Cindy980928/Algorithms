/**
* AVL树(C语言): C语言实现的AVL树。
*
* @author skywang
* @date 2013/11/07
*/

#include <stdio.h>
#include <stdlib.h>
#include "avltree.h"

#define HEIGHT(p)    ( (p==NULL) ? -1 : (((Node *)(p))->height) )
#define MAX(a, b)    ( (a) > (b) ? (a) : (b) )

/*
* 获取AVL树的高度
*/
int avltree_height(AVLTree tree)
{
	return HEIGHT(tree);
}


/*
* LL：左左对应的情况(左单旋转)。
*
* 返回值：旋转后的根节点
*/
static Node* left_left_rotation(AVLTree k2)
{
	AVLTree k1;

	k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;

	k2->height = MAX(HEIGHT(k2->left), HEIGHT(k2->right)) + 1;
	k1->height = MAX(HEIGHT(k1->left), k2->height) + 1;

	return k1;
}

/*
* RR：右右对应的情况(右单旋转)。
*
* 返回值：旋转后的根节点
*/
static Node* right_right_rotation(AVLTree k1)
{
	AVLTree k2;

	k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;

	k1->height = MAX(HEIGHT(k1->left), HEIGHT(k1->right)) + 1;
	k2->height = MAX(HEIGHT(k2->right), k1->height) + 1;

	return k2;
}

/*
* LR：左右对应的情况(左双旋转)。
*
* 返回值：旋转后的根节点
*/
static Node* left_right_rotation(AVLTree k3)
{
	k3->left = right_right_rotation(k3->left);

	return left_left_rotation(k3);
}

/*
* RL：右左对应的情况(右双旋转)。
*
* 返回值：旋转后的根节点
*/
static Node* right_left_rotation(AVLTree k1)
{
	k1->right = left_left_rotation(k1->right);

	return right_right_rotation(k1);
}

/*
* 创建AVL树结点。
*
* 参数说明：
*     key 是键值。
*     left 是左孩子。
*     right 是右孩子。
*/
static Node* avltree_create_node(Type key, Node *left, Node* right)
{
	Node* p;

	if ((p = (Node *)malloc(sizeof(Node))) == NULL)
		return NULL;
	p->key = key;
	p->height = 0;
	p->left = left;
	p->right = right;

	return p;
}

/*
* 将结点插入到AVL树中，并返回根节点
*
* 参数说明：
*     tree AVL树的根结点
*     key 插入的结点的键值
* 返回值：
*     根节点
*/
Node* avltree_insert(AVLTree tree, Type key)
{
	if (tree == NULL)
	{
		// 新建节点
		tree = avltree_create_node(key, NULL, NULL);
		if (tree == NULL)
		{
			printf("ERROR: create avltree node failed!\n");
			return NULL;
		}
	}
	else if (key < tree->key) // 应该将key插入到"tree的左子树"的情况
	{
		tree->left = avltree_insert(tree->left, key);
		// 插入节点后，若AVL树失去平衡，则进行相应的调节。
		if (HEIGHT(tree->left) - HEIGHT(tree->right) == 2)
		{
			if (key < tree->left->key)
				tree = left_left_rotation(tree);
			else
				tree = left_right_rotation(tree);
		}
	}
	else if (key > tree->key) // 应该将key插入到"tree的右子树"的情况
	{
		tree->right = avltree_insert(tree->right, key);
		// 插入节点后，若AVL树失去平衡，则进行相应的调节。
		if (HEIGHT(tree->right) - HEIGHT(tree->left) == 2)
		{
			if (key > tree->right->key)
				tree = right_right_rotation(tree);
			else
				tree = right_left_rotation(tree);
		}
	}
	else //key == tree->key)
	{
		printf("添加失败：不允许添加相同的节点！\n");
	}

	tree->height = MAX(HEIGHT(tree->left), HEIGHT(tree->right)) + 1;

	return tree;
}


/*
* 销毁AVL树
*/
void destroy_avltree(AVLTree tree)
{
	if (tree == NULL)
		return;

	if (tree->left != NULL)
		destroy_avltree(tree->left);
	if (tree->right != NULL)
		destroy_avltree(tree->right);

	free(tree);
}

/*
* 打印"AVL树"
*
* tree       -- AVL树的节点
* key        -- 节点的键值
* direction  --  0，表示该节点是根节点;
*               -1，表示该节点是它的父结点的左孩子;
*                1，表示该节点是它的父结点的右孩子。
*/
void print_avltree(AVLTree tree, Type key, int direction)
{
	if (tree != NULL)
	{
		if (direction == 0)    // tree是根节点
			printf("%2d 是根节点\n", tree->key);
		else                // tree是分支节点
			printf("%2d 是 %2d 的 %6s child\n", tree->key, key, direction == 1 ? "右" : "左");

		print_avltree(tree->left, tree->key, -1);
		print_avltree(tree->right, tree->key, 1);
	}
}