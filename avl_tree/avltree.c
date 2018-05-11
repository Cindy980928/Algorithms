/**
* AVL��(C����): C����ʵ�ֵ�AVL����
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
* ��ȡAVL���ĸ߶�
*/
int avltree_height(AVLTree tree)
{
	return HEIGHT(tree);
}


/*
* LL�������Ӧ�����(����ת)��
*
* ����ֵ����ת��ĸ��ڵ�
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
* RR�����Ҷ�Ӧ�����(�ҵ���ת)��
*
* ����ֵ����ת��ĸ��ڵ�
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
* LR�����Ҷ�Ӧ�����(��˫��ת)��
*
* ����ֵ����ת��ĸ��ڵ�
*/
static Node* left_right_rotation(AVLTree k3)
{
	k3->left = right_right_rotation(k3->left);

	return left_left_rotation(k3);
}

/*
* RL�������Ӧ�����(��˫��ת)��
*
* ����ֵ����ת��ĸ��ڵ�
*/
static Node* right_left_rotation(AVLTree k1)
{
	k1->right = left_left_rotation(k1->right);

	return right_right_rotation(k1);
}

/*
* ����AVL����㡣
*
* ����˵����
*     key �Ǽ�ֵ��
*     left �����ӡ�
*     right ���Һ��ӡ�
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
* �������뵽AVL���У������ظ��ڵ�
*
* ����˵����
*     tree AVL���ĸ����
*     key ����Ľ��ļ�ֵ
* ����ֵ��
*     ���ڵ�
*/
Node* avltree_insert(AVLTree tree, Type key)
{
	if (tree == NULL)
	{
		// �½��ڵ�
		tree = avltree_create_node(key, NULL, NULL);
		if (tree == NULL)
		{
			printf("ERROR: create avltree node failed!\n");
			return NULL;
		}
	}
	else if (key < tree->key) // Ӧ�ý�key���뵽"tree��������"�����
	{
		tree->left = avltree_insert(tree->left, key);
		// ����ڵ����AVL��ʧȥƽ�⣬�������Ӧ�ĵ��ڡ�
		if (HEIGHT(tree->left) - HEIGHT(tree->right) == 2)
		{
			if (key < tree->left->key)
				tree = left_left_rotation(tree);
			else
				tree = left_right_rotation(tree);
		}
	}
	else if (key > tree->key) // Ӧ�ý�key���뵽"tree��������"�����
	{
		tree->right = avltree_insert(tree->right, key);
		// ����ڵ����AVL��ʧȥƽ�⣬�������Ӧ�ĵ��ڡ�
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
		printf("���ʧ�ܣ������������ͬ�Ľڵ㣡\n");
	}

	tree->height = MAX(HEIGHT(tree->left), HEIGHT(tree->right)) + 1;

	return tree;
}


/*
* ����AVL��
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
* ��ӡ"AVL��"
*
* tree       -- AVL���Ľڵ�
* key        -- �ڵ�ļ�ֵ
* direction  --  0����ʾ�ýڵ��Ǹ��ڵ�;
*               -1����ʾ�ýڵ������ĸ���������;
*                1����ʾ�ýڵ������ĸ������Һ��ӡ�
*/
void print_avltree(AVLTree tree, Type key, int direction)
{
	if (tree != NULL)
	{
		if (direction == 0)    // tree�Ǹ��ڵ�
			printf("%2d �Ǹ��ڵ�\n", tree->key);
		else                // tree�Ƿ�֧�ڵ�
			printf("%2d �� %2d �� %6s child\n", tree->key, key, direction == 1 ? "��" : "��");

		print_avltree(tree->left, tree->key, -1);
		print_avltree(tree->right, tree->key, 1);
	}
}