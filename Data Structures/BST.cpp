#include<iostream>
using namespace std;

template <typename T>


class BSTNode{
    T el;
    BSTNode<T> *left,*right;
public :
        BSTNode(){
            left=0;
            right=0;
        }
        BSTNode(const T &e, BSTNode<T> *l, BSTNode<T> *r){
            el = e;
            left = l;
            right = r;
        }
};

template<class T>
void BST<T>::iterativePostorder() {
    Stack<BSTNode<T>*> travStack;
    BSTNode<T>* p = root, *q = root;
    while (p != 0) {
        for ( ; p->left != 0; p = p->left)
        travStack.push(p);
        while (p->right == 0 || p->right == q) {
            visit(p);
            q = p;
            if (travStack.empty())
            return;
            p = travStack.pop();
        }
        travStack.push(p);
        p = p->right;
    }
}
