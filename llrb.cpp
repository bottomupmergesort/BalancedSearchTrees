#include <iostream>
using namespace std;
int rotcount;
template <class K, class V>
class LLRB {
	private:
	static const bool red = true, black = false;
	struct node {
		K key;
		V val;
		bool color;
		node* left;
		node* right;
		node(K k, V v)
		{
			key = k;
			val = v;
			left = right = nullptr;
			color = red;
		}
	};
	typedef node* nodeptr;
	nodeptr root;
	bool isRed(nodeptr h) { return (h == nullptr) ? false:(h->color == red); }
	void colorFlip(nodeptr& h)
	{
		h->color = red;
		h->left->color = black;
		h->right->color = black;
	}
	void rotL(nodeptr& h)
	{
		rotcount++;
		nodeptr x = h->right; h->right = x->left; x->left = h;
		x->color = h->color; h->color = red;
		h = x;
	}
	void rotR(nodeptr& h)
	{
		rotcount++;
		nodeptr x = h->left; h->left = x->right; x->right = h;
		x->color = h->color; h->color = red;
		h = x;
	}
	void insertR(nodeptr& h, K key, V val)
	{
		if (h == nullptr)
		{
			h = new node(key, val);
			return;
		}

		if (key < h->key) insertR(h->left, key, val);
		else insertR(h->right, key, val);

		if (isRed(h->right) && !isRed(h->left)) rotL(h);
		if (isRed(h->left) && isRed(h->left->left)) rotR(h);
		if (isRed(h->right) && isRed(h->left)) colorFlip(h);
	}
	void show(nodeptr h)
	{
		if (h == nullptr) return;
		cout<<h->key<<" ";
		show(h->left);
		show(h->right);
	}
	public:
	LLRB()
	{
		root = nullptr;
	}
	void insert(K key, V val)
	{
		insertR(root, key, val);
		root->color = black;
	}
	void show()
	{
		show(root);
		cout<<endl;
	}

};


int main()
{
	rotcount = 0;
	cout<<"Left Leaning Red/Black: \n";
	string str = "ASEARCHINGEXAMPLE";
	LLRB<char, char> llrb;
	for (auto c : str)
		llrb.insert(c, c);
	llrb.show();
	cout<<"Rotations: "<<rotcount<<"\n-------------\n";
	return 0;
}
