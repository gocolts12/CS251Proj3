#include <stdio.h>
#include <assert.h>
#include "bst.h"

/**
BARE-BONES DEMO PROGRAM.
You may use this as a starting pint for developing your
testing code
**/

int main() {
	int i;

	int a[] = { 8, 6, 9, 11, 3, 7, 12, 2, 12, 12, 12, 15, 17 };
	int bak[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };

	BST * t = bst_create();

	for (i = 0; i<13; i++)
		bst_insert(t, a[i]);

	//assert(bst_size(t) == 13);

	/*
	printf("AFTER SEQUENTIAL INSERTION OF  {8, 2, 6, 9, 11, 3, 7}\n\n");;
	bst_inorder(t);
	bst_preorder(t);
	bst_free(t);

	printf("NOW TRYING bst_from_sorted_arr()\n\n");
	int sorted_a[] = { 2, 3, 6, 7, 8, 9, 11 };

	t = bst_from_sorted_arr(sorted_a, 7);

	bst_inorder(t);
	bst_preorder(t);
	bst_free(t);

	t = bst_create();
	printf("NOW INSERTING 1...10 in ordern\n");

	for (i = 1; i <= 10; i++)
		bst_insert(t, i);

	bst_inorder(t);
	bst_preorder(t);
	bst_free(t);
	*/

	//int *array = bst_to_array(t);

	//for (i = 0; i < 7; i++)
	//	printf(" %d ", array[i]);
	//int range;

	//range = bst_num_range(t, 2, 10);
	//printf("range: %d\n", range);

	bst_preorder(t);

	int geq = bst_num_geq(t, 10);
	printf("GEQ: %d \n", geq);

	int leq = bst_num_leq(t, 6);
	printf("LEQ: %d \n", leq);

	int ith = bst_get_ith(t, 3);
	printf("ith: %d \n", ith);

	int nearest = bst_get_nearest(t, 14);
	printf("Nearest: %d \n", nearest);

	int range = bst_num_range(t, 0, 11);
	printf("Range = %d \n", range);

	bst_remove(t, 11);
	bst_preorder(t);

	int work = bst_sb_work(t);
	printf("Work: %d", work);

	return 0;
}
