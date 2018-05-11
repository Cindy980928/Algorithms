
#include <stdio.h>
#include "avltree.h"

static int arr[] = { 5,6,8,3,2,4,7 };
#define TBL_SIZE(a) ( (sizeof(a)) / (sizeof(a[0])) )

void main()
{
	int i, ilen;
	AVLTree root = NULL;

	printf("依次添加: ");
	ilen = TBL_SIZE(arr);
	for (i = 0; i<ilen; i++)
	{
		printf("%d ", arr[i]);
		root = avltree_insert(root, arr[i]);
	}


	printf("== 高度: %d\n", avltree_height(root));
	printf("== 树的详细信息: \n");
	print_avltree(root, root->key, 0);


	// 销毁二叉树
	destroy_avltree(root);
}