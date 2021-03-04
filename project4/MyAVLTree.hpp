#ifndef __PROJ_THREE_AVL_HPP
#define __PROJ_THREE_AVL_HPP

#include "runtimeexcept.hpp"
#include <string>
#include <vector>
#include <iostream>

class ElementNotFoundException : public RuntimeException 
{
public:
	ElementNotFoundException(const std::string & err) : RuntimeException(err) {}
};

template<typename Key, typename Value>
struct Node
{
    Key key;
    Value value;
    Node* left;
    Node* right;
    int height = 0;
};


template<typename Key, typename Value>
class MyAVLTree
{
private:
	// fill in private member data here
	// If you need to declare private functions, do so here too.
    size_t sz;
    Node<Key, Value>* root;

    // private function:
    void getInOrder(Node<Key, Value>* current, std::vector<Key>& foo) const;
    void getPreOrder(Node<Key, Value>* current, std::vector<Key>& foo) const;
    void getPostOrder(Node<Key, Value>* current, std::vector<Key>& foo) const;
    Node<Key, Value>* myInsert(Node<Key, Value>* current, const Key& k, const Value& v);
    void deleteTree(Node<Key, Value>* current);
    int getHeight(Node<Key, Value>* node);

    Node<Key, Value>* lrBalance(Node<Key, Value>* z);
    Node<Key, Value>* llBalance(Node<Key, Value>* z);
    Node<Key, Value>* rlBalance(Node<Key, Value>* z);
    Node<Key, Value>* rrBalance(Node<Key, Value>* z);


public:
	MyAVLTree();

	// In general, a copy constructor and assignment operator
	// are good things to have.
	// For this quarter, I am not requiring these. 
	//	MyAVLTree(const MyAVLTree & st);
	//	MyAVLTree & operator=(const MyAVLTree & st);


	// The destructor is, however, required. 
	~MyAVLTree()
	{
		// TODO
        deleteTree(root);        
	}

	// size() returns the number of distinct keys in the tree.
	size_t size() const noexcept;

	// isEmpty() returns true if and only if the tree has no values in it. 
	bool isEmpty() const noexcept;

	// contains() returns true if and only if there
	//  is a (key, value) pair in the tree
	//	that has the given key as its key.
	bool contains(const Key & k) const; 

	// find returns the value associated with the given key
	// If !contains(k), this will throw an ElementNotFoundException
	// There needs to be a version for const and non-const MyAVLTrees.
	Value & find(const Key & k);
	const Value & find(const Key & k) const;

	// Inserts the given key-value pair into 
	// the tree and performs the AVL re-balance
	// operation, as described in lecture. 
	// If the key already exists in the tree, 
	// you may do as you please (no test cases in
	// the grading script will deal with this situation)
	void insert(const Key & k, const Value & v);

	// in general, a "remove" function would be here
	// It's a little trickier with an AVL tree
	// and I am not requiring it for this quarter's ICS 46.
	// You should still read about the remove operation
	// in your textbook. 

	// The following three functions all return
	// the set of keys in the tree as a standard vector.
	// Each returns them in a different order.
	std::vector<Key> inOrder() const;
	std::vector<Key> preOrder() const;
	std::vector<Key> postOrder() const;


};


template<typename Key, typename Value>
MyAVLTree<Key,Value>::MyAVLTree()
    : sz{0}, root{nullptr}
{
}

template<typename Key, typename Value>
size_t MyAVLTree<Key, Value>::size() const noexcept
{
	return sz;
}

template<typename Key, typename Value>
bool MyAVLTree<Key, Value>::isEmpty() const noexcept
{
	return (sz == 0);
}


template<typename Key, typename Value>
bool MyAVLTree<Key, Value>::contains(const Key &k) const
{
	Node<Key, Value>* temp = root;
    while (temp != nullptr)
    {
        if (temp->key == k) {return true;}
        else if (temp->key < k) {temp = temp->right;}
        else {temp = temp->left;}
    }
    return false;
}



template<typename Key, typename Value>
Value & MyAVLTree<Key, Value>::find(const Key & k)
{
    Node<Key, Value>* temp = root;
    while (temp != nullptr)
    {
        if (temp->key == k) {return temp->value;}
        else if (temp->key < k) {temp = temp->right;}
        else {temp = temp->left;}
    }
    throw ElementNotFoundException("The key is not in tree");
	//return v; 
}

template<typename Key, typename Value>
const Value & MyAVLTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value>* temp = root;
    while (temp != nullptr)
    {
        if (temp->key == k) {return temp->value;}
        else if (temp->key < k) {temp = temp->right;}
        else {temp = temp->left;}
    }
    throw ElementNotFoundException("The key is not in tree");
}

template<typename Key, typename Value>
void MyAVLTree<Key, Value>::insert(const Key & k, const Value & v)
// use recursion to insert (key, value)
{
    // if key already in the tree, skip it 
    if (contains(k)) {return;}	
    sz++;
    root = myInsert(root, k, v);   // recursive function to insert key
}




template<typename Key, typename Value>
std::vector<Key> MyAVLTree<Key, Value>::inOrder() const
{
	std::vector<Key> foo;
    getInOrder(root, foo);
	return foo; 
}


template<typename Key, typename Value>
std::vector<Key> MyAVLTree<Key, Value>::preOrder() const
{
	std::vector<Key> foo;
    getPreOrder(root, foo);
	return foo; 
}


template<typename Key, typename Value>
std::vector<Key> MyAVLTree<Key, Value>::postOrder() const
{
	std::vector<Key> foo;
    getPostOrder(root, foo);
	return foo; 
}


// helper function
template<typename Key, typename Value>
void MyAVLTree<Key, Value>::getInOrder(Node<Key, Value>* current, std::vector<Key>& foo) const
{
    if (current != nullptr)
    {
        getInOrder(current->left, foo);
        foo.push_back(current->key);
        getInOrder(current->right, foo);
    }
}

template<typename Key, typename Value>
void MyAVLTree<Key, Value>::getPreOrder(Node<Key, Value>* current, std::vector<Key>& foo) const
{
    if (current != nullptr)
    {
        foo.push_back(current->key);
        getPreOrder(current->left, foo);
        getPreOrder(current->right, foo);
    }
}

template<typename Key, typename Value>
void MyAVLTree<Key, Value>::getPostOrder(Node<Key, Value>* current, std::vector<Key>& foo) const
{
    if (current != nullptr)
    {
        getPostOrder(current->left, foo);
        getPostOrder(current->right, foo);
        foo.push_back(current->key);
    }
}



template<typename Key, typename Value>
Node<Key, Value>* MyAVLTree<Key, Value>::myInsert(Node<Key, Value>* current, const Key& k, const Value& v) 
{
    //if tree is empty, make root directly point to the new (k,v
    if (current == nullptr)
    {
        return new Node<Key, Value>{k, v, nullptr, nullptr};
    }
    
    else
    {
        // right side
        if (current->key < k) { current->right = myInsert(current->right, k, v);}
        // left side
        else if (k < current->key) { current->left = myInsert(current->left, k, v);}
        else { return current; }
    }

    current->height = std::max(getHeight(current->left), getHeight(current->right)) + 1;
    int d = getHeight(current->left) - getHeight(current->right);
   
    // left-right
    if (d > 1 && current->left->key < k)
    {
        return lrBalance(current);
    }
    // left-left
    if (d > 1 && k < current->left->key)
    {
        return llBalance(current);
    }
    // right-left
    if (d < -1 && k < current->right->key)
    {
        return rlBalance(current);
    }
    // right-right
    if (d < -1 && current->right->key < k)
    {
        return rrBalance(current);
    }
    
    return current;
}

template<typename Key, typename Value>
Node<Key, Value>* MyAVLTree<Key, Value>::lrBalance(Node<Key, Value>* z)
{
    z->left = rrBalance(z->left);
    return llBalance(z);
}

template<typename Key, typename Value>
Node<Key, Value>* MyAVLTree<Key, Value>::llBalance(Node<Key, Value>* z)
{
    Node<Key, Value>* y = z->left;
    Node<Key, Value>* T3 = y->right;

    z->left = T3;
    y->right = z;

    z->height = std::max(getHeight(z->left), getHeight(z->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

template<typename Key, typename Value>
Node<Key, Value>* MyAVLTree<Key, Value>::rrBalance(Node<Key, Value>* z)
{
    Node<Key, Value>* y = z->right;
    Node<Key, Value>* T2 = y->left;

    z->right = T2;
    y->left = z;

    z->height = std::max(getHeight(z->left), getHeight(z->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

template<typename Key, typename Value>
Node<Key, Value>* MyAVLTree<Key, Value>::rlBalance(Node<Key, Value>* z)
{
    z->right = llBalance(z->right);
    return rrBalance(z);
}

template<typename Key, typename Value>
int MyAVLTree<Key, Value>::getHeight(Node<Key, Value>* node)
{
    if (node != nullptr) { return node->height; }
    return -1;
}

template<typename Key, typename Value>
void MyAVLTree<Key, Value>::deleteTree(Node<Key, Value>* current)
{
    if (current->left != nullptr)
    {
        deleteTree(current->left);
    }
    if (current->right != nullptr)
    {
        deleteTree(current->right);
    }
    delete current;
}


#endif 
