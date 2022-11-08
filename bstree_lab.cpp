//Jordan Brown 
//Lab 12: Binary Search Tree
//18 Apr 2021

#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include "bstree.hpp"
using namespace std;
using CS::BSTree;
using CS::BSTNode;

//Returns the distance that a key is from the root of tree
int BSTree::Depth(const string &key) const
{
	BSTNode *n;
	n = sentinel->right;

	int c = 0;
	
	//node pointer to a single loop, using key to determine direction
	//similar to find function in notes
	while(1){
		if(n == sentinel) break;
		if(key == n->key) return c;
		
		if(key < n->key){
			c++;
			n = n->left;
		} else if(key > n->key){
			c++;
			n = n->right;
		}
	}

	(void) key;
	return -1;
}

//Returns depth of node with maximum depth, plus one
int BSTree::Height() const
{
	BSTNode *n;
	n = sentinel->right;
	return recursive_find_height(n);
}

//return vector of sorted keys
vector <string> BSTree::Ordered_Keys() const
{
	BSTNode *n;
	vector <string> rv;
	
	n = sentinel->right;
	make_key_vector(n, rv);

	return rv;
}
 
//Copy constructor
BSTree::BSTree(const BSTree &t)        
{
	BSTNode *n;

	//(used this from plank notes)
	sentinel = new BSTNode;
	sentinel->left = NULL;
	sentinel->right = sentinel;
	sentinel->parent = NULL;
	sentinel->key = "---SENTINEL---";
	sentinel->val = NULL;
	size = 0;
	

	vector <string> sorted_keys;
	vector <void *> vals;	
	sorted_keys = t.Ordered_Keys();
	vals = t.Ordered_Vals();

	n = make_balanced_tree(sorted_keys, vals, 0, sorted_keys.size());
	sentinel->right = n;

	(void) t;
}

//Assignment overload
BSTree& BSTree::operator= (const BSTree &t) 
{
	BSTNode *n;
	
	vector <string> sorted_keys;
	vector <void *> vals;
	//calls order_keys to get vector of keys in sorted order
	sorted_keys = t.Ordered_Keys();
	//calls ordered_vals to get vector of vals that correspond to the keys
	vals = t.Ordered_Vals();
	
	//create subtree of the given region of keys/vals
	n = make_balanced_tree(sorted_keys, vals, 0, sorted_keys.size());
	sentinel->right = n;
	
	size = sorted_keys.size();

	(void) t;
	return *this;
}

//helper for height
int BSTree::recursive_find_height(const BSTNode *n) const
{
	if(n == sentinel) return 0;
	
	int lDepth, rDepth;
	lDepth = recursive_find_height(n->left);
	rDepth = recursive_find_height(n->right);
	
	if(lDepth > rDepth){ 
		return lDepth + 1;
	} else {	
		return rDepth + 1;
	}

	(void) n;
	return -1;
}

//helper for ordered_keys
void BSTree::make_key_vector(const BSTNode *n, vector<string> &v) const
{
	if(n == sentinel) return;
	
	make_key_vector((n->left), v);
	v.push_back(n->key);
	make_key_vector(n->right, v);

	(void) n;
	(void) v;
}

//helper for copy constructor and assignment overload
BSTNode *BSTree::make_balanced_tree(const vector<string> &sorted_keys, const vector<void *> &vals, 
									size_t first_index, size_t num_indices) const
{
	//BSTNode *n;
	BSTNode *n = new BSTNode;
	int c;
	
	if(num_indices == 0) return sentinel;
	
	c = num_indices / 2;
	
	n->left = make_balanced_tree(sorted_keys, vals, first_index, c);
	//n-1 edges, use middle key as root of the tree(plank notes - implementation)
	n->right = make_balanced_tree(sorted_keys, vals, ((c + first_index)  + 1), (num_indices - 1) / 2);
	n->key = sorted_keys[first_index + c];
	n->val = vals[first_index + c];
	n->left->parent = n;
	n->right->parent = n;

	return n;

	(void) sorted_keys;
	(void) vals;
	(void) first_index;
	(void) num_indices;
	//return NULL;
}














