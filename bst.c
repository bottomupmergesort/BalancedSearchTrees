#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node {
	char key;
	struct node* left;
	struct node* right;
};

struct node* insert(struct node* h, char key)
{
	if (h == NULL)
	{
		h = (struct node*)malloc(sizeof(struct node));
		h->key = key;
		h->left = NULL; h->right = NULL;
		return h;
	}
	if (key < h->key) h->left = insert(h->left, key);
	else h->right = insert(h->right, key);
	return h;
}

void walk(struct node* h)
{
	if (h == NULL) return;
	printf("%c ", h->key);
	walk(h->left);
	walk(h->right);
}

int main()
{
	struct node* root = NULL;
	char *str = "ASEARCHINGEXAMPLE";
	puts("Unbalanced BST: ");
	for (int i = 0; i < strlen(str); i++)
		root = insert(root, str[i]);

	walk(root);
	puts("\n-------------- ");
	return 0;
}
