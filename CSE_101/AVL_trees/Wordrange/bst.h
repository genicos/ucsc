//Modified code from C. Seshadhri

#ifndef BST_H
#define BST_H

#include <string>
#include <iostream>

using namespace std;

class Node{
  public:
    string key;
    Node *left, *right, *parent;
    
    int size; // number of nodes in the subtree with this^ as root
   
    int height; // height of subtree with this^ as root 
    
    Node(){ //default constructor
      left = right = parent = NULL;
      size = height = 1;
    }

    Node(string k){
      key = k;
      left = right = parent = NULL;
      size = height = 1;
    }
};

class BST{
  private:
    //Node *root;
  public:
    Node *root;
    BST();
    
    void deleteBST();
      void deleteBST(Node* start);
    
    void insert(string s);
      bool AVLinsert(Node *r, Node *n);
        Node *left_rotation(Node *rotation_root);  // updates parents child pointer
        Node *right_rotation(Node *rotation_root); //|returns pointer to new root of rotated subtree
    
    int range(string a, string b); // number of nodes whose key are in the range [a,b]
    int range(Node *n, string a, string b); //recursive range function
      int leq(Node *n, string b); // number of nodes in tree rooted at n, whose key are less than or equal to b
      int geq(Node *n, string a); // ''                                                 greater than or equal to a

    string printPreOrder(); // Construct string with tree printed PreOrder
      string printPreOrder(Node* start); // Construct string with rooted subtree printed PreOrder
};
#endif
