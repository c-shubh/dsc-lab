#include <stdio.h>
#include <stdlib.h>

struct BSTreeNode 
{
	struct BSTreeNode *lsTree;
	struct BSTreeNode *rsTree;
	int data;
};
typedef struct BSTreeNode BSTree;

BSTree * newNode(int elem)
{
	// allocate memory for BSTree node
	BSTree *pNew = malloc(sizeof(BSTree));
	// initialize members
	pNew->data = elem;
	pNew->lsTree = pNew->rsTree = NULL;
	return pNew;
}

void inorder(BSTree *root)
{
	if(root == NULL)
		return;
	inorder(root->lsTree);
	printf("%d ", root->data);
	inorder(root->rsTree);
}

BSTree * findMaxNode(BSTree *root)
{
	while(root != NULL && root->rsTree != NULL)
		root = root->rsTree;
	return root;
}

BSTree * findMinNode(BSTree *root)
{
	while(root != NULL && root->lsTree != NULL)
		root = root->lsTree;
	return root;
}

BSTree * insert(BSTree *root, int elem)
{
	// if root is null, new node is the root
	if(root == NULL)
		root = newNode(elem);
	else if(elem < root->data) // delegate insertion to right subtree
		root->lsTree = insert(root->lsTree, elem);
	else if(elem > root->data) // delegate insertion to left subtree
		root->rsTree = insert(root->rsTree, elem);
	return root;
}

BSTree * delete(BSTree *root, int elem)
{
	if(root == NULL) // elem not in tree
		return NULL;
	
	if(root->data == elem)
	{
		BSTree *pDel = NULL;
		
		// root is a leaf node
		if(root->lsTree == NULL && root->rsTree == NULL)
		{
			pDel = root;
			root = NULL; // logical deletion
			free(pDel); // physical deletion
			return root;
		}
		
		// root has one child (left child)
		if(root->lsTree != NULL && root->rsTree == NULL)
		{
			pDel = root;
			root = root->lsTree;
			free(pDel);
			return root;
		}
		
		// root has one child (right child)
		if(root->lsTree == NULL && root->rsTree != NULL)
		{
			pDel = root;
			root = root->rsTree;
			free(pDel);
			return root;
		}
		
		// root has two children
		if(root->lsTree != NULL && root->rsTree != NULL)
		{
			// find inorder successor of RST for deleting node
			BSTree *minRst = findMinNode(root->rsTree);
			root->data = minRst->data;
			root->rsTree = delete(root->rsTree, minRst->data);
			return root;
		}
	}

	if(elem < root->data) // elem belongs to LST
		root->lsTree = delete(root->lsTree, elem);
	else if(elem > root->data) // elem belongs to RST
		root->rsTree = delete(root->rsTree, elem);
	
	return root;
}

BSTree * search(BSTree *root, int key)
{
	while(root != NULL)
	{
		// key found
		if(key == root->data)
			return root;
		else if(key > root->data)
			root = root->rsTree;
		else 
			root = root->lsTree;
	}
	// key not found
	return NULL;
}


int main(void)
{
	BSTree *root = NULL;
	int n, input;
	printf("Enter number of elements: ");
	scanf("%d", &n);
	printf("Enter %d elements: ", n);
	for(int i=0; i<n; i++)
	{
		scanf("%d", &input);
		root = insert(root, input);
	}
	
	printf("BST elements are: ");
	inorder(root);
	printf("\n");
	
	printf("Maximum value: %d\n", findMaxNode(root)->data);
	printf("Minimum value: %d\n", findMinNode(root)->data);
	
	int delElem;
	printf("Enter element to delete: ");
	scanf("%d", &delElem);
	
	printf("After deleting %d:\n", delElem);
	root = delete(root, delElem);
	inorder(root);
	printf("\n");

	int key;
	printf("Enter key to search: ");
	scanf("%d", &key);
	BSTree *res = search(root, key);
	if(res == NULL)
		printf("%d not in tree.\n", key);
	else 
		printf("%d found in tree.\n", key);

	printf("\n");
	return 0;
}
