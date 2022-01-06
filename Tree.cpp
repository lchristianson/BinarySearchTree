#include <iostream>
#include <string>
#include <cstdlib>
#include "Tree.h"
#include "DRT.h"
#include "TreeNode.h"
using namespace std;

Tree::Tree() { root = NULL; }

Tree::~Tree() { delete root; }

void Tree::setroot(TreeNode* r) { root = r; }

TreeNode* Tree::getroot() { return root; }

DRT* Tree::add(string key, string data) { //very similar to sample code

    if (!root) {
        root = new TreeNode(key, data, NULL, NULL, NULL, this);
        return new DRT("", "", "");
    }
    return root->add(key, data, "", "");
}

DRT* Tree::searchnode(string key) { //searches the tree for the given key
    
    if (key == "")
        return new DRT("", "", "");
    if (root->getd() == key) {
        if(root->getleft() && root->getright())
            return new DRT(root->getd(), root->getright()->getk(), root->getleft()->getk());
        if (root->getleft() && !root->getright())
            return new DRT(root->getd(), "", root->getleft()->getk());
        if (!root->getleft() && root->getright())
            return new DRT(root->getd(), root->getright()->getk(), "");
        return new DRT(root->getd(), "", "");
    }
    return root->searchnode(key, "", "");

        

}

string Tree::first() {
    if (!root)
        return "";
    TreeNode* temp(root);
    while (temp->getleft() != nullptr)
        temp = temp->getleft();
    return temp->getk();

}

string Tree::last() { //last key in the tree (right all the way down)
    if (!root)
        return "";
    TreeNode* temp(root);
    while (temp->getright() != nullptr)
        temp = temp->getright();
    return temp->getk();

}

DRT* Tree::remove(string key) { //removes an item from the list
    if (key == "")
        return new DRT("", first(), last());
    return root->remove(key, "", "");


}

 DRT* Tree::search(string key) { //Database search method
    if (!root) return new DRT("", "", "");
    if (key == "")
        return new DRT("", first(), last());
    return root->searchnode(key, "","");
    }
      //checks to see if we're searching on the empty string, if so builds a DRT with first() and last (), otherwise calls searchnode



DRT* Tree::modify(string key, string data) { //Database modify method

    if (key == "") return new DRT("", first(), last());
    if (data == "") return remove(key);
    return add(key, data);
}