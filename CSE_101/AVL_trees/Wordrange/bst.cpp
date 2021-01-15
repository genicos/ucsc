#include "bst.h"
#include <string>


using namespace std;

BST :: BST(){
  root = NULL;
}

void BST :: insert(string s){
  
  Node *to_insert = new Node(s);

  if(root == NULL){
    root = to_insert;
  }else{
    AVLinsert(root, to_insert);  //Make call to avl insert
  }

}




int balance_factor(Node *n){ //right - left
  if(!n)
    return 0;
  
  int ans = 0;

  if(n->right){
    ans += n->right->height;
  }

  if(n->left){
    ans -= n->left->height;
  }

  return ans;
}

void update_size(Node *n){
  if(!n)
    return;

  int ans = 1;

  if(n->left){
    ans += n->left->size;
  }

  if(n->right){
    ans += n->right->size;
  }

  n->size = ans;
}

void update_height(Node *n){
  if(!n)
    return;

  int left_height = 0;
  int right_height = 0;

  if(n->left){
    left_height = n->left->height;
  }

  if(n->right){
    right_height = n->right->height;
  }

  n->height = max(left_height, right_height) + 1;
  
  update_height(n->parent);
}



bool BST :: AVLinsert(Node *start, Node *to_insert){
  if(start == NULL || to_insert == NULL){
    return false;
  }
    
  if(to_insert->key == start->key){
    delete(to_insert);                         //key is already in structure, no need for another.
    return false; 
  }
  
  start->size++;  //a node is being inserted, so size has increased by one

  if(to_insert->key < start->key){ //To insert is lesser than start
    
    if(!start->left){
      start->left = to_insert; //If no left child, make one. 
      to_insert->parent = start;
      
      update_height(start);

      return true;
    }

    if(!AVLinsert(start->left, to_insert)){
      start->size--;
      return false;
    }


    //We know that insert path is toward left
    if(balance_factor(start) < -1){ //Left heavy, re-balancing needed
      
      if(to_insert->key < start->left->key){// Left Left case
        right_rotation(start);
      }else{// Left Right case
        left_rotation(start->left);
	right_rotation(start);
      }

    }

  }else{ //to_insert is larger than start
    
    if(!start->right){
      start->right = to_insert; //If no right child, make one
      to_insert->parent = start;
      
      update_height(start);
      
      return true;
    }
    
    if(!AVLinsert(start->right, to_insert)){
      start->size--;
      return false;
    }
    
    //We know that insert path is toward right
    if(balance_factor(start) > 1){ //Right heavy, re-balancing needed
      
      if(to_insert->key < start->right->key){// Right Left case
        right_rotation(start->right);
	left_rotation(start);
      }else{// Right Right case
        left_rotation(start);
      }

    }
    
  }

  return true;
}




//AVL left rotation
//Input:
//  rot_root: root of subtree to be rotated
//Output:
//  new subtree root
Node *BST :: left_rotation(Node *rot_root){
  
  if(!rot_root || !rot_root->right) //We dont have enough members to rotate
    return rot_root;
  
  if(root == rot_root){ //rot_root is the true root, we must update the true root
    root = rot_root->right;
  }

  /*    |            |
        B            D
       / \          / \
      A   D   to   B   E
         / \      / \
        C   E    A   C
  */

  Node *right = rot_root->right; //temp node pointer
  rot_root->right = right->left; //Pass inheritence of C, that between rot_root and right
  if(rot_root->right){           //ensure C exists, to prevent seg faults
    rot_root->right->parent = rot_root;
  }
  
  right->left = rot_root;             //rotation
 
  right->parent = rot_root->parent;  //update parent
  rot_root->parent = right;          //
  
  rot_root = right; //subtree root has changed because of rotation
  

  //update child pointer of parent of original rot_root
  if(rot_root->parent){
    if(rot_root->parent->left == rot_root->left){ //rot_root->left is original rot_root
      rot_root->parent->left = rot_root;
    }else{
      rot_root->parent->right = rot_root;
    }
  }

  //Updating sizes and heights

  update_size(rot_root->left);
  update_height(rot_root->left);
  
  update_size(rot_root);
  update_height(rot_root);

  return rot_root;
}

//AVL right rotation
//Input:
//  rot_root: root of subtree to be rotated
//Output:
//  new subtree root
Node *BST :: right_rotation(Node *rot_root){
  
  if(!rot_root || !rot_root->left) //We dont have enough members to rotate
    return rot_root;
  
  if(root == rot_root){ //rot_root is the true root, we must update the true root
    root = rot_root->left;
  }


  /*      |          |
          D          B
         / \        / \
        B   E  to  A   D
       / \            / \
      A   C          C   E
  */

  Node *left = rot_root->left; //temp node pointer
  rot_root->left = left->right; //Pass inheritence of C, that between rot_root and left
  if(rot_root->left){           //ensure C exists, to prevent seg faults
    rot_root->left->parent = rot_root;
  }
  
  left->right = rot_root;             //rotation
  
  left->parent = rot_root->parent;  //update parent
  rot_root->parent = left;          //
 
  rot_root = left; //subtree root has changed because of rotation
 

   //update child pointer of parent of original rot_root
  if(rot_root->parent){
    if(rot_root->parent->left == rot_root->right){ //rot_root->right is original rot_root
      rot_root->parent->left = rot_root;
    }else{
      rot_root->parent->right = rot_root;
    }
  }
  
  //Updating sizes and heights

  update_size(rot_root->right);
  update_height(rot_root->right);

  update_size(rot_root);
  update_height(rot_root);

  return rot_root;
}





int BST :: range(string a, string b){
  return range(root, a, b);
}

int BST :: range(Node *n, string a, string b){
  if(!n)
    return 0; //empty tree


  if(n->key < a){
    return range(n->right, a, b);  //left subtree has none in range
  }
  if(b < n->key){
    return range(n->left, a, b);  //right subtree has none in range 
  }
  
  //At this point, we know that:
  //  n->key is in the range
  //  left subtree is all less than b
  //  right subtree is all larger than a

  return geq(n->left, a) + 1 + leq(n->right, b);
}

int BST :: geq(Node *n, string a){
  if(!n)
    return 0;

  int ans = 0; //for storing extra counts
  
  if(a < n->key){
    
    if(n->right){
      ans += n->right->size; // entire right subtree is greater
    }

    return geq(n->left, a) + 1 + ans;
  }
  //From here: none of left tree is greater
  if(n->key == a){
    
    if(n->right){
      ans += n->right->size; // entire right subtree is greater
    }

    return 1 + ans;
  }
  //n->key < a

  return geq(n->right, a); 
}

int BST :: leq(Node *n, string b){
  if(!n)
    return 0;

  int ans = 0; //for storing extra counts
  
  if(b < n->key){
    return leq(n->left, b); //none of right subtree is less
  }
  //From here: entire left subtree is less
  if(n->left){
    ans += n->left->size;
  }

  if(n->key == b){
    return ans + 1; //none of right subtree is less
  }

  //n->key < b

  return ans + 1 + leq(n->right, b);
}



//The following 2 functions were made by Seshadhri 
string BST :: printPreOrder()
{
    return printPreOrder(root);
}
string BST :: printPreOrder(Node* start)
{
    if(start == NULL) // base case
        return ""; // return empty string
    string leftpart = printPreOrder(start->left);
    string rightpart = printPreOrder(start->right);
    string output = start->key;
    if(leftpart.length() != 0) // left part is empty
        output = output + " " + leftpart; // append left part
    if(rightpart.length() != 0) // right part in empty
        output = output + " " + rightpart; // append right part
    return output;
}





void BST :: deleteBST(){ //Deletes entire BST
  deleteBST(root);
}

void BST :: deleteBST(Node *start){
  if(!start){
    return;
  }
  
  deleteBST(start->left);
  deleteBST(start->right);

  delete(start);
}
