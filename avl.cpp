#include <iostream>
#include <stack>
using namespace std;

char name(int k) { return 'A' + k - 1; }
int rotcount;
class BinarySearchTree {
	protected:
	struct node {
		node* left;
		node* right;
		int height;
		int key;
		node(int k) { key = k; height = 0; left = right = nullptr; }
		node() { key = 0; height = 0; left = right = nullptr; }
	};
	typedef node* nodeptr;
	nodeptr root;
	int height(nodeptr h) { return (h == nullptr) ? 0:h->height; }
	int balFac(nodeptr h) { return (h == nullptr) ? 0:(height(h->left) - height(h->right)); }
	node* rotateRight(nodeptr h)
	{
		rotcount++;
//		cout<<"RR"<<endl;
			nodeptr x = h->left; h->left = x->right; x->right = h;
			h->height = std::max(height(h->left), height(h->right)) + 1;
			x->height = std::max(height(x->left), height(x->right)) + 1;
			return x;
	}
	node* rotateLeft(nodeptr h)
	{
		rotcount++;
//		cout<<"RL"<<endl;
			nodeptr x = h->right; h->right = x->left; x->left = h;
			h->height = std::max(height(h->left), height(h->right)) + 1;
			x->height = std::max(height(x->left), height(x->right)) + 1;
			return x;			
	}
	node* balance(nodeptr h, int key)
	{
		h->height = std::max(height(h->left), height(h->right)) + 1;
		int bal = balFac(h);

		if (bal > 1 && key < h->left->key)
			return rotateRight(h);
		if (bal < -1 && key > h->right->key)
			return rotateLeft(h);
		if (bal > 1 && key > h->left->key)
		{
			h->left = rotateLeft(h->left);
			return rotateRight(h);
		}
		if (bal < -1 && key < h->right->key)
		{
			h->right = rotateRight(h->right);
			return rotateLeft(h);
		}
		return h;
	}
	void insert(node*& h, int key)
	{
		if (h == nullptr)
		{
			h = new node(key);
			return;
		}
		if (key < h->key) insert(h->left, key);
		else insert(h->right, key);
		h = balance(h, key);
	}
	void preorder(nodeptr h)
	{
		if (h == nullptr) return;
		cout<<char(h->key)<<" ";
		preorder(h->left);
		preorder(h->right);
	}
	public:
	BinarySearchTree()
	{
		root = nullptr;
	}
	void insert(int key)
	{
		insert(root, key);
	}
	void show()
	{
		preorder(root);
		cout<<endl;
	}
};

int main(int argc, char **argv)
{
	cout<<"AVL Tree: \n";
	rotcount = 0;
	BinarySearchTree bst;
	/*for (int i = 0; i < 10; i++)
	{
			int p = rand() % 50;
			cout<<"inserting: "<<p<<endl;
			bst.insert(p);
	}*/
	string str = "ASEARCHINGEXAMPLE";
	for (auto c : str)
		bst.insert(c);
	bst.show();
	cout<<"Rotations: "<<rotcount<<"\n-----------\n";
	return 0;
}

