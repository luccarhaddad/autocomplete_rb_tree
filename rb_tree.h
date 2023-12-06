#ifndef RB_TREE_H
#define RB_TREE_H

#include <vector>
#include <string>

enum Color {RED, BLACK};

struct node{
	std::string key;
	long idx;
	node* parent;
	node* right;
	node* left;
	Color color;

	node(std::string key, long idx, node* x):
		key(key),
		idx(idx),
		parent(x),
		right(x),
		left(x),
		color(BLACK) {}
};

class RBTree{
private:
	long _size;
	node* _root;
	node* _nil;

public:
	RBTree(){
		_size = 0;
		_nil = new node("",0,nullptr);
		_root = _nil;
	}
	long size();        
	void add (std::string key, long idx);
	void find(std::vector<long> &res, std::string first, std::string last);
	void leftRotate(node* x);
	void rightRotate(node* x);
	void findInRange(std::vector<long> &res, std::string first, std::string last, node* p);
	void insertFixup(node* z);
};
#endif