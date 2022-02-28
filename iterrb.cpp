//Iterative Red/Black Tree with dummy nodes.
//MUCH simpler version than what is presented in cormen et. al.
//and used in sys/tree.h
#include <iostream>
#include <stack>
#include <limits>
using namespace std;

int rotcount;
template <class K, class V>
class RB {
	private:
	static const bool red = true;
	static const bool black = false;
	struct node {
		node* l;
		node* r;
		K key;
		V info;
		bool color;
		node(K k, V v, bool c, node* ll, node* rr)
		{ key = k; info = v; color = c; l = ll; r = rr; }
		node()
		{ color = red; l = nullptr; r = nullptr; } 
	};
	typedef node* nodeptr;
	nodeptr head, z;
	nodeptr x, p, g, gg;
	int N;
	K keyMIN, keyMAX;
	V infoMIN, infoMAX;
	nodeptr rotate(K key, nodeptr y)
	{
		nodeptr c, gc;
		c = (key < y->key) ? y->l:y->r;
		if (key < c->key)
		{
			gc = c->l; c->l = gc->r; gc->r = c;
			//cout<<"Right Rotate!\n";
			rotcount++;
		} else {
			rotcount++;
			//cout<<"Left Rotate!\n";
			gc = c->r; c->r = gc->l; gc->l = c;
		}
		if (key < y->key) y->l = gc; else y->r = gc;
		return gc;
	}
	void split(K key)
	{
		x->color = red; x->l->color = black; x->r->color = black;
		if (p->color == red)
		{
			g->color = red;
			if (key < g->key != key < p->key) p = rotate(key, g);
			x = rotate(key, gg);
			x->color = black; 
		}
	}
	void add(K key, V info)
	{
		x = head;
		p = x;
		g = p;
		while (x != z)
		{
			gg = g; g = p; p = x;
			x = (key < x->key) ? x->l:x->r;
			if (x->l->color && x->r->color) split(key);
		}
		x = new node(key, info, red, z, z);
		if (key < p->key) p->l = x;
		else p->r = x;
		split(key);
	}
	public:
	RB()
	{
		keyMIN = std::numeric_limits<K>::min();
		keyMAX = std::numeric_limits<K>::max();
		z = new node(keyMAX, infoMAX, black, nullptr, nullptr);
		z->l = z; z->r = z;
		head = new node(keyMIN, infoMIN, black, nullptr, z);
		N = 0;
	}
	void insert(K key, V info)
	{
		add(key, info);
		head->r->color = black;
	}
	V find(K key)
	{
		x = head->r;
		while (x != z)
		{
			if (key == x->key)
			{
				return x->info;
			}
			x = (key < x->key) ? x->l:x->r;
		}
		return NULL;
	}
	V min()
	{
		x = head->r;
		while (x->l != z)
			x = x->l;
		return x->info;
	}
	
	V max()
	{
		x = head->r;
		while (x->r != z)
			x = x->r;
		return x->info;
	}	
	void show()
	{
		std:;stack<nodeptr> sf;
		sf.push(head->r);
		while (!sf.empty())
		{
			nodeptr curr = sf.top();
			sf.pop();
			if (curr != z)
			{
				cout<<curr->key<<" ";
				//if (curr->color == red) cout<<" red.\n";
				//else cout<<" black.\n";
				sf.push(curr->r);
				sf.push(curr->l);
			}
		}
		cout<<endl;
	}
};

int main()
{
	cout<<"Red Black Tree: \n";
	rotcount = 0;
	string str = "ASEARCHINGEXAMPLE";
	RB<char,char> rbt;
	for (auto c : str)
	{
		rbt.insert(c, c);
	}
	rbt.show();
	cout<<"rotcount: "<<rotcount<<"\n-----------------\n";
	return 0;
}
