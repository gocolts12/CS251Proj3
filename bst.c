#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

struct bst_node {
	int val;
	int nRight;
	int nLeft;
	struct bst_node *left;
	struct bst_node *right;
};
typedef struct bst_node NODE;


struct bst {
	NODE *root;
	int work;
}; 

BST * bst_create() {
	BST * t = malloc(sizeof(struct bst));
	t->root = NULL;
	return t;
}

static void free_r(NODE *r) {
	if (r == NULL) return;
	free_r(r->left);
	free_r(r->right);
	free(r);
}
void bst_free(BST * t) {
	free_r(t->root);
	free(t);
}

/*
* Write the (recursive) helper function from_arr, used by
* bst_from_sorted_arr(...). The function must return a sub-tree that is
* perfectly balanced, given a sorted array of elements a.
*/
static NODE * from_arr(int *a, int n) {
	int m;
	NODE *root;

	if (n <= 0) return NULL;
	m = n / 2;
	root = malloc(sizeof(NODE));
	root->val = a[m];
	root->nRight = n - (m + 1);
	root->nLeft = m;
	root->left = from_arr(a, m);
	root->right = from_arr(&(a[m + 1]), n - (m + 1));
	return root;
}

BST * bst_from_sorted_arr(int *a, int n) {

	BST * t = bst_create();

	t->root = from_arr(a, n);

	return t;
}


void to_array_helper(NODE *NODE, int *array, int *count)
{
	//Check if the current node is NULL
	if (NODE == NULL)
		return;

	to_array_helper(NODE->left, array, count);

	array[*count] = NODE->val;
	(*count)++;

	to_array_helper(NODE->right, array, count);
}

NODE *balance_array_helper(NODE *r)
{
	int count = 0;
	int size = r->nRight + r->nLeft + 1;
	int *array = malloc(sizeof(int)*size);
	to_array_helper(r, array, &count);
	free_r(r);
	r = from_arr(array, size);
	free(array);
	return r;
}

static NODE * insert(NODE *r, int x) {
	NODE *leaf;
	//If the node is NULL (i.e, the function is passed a child that doesn't exist, 
	//then you are assigning a new leaf to the previous node
	if (r == NULL) {
		leaf = malloc(sizeof(NODE));
		leaf->left = NULL;
		leaf->right = NULL;
		leaf->val = x;
		leaf->nRight = 0;
		leaf->nLeft = 0;
		return leaf;
	}

	//If the node to insert is a duplicate, return r
	if (r->val == x)
		return r;

	//If the node to insert is less than the current node, place to the left
	if (x < r->val) {
		r->nLeft++;
		r->left = insert(r->left, x);
		if (r->nLeft > (2 * r->nRight) + 1)
		{
			r = balance_array_helper(r);
		}
	}

	//The node to insert must be greater than the current node, place to the right
	else {
		r->nRight++;
		r->right = insert(r->right, x);
		if (r->nRight > (2 * r->nLeft) + 1)
		{
			r = balance_array_helper(r);
		}
	}

	return r;

}

// how about an iterative version?
static NODE *insert_i(NODE *r, int x) {

	return NULL;

}


void bst_insert(BST * t, int x) {
	t->root = insert(t->root, x);

//	if (t != NULL)
//	{
//		t->totalNodes++;
//	}
}

int bst_contains(BST * t, int x) {
	NODE *p = t->root;

	while (p != NULL) {

		if (p->val == x)
			return 1;
		if (x < p->val) {
			p = p->left;
		}
		else
			p = p->right;
	}
	return 0;
}

static int min_h(NODE *r) {
	if (r == NULL)
		return -1; // should never happen!
	while (r->left != NULL)
		r = r->left;
	return r->val;
}

static int max_h(NODE *r) {
	if (r == NULL)
		return -1; // should never happen!
	while (r->right != NULL)
		r = r->right;
	return r->val;
}

static NODE *remove_r(NODE *r, int x, int *success) {
	NODE   *tmp;
	int sanity;

	if (r == NULL) {
		*success = 0;
		return NULL;
	}
	if (r->val == x) {
		*success = 1;

		if (r->left == NULL) {
			tmp = r->right;
			free(r);
			return tmp;
		}
		if (r->right == NULL) {
			tmp = r->left;
			free(r);
			return tmp;
		}
		// if we get here, r has two children
		r->val = min_h(r->right);
		r->right = remove_r(r->right, r->val, &sanity);
		if (!sanity)
			printf("ERROR:  remove() failed to delete promoted value?\n");
		return r;
	}
	if (x < r->val) {
		
		r->left = remove_r(r->left, x, success);
	}
	else {
		r->right = remove_r(r->right, x, success);
	}


	return r;

}


int bst_remove(BST * t, int x) {
	int success;
	t->root = remove_r(t->root, x, &success);
	//Make sure that it is successful first
	//t->totalNodes--;
	return success;
}
static int size(NODE *r) {

	if (r == NULL) return 0;
	return size(r->left) + size(r->right) + 1;
}
int bst_size(BST * t) {

	return size(t->root);
}

static int height(NODE *r) {
	int l_h, r_h;

	if (r == NULL) return -1;
	l_h = height(r->left);
	r_h = height(r->right);
	return 1 + (l_h > r_h ? l_h : r_h);

}
int bst_height(BST * t) {
	return height(t->root);

}

int bst_min(BST * t) {
	return min_h(t->root);
}

int bst_max(BST * t) {
	return max_h(t->root);
}

static void indent(int m) {
	int i;
	for (i = 0; i<m; i++)
		printf("-");
}

static void inorder(NODE *r) {
	if (r == NULL) return;
	inorder(r->left);
	printf("[%d]\n", r->val);
	inorder(r->right);

}
void bst_inorder(BST * t) {

	printf("========BEGIN INORDER============\n");
	inorder(t->root);
	printf("=========END INORDER============\n");

}

static void preorder(NODE *r, int margin) {
	if (r == NULL) {
		indent(margin);
		printf("NULL \n");
	}
	else {
		indent(margin);
		printf("%d\n", r->val);
		preorder(r->left, margin + 3);
		preorder(r->right, margin + 3);
	}
}

void bst_preorder(BST * t) {

	printf("========BEGIN PREORDER============\n");
	preorder(t->root, 0);
	printf("=========END PREORDER============\n");

}

/*
* Complete the (recursive) helper function for the post-order traversal.
* Remember: the indentation needs to be proportional to the height of the node!
*/
static void postorder(NODE *r, int margin) {
	/* FILL IN FUNCTION */
}

// indentation is proportional to depth of node being printed
//   depth is #hops from root.
void bst_postorder(BST * t) {

	printf("========BEGIN POSTORDER============\n");
	postorder(t->root, 0);
	printf("=========END POSTORDER============\n");

}

int * bst_to_array(BST * t)
{

	if (t == NULL)
		return 0;
	//Malloc the array and set variables
	int size = t->root->nLeft + t->root->nRight +1;
	//printf("size %d\n", );
	int *array = malloc(sizeof(int) * size);
	int *array = malloc(sizeof(int) * size);
	int count = 0;
	
	//Call recursive function to populate the array
	to_array_helper(t->root, array, &count);

	return array;

}

int num_range_helper(NODE *r, int max, int min)
{
	if (r == NULL)
		return 0;

	if (r->val >= min && r->val <= max)
	{
		return ((1 + num_range_helper(r->left, max, min)) + (num_range_helper(r->right, max, min)));
	}

	else if (r->val < min)
		return num_range_helper(r->right, max, min);
	else
		return num_range_helper(r->left, max, min);
}

int bst_num_range(BST * t, int min, int max)
{
	int range = 0;

	return num_range_helper(t->root, max, min);
}

int geq_helper(NODE *r, int *counter, int x)
{
	if (r == NULL)
		return *counter;

	if (x <= r->val)
	{
		(*counter) += (r->nRight + 1);
		geq_helper(r->left, counter, x);
	}
	else
	{
		geq_helper(r->right, counter, x);
	}

	return *counter;
}

int bst_num_geq(BST * t, int x)
{
	if (t == NULL)
		return 0;

	int counter = 0;

	counter = geq_helper(t->root, &counter, x);

	return counter;
}

int leq_helper(NODE *r, int *counter, int x)
{
	if (r == NULL)
		return *counter;

	if (x >= r->val)
	{
		(*counter) += (r->nLeft + 1);
		leq_helper(r->right, counter, x);
	}
	else
	{
		leq_helper(r->left, counter, x);
	}

	return *counter;
}

int bst_num_leq(BST * t, int x)
{
	if (t == NULL)
		return 0;
	int counter = 0;

	counter = leq_helper(t->root, &counter, x);

	return counter;
}

int ith_helper(NODE *r, int x)
{
	if ((r->nLeft + 1) == x)
		return r->val;
	else if (x > r->nLeft)
	{
		x -= (r->nLeft + 1);
		ith_helper(r->right, x);
	}
	else
	{
		ith_helper(r->left, x);
	}
}

int bst_get_ith(BST * t, int x)
{
	if (t == NULL)
		return 0;

	return ith_helper(t->root, x);
}

void nearest_helper(NODE *r, int x, int *min_diff, int *min_diff_node)
{
	if (r == NULL)
	{
		return;
	}

	if (r->val == x)
	{
		*min_diff_node = x;
		return;
	}

	if (*min_diff > abs(r->val - x))
	{
		*min_diff = abs(r->val - x);
		*min_diff_node = r->val;
	}

	if (x < r->val)
		nearest_helper(r->left, x, min_diff, min_diff_node);
	else
		nearest_helper(r->right, x, min_diff, min_diff_node);
}

int bst_get_nearest(BST * t, int x)
{
	int min_diff = abs(t->root->val - x);
	int min_diff_node = t->root->val;
	if (t == NULL)
		return -1;

	nearest_helper(t->root, x, &min_diff, &min_diff_node);

	return min_diff_node;
}

int bst_sb_work(BST * t)
{
	return t->work;
}