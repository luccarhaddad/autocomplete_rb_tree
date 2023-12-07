#ifndef RB_TREE_H
#define RB_TREE_H

#include <vector>
#include <string>

enum Color {RED, BLACK};

struct node{
	std::string key;
	node* parent;
	node* right;
	node* left;
	Color color;

	node(std::string key, node* x):
		key(key),
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
		_nil = new node("",nullptr);
		_root = _nil;
	}
	long size();
	void add (std::string key);
	void leftRotate(node* x);
	void rightRotate(node* x);
	void findSuggestions(std::string& currentWord, std::vector<std::string>& suggestions);
	void getSuggestions(std::string& currentWord, std::vector<std::string>& suggestions, node* x, int& count);
	void insertFixup(node* z);
};
#endif