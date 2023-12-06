#include <rb_tree.h>

long RBTree::size(){
	return RBTree::_size;
}

void RBTree::leftRotate(node* x){
	node* y = x->right;
	x->right = y->left;
	if(y->left != _nil){
		y->left->parent = x;
	}
	y->parent = x->parent;
	if(x->parent == _nil){
		_root = y;
	}
	else if(x == x->parent->left){
		x->parent->left = y;
	}
	else{
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

void RBTree::rightRotate(node* x){
	node* y = x->left;
	x->left = y->right;
	if(y->right != _nil){
		y->right->parent = x;
	}
	y->parent = x->parent;
	if(x->parent == _nil){
		_root = y;
	}
	else if(x == x->parent->right){
		x->parent->right = y;
	}
	else{
		x->parent->left = y;
	}
	y->right = x;
	x->parent = y;
}

void RBTree::insertFixup(node* z){
	while(z->parent->color == RED){
		if(z->parent == z->parent->parent->left){
			node* y = z->parent->parent->right;
			if(y->color == RED){
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			} 
			else{
				if(z == z->parent->right){
					z = z->parent;
					RBTree::leftRotate(z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				RBTree::rightRotate(z->parent->parent);
			}
		}
		else{
			node* y = z->parent->parent->left;
			if(y->color == RED){
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else{ 
				if(z == z->parent->left){
					z = z->parent;
					RBTree::rightRotate(z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				RBTree::leftRotate(z->parent->parent);
			}
		}
	}
	_root->color = BLACK;
}

void RBTree::add(std::string key, long idx){
	node* z = new node(key,idx,_nil);
	node* y = _nil;
	node* x = _root;
	while(x != _nil){
		y = x;
		if(z->key.compare(x->key) < 0){
			x = x->left;
		}
		else{
			x = x->right;
		}
	}
	z->parent = y;
	if(y == _nil){
		_root = z; 
	}
	else if(z->key.compare(y->key) < 0){
		y->left = z;
	}
	else{
		y->right = z;
	}
	z->left = _nil;
	z->right = _nil;
	z->color = RED;
	_size++;
	RBTree::insertFixup(z);
}

void RBTree::findInRange(std::vector<long> &res, std::string first, std::string last, node* p){
	if(p == _nil){
		return;
	}
	if(p->key.compare(first) >= 0 && p->key.compare(last) <= 0){
		findInRange(res, first, last, p->left);
		res.push_back(p->idx);
		findInRange(res, first, last, p->right);
	}
	if(p->key < first){
		findInRange(res, first, last, p->right);
	}
	if(p->key > last){
		findInRange(res, first, last, p->left);
	}
}

void RBTree::find(std::vector<long> &res, std::string first, std::string last){       
	node* current = _root;
	findInRange(res, first, last, current);
	res.resize(res.size());
}