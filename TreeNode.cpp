#include <iostream>
#include <string>
#include <cstdlib>
#include "TreeNode.h"
#include "DRT.h"
using namespace std;

TreeNode::TreeNode(string key, string data, TreeNode* l, TreeNode* r, TreeNode* p, Tree* T) {

	k = key; d = data; left = l; right = r; parent = p; t = T;
}

TreeNode::TreeNode(TreeNode &other) {
	k = other.getk();
	d = other.getd();
	left = other.getleft();
	right = other.getright();
	parent = other.getParent();
	t = other.getTree();
}

TreeNode::~TreeNode() { //destructor

	delete left;
	delete right;
}

DRT* TreeNode::add(string key, string data, string n, string p) {
	if (key < k) {
		if (left == nullptr) {
			TreeNode* s = new TreeNode(key, data, nullptr, nullptr, this, t);
			left = s;
			return new DRT("", k, p);
		}
		else
			return left->add(key, data, k, p);
	}
	if (key > k) {
			if (right == nullptr) {
				TreeNode* s = new TreeNode(key, data, nullptr, nullptr, this, t);
				right = s;
				return new DRT("", n, k);
			}
			else
				return right->add(key, data, n, k);
	}
		string temp = d;
		d = data;
		return new DRT(d, n, p);

}

DRT* TreeNode::searchnode(string key, string n, string p) {

	if (k == key) {
		string next, prev;
		if (!right) next = n;
		else next = right->first()->getk();
		if (!left) prev = p;
		else prev = left->last()->getk();
		return new DRT(d, next, prev);
	}
	if (k < key) {
		if (right) return right->searchnode(key, n, k); //k is now the psf
		return new DRT("", n, k);
	}
	if (left) return left->searchnode(key, k, p);
	 return new DRT("", k, p);

}
TreeNode* TreeNode::first() {//left all the down
	if (left == nullptr)
		return this;
	TreeNode* temp = left->first();
	return temp;
}

TreeNode* TreeNode::last() { //right all the way down
	if (right == nullptr)
		return this;
	TreeNode* temp = right->last();
	return temp;

}

Tree* TreeNode::getTree() { return t; }
TreeNode* TreeNode::getParent() { return parent; }
string TreeNode::getk() { return k; }
string TreeNode::getd() { return d; }
TreeNode* TreeNode::getright() { return right; }
TreeNode* TreeNode::getleft() { return left; }
string TreeNode::next() { return right->first()->getk(); }
string TreeNode::prev() { return left->last()->getk(); }

DRT* TreeNode::remove(string key, string n, string p) {
	if (k == key) {
		string next, prev;
		if (!right) next = n;
		else next = right->first()->getk();
		if (!left) prev = p;
		else prev = left->last()->getk();
		this->remove();
		return new DRT("", next, prev);
	}
	if (k < key) {
		if (right) return right->remove(key, n, k); //k is now the psf
		return new DRT("", n, k);
	}
	if (left) return left->remove(key, k, p);
	return new DRT("", k, p);
}

void TreeNode::remove() {
	if (left && right) {			// TWO CHILD CASE, FIND NEXT HIGHEST NODE AND COPY KEY
		string data = searchnode(next(), k, next())->getdata();
		k = right->first()->getk();
		d = right->first()->getd();
		right->first()->remove();
	}
	else if ((left && !right) || (right && !left)) {		
		if (parent) {				
			if (parent->getright() == this) {		
				if (left) {		
					parent->setright(left);
					left->setparent(parent);
				}
				else {				
					parent->setright(right);
					right->setparent(parent);
				}
			}						
			else {					
				if (left) {			
					parent->setleft(left);
					left->setparent(parent);
				}
				else {			
					parent->setleft(right);
					right->setparent(parent);
				}
			}						
		}							
		else {						
			if (left) {
				left->setparent(NULL);
				t->setroot(left);
			}
			else {
				right->setparent(NULL);
				t->setroot(right);
			}
		}							
		right = NULL;
		left = NULL;
		delete this;				
	}								

	else if (!left && !right) {		
		if (parent) {
			if (parent->getright() == this) parent->setright(NULL);
			else parent->setleft(NULL);
		}
		else (t->setroot(NULL));
		right = NULL;
		left = NULL;
		delete this;
	}
}



void TreeNode::setparent(TreeNode* p) { parent = p; }
void TreeNode::setleft(TreeNode* l) { left = l; }
void TreeNode::setright(TreeNode* r) { right = r; }

