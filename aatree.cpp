#include <iostream>
using namespace std;
int rotcount;
template <class K, class V>
class AATree {
    private:
    struct node {
        K key;
        V val;
        node* left;
        node* right;
        int height;
        node(K k, V v, int ht)
        { key = k; val = v; left = right = nullptr; height = ht; }
        node()
        { left = right = nullptr; height = 0; }
    };
    typedef node* nodeptr;
    bool isNil(nodeptr h) { return (h==nullptr); }
    int level(nodeptr h) { return (h == nullptr) ? 0:h->height; }
    nodeptr split(nodeptr h)
    {
        if (isNil(h))
        {
            return nullptr;
        } else if (isNil(h->left)) {
            return h;
        } else if (level(h) == level(h->left)) {
	    rotcount++;
//            cout<<"Right Rotate!\n";
            nodeptr x = h->left;
            h->left = x->right;
            x->right = h;
            return x;
        } else {
            return h;
        }
    }
    nodeptr skew(nodeptr h)
    {
        if (isNil(h)) {
            return nullptr;
        } else if (isNil(h->right) || isNil(h->right->right)) {
            return h;
        } else if (level(h) == level(h->right->right)) {
//            cout<<"Left rotate!\n";
	    rotcount++;
            nodeptr x = h->right;
            h->right = x->left;
            x->left = h;
            x->height++;
            return x;
        } else {
            return h;
        }
    }
    nodeptr add(nodeptr h, K key, V val)
    {
        if (h == nullptr)
        {
            return new node(key, val, 1);
        }
        if (key < h->key) h->left = add(h->left, key, val);
        else h->right = add(h->right, key, val);
        h = skew(h);
        h = split(h);
        return h;
    }
    void walk(nodeptr h)
    {
        if (h != nullptr)
        {
            cout<<h->key<<" ";
            walk(h->left);
            walk(h->right);
        }
    }
    nodeptr root;
    public:
    AATree()
    {
        root = nullptr;
    }
    void insert(K key, V val)
    {
        root = add(root, key, val);
    }
    void show()
    {
        walk(root);
	cout<<endl;
    }
};

int main()
{
  cout<<"AA Tree: \n";
  rotcount = 0;
    string str = "ASEARCHINGEXAMPLE";
    AATree<char, char> rr;
    for (auto c : str)
        rr.insert(c, c);

    rr.show();
    cout<<"Rotations: "<<rotcount<<"\n-----------------\n";
    return 0;
}
