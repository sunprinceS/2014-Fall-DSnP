/****************************************************************************
  FileName     [ bst.h ]
  PackageName  [ util ]
  Synopsis     [ Define binary search tree package ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2005-2014 LaDs(III), GIEE, NTU, Taiwan ]
****************************************************************************/

#ifndef BST_H
#define BST_H

#include <cassert>

using namespace std;

template <class T> class BSTree;

// BSTreeNode is supposed to be a private class. User don't need to see it.
// Only BSTree and BSTree::iterator can access it.
//
// DO NOT add any public data member or function to this class!!
//
//#define STR_MAX "~"
//for differnet class , you must define defferent max value
template <class T>
class BSTreeNode
{
   // TODO: design your own class!!(ok)
   friend class BSTree<T>;
   friend class BSTree<T>::iterator;

   BSTreeNode(const T& d,BSTreeNode<T>* p,
		      BSTreeNode<T>* l=NULL,BSTreeNode<T>* r = NULL):
	   _data(d),_parent(p),_left(l),_right(r) {}

   T              _data;
   BSTreeNode<T>* _parent;
   BSTreeNode<T>* _left;
   BSTreeNode<T>* _right;

};


   // TODO: design your own class!!
template <class T>
class BSTree
{
public:
	#ifdef STR_MAX
	BSTree():_size(0){
		_root = new BSTreeNode<T>(T(STR_MAX),NULL);//a dummy node
	}
	#else
	BSTree():_size(0){
		_root = new BSTreeNode<T>(T(),NULL);//a dummy node
	}
	#endif
   ~BSTree(){clear();delete _root;}

   class iterator
   {
      friend class BSTree;

   public:
      iterator(BSTreeNode<T>* n= 0): _node(n) {}
      iterator(const iterator& i) : _node(i._node) {}
      ~iterator() {} // Should NOT delete _node

      // TODO: implement these overloaded operators
      const T& operator * () const { return _node->_data; }
      T& operator * () { return _node->_data; }
      iterator& operator ++ () {_node = successor(_node); return *(this); }
      iterator operator ++ (int) {
		  iterator tmp = iterator(*this);
		  _node = successor(_node);
		  return tmp; 
	  }
      iterator& operator -- () {_node = ancestor(_node); return *(this); }
      iterator operator -- (int) {
		  iterator tmp = iterator(*this);
		  _node = ancestor(_node);
		  return tmp; 
	  }

      iterator& operator = (const iterator& i) { _node=i._node;return *this;}
      bool operator != (const iterator& i) const{return (_node != i._node);}
      bool operator == (const iterator& i) const {return (_node == i._node);}

   private:
      BSTreeNode<T>* _node;
   // [OPTIONAL TODO] helper functions; called by public member functions
   bool rlChild(BSTreeNode<T>* curNode)const
   {
	   if(curNode->_parent->_left == curNode)
		   return 0; //left child
	   else //(curNode->_parent->_right == curNode)
		   return 1; //right child
   }
   BSTreeNode<T>* min(BSTreeNode<T>* curNode)const
   {
	   while(curNode->_left != NULL)
	   {
		   curNode = curNode->_left;
	   }
	   return curNode;
   }
   BSTreeNode<T>* max(BSTreeNode<T>* curNode)const
   {
	   while(curNode->_right != NULL)
	   {
		   curNode = curNode->_right;
	   }
	   return curNode;
   }
   BSTreeNode<T>* successor(BSTreeNode<T>* curNode)const
   {
	   if(curNode->_right != NULL){
	   		return min(curNode->_right);
	   }
	   else{
		  bool rl = rlChild(curNode);
		  if(rl == 0){//left child
		  		return curNode->_parent;
		  }
		  else{//right child
		  	BSTreeNode<T>* traceNode = curNode->_parent;
			  while(rlChild(curNode) == 1&&traceNode->_parent!=NULL)
			  {
				  curNode = traceNode;
				  traceNode = traceNode->_parent;
			  }
			  return traceNode;
		  }
	   }
   }
   BSTreeNode<T>* ancestor(BSTreeNode<T>* curNode)const
   {
		if(curNode->_left != NULL){
			return max(curNode->_left);
		}
		else{
		  bool rl = rlChild(curNode);
		  if(rl == 1){//right child
		  		return curNode->_parent;
		  }
		  else{//left child
		  	BSTreeNode<T>* traceNode = curNode->_parent;
			  while(rlChild(curNode) ==0&&traceNode->_parent!=NULL) //prevent 
			  {
				  curNode = traceNode;
				  traceNode = traceNode->_parent;
			  }
			  return traceNode;
		  }
		}
   }
   };

   // TODO: implement these functions
   iterator begin() const {return iterator(min(this->_root));}

   iterator end() const {return iterator(this->_root);}

   bool empty() const { return(_size == 0);}

   size_t size() const { return _size;}

   void pop_front()
   {
	   if (!empty()) {
		   erase(begin());
	   }	
   }
   void insert(const T& x){
	   if(!empty()){
		   insertNode(x,_root->_left);	
	   }
	   else{
	   		_root->_left = new BSTreeNode<T> (x,_root);
	   }
		++_size;
   }
   void pop_back()
   {
	   if (!empty()) {
		   erase(--end());
	   }	
   }

   // return false if nothing to erase
   bool erase(iterator pos){
		if (!empty()) {
			BSTreeNode<T>* curNode = pos._node;
			short nodeDegree = degree(curNode);
			bool rl = rlChild(curNode);
			if(nodeDegree == 0){//trivial case
				if(rl == 0){ //left
					curNode->_parent->_left = NULL;
				}
				else{ // right
					curNode->_parent->_right = NULL;
				}
				delete curNode;
				--_size;
				return true;
			}
			else if(nodeDegree == 1){
				if(rl == 0){ //left
					if(curNode->_left != NULL){ 
						curNode->_parent->_left = curNode->_left;
						curNode->_left->_parent = curNode->_parent; 
					}
					else{
						curNode->_parent->_left = curNode->_right;
						curNode->_right->_parent = curNode->_parent; 
					} 
				}
				else{ // right
					if(curNode->_left != NULL){ 
						curNode->_parent->_right = curNode->_left;
						curNode->_left->_parent = curNode->_parent; 
					}
					else{
						curNode->_parent->_right = curNode->_right;
						curNode->_right->_parent = curNode->_parent; 
					} 
				}
				delete curNode;
				--_size;
				return true;
			}
			else{//nodeDegree == 2
				BSTreeNode<T>* sucNode = pos.successor(curNode);
				nodeSwap(curNode,sucNode);
				return erase(iterator(sucNode));
			}
		}
	   return false;
   }

   bool erase(const T& x) { 
	   if(!empty()){
		   iterator it = findElm(x,this->_root->_left);
		   if( it != NULL ){
			  return erase(it);
		   }
		   else //not found
			   return false;
	   }
	   else
		   return false;
   }

   void clear() {
	   if(!empty()){
		   eraseSubtree(_root->_left);
	   }
	   _root->_left = _root->_right = NULL;
	   _size = 0;
   }  // delete all nodes except for the _root node

   void sort() const {}
   void print()const {}

private:
   BSTreeNode<T>*  _root;  //the data stored in it is STR_MAX
   size_t _size;
   BSTreeNode<T>* min(BSTreeNode<T>* curNode)const
   {
	   while(curNode->_left != NULL)
	   {
		   curNode = curNode->_left;
	   }
	   return curNode;
   }
   BSTreeNode<T>* max(BSTreeNode<T>* curNode)const
   {
	   while(curNode->_right != NULL)
	   {
		   curNode = curNode->_right;
	   }
	   return curNode;
   }
   void insertNode(const T& x,BSTreeNode<T>* curNode)
   {
	   if( curNode->_data < x || x == curNode->_data)//go to the right child
	   {
		   if(curNode->_right != NULL){
			   insertNode(x,curNode->_right);
		   }
		   else{
			   BSTreeNode<T>* newNode = new BSTreeNode<T>(x,curNode);
			   curNode->_right = newNode;
		   }
	   }
	   else
	   {
		   if (curNode->_left != NULL) {
			   insertNode(x,curNode->_left);
		   }
		   else {
			   BSTreeNode<T>* newNode = new BSTreeNode<T>(x,curNode);
			   curNode->_left = newNode;
		   }
	   }
   }
   iterator findElm(const T& x,BSTreeNode<T>* curNode) const
   {
		if(x == curNode->_data)
			return iterator(curNode);
		else if(x < curNode->_data){
			if(curNode->_left != NULL)
				return findElm(x,curNode->_left);
			else
				return NULL;
		}
		else{ //x > curNode->_data
   			if(curNode->_right !=NULL )
				return findElm(x,curNode->_right);
			else
				return NULL;
		}
   }
   void eraseSubtree(BSTreeNode<T>* curNode)
   {
	   if(curNode->_left != NULL){
	   		eraseSubtree(curNode->_left);
	   }

	   if (curNode->_right != NULL) {
	   		eraseSubtree(curNode->_right);
	   }	

	   delete curNode;
   }
   short degree(BSTreeNode<T>* curNode) const
   {
	   if(curNode->_right == NULL && curNode->_left == NULL)
		   return 0;
	   else if(curNode->_right != NULL && curNode->_left != NULL)
		   return 2;
	   else
		   return 1;
   }
   bool rlChild(BSTreeNode<T>* curNode)const
   {
	   if(curNode->_parent->_left == curNode)
		   return 0; //left child
	   else //(curNode->_parent->_right == curNode)
		   return 1; //right child
   }
   void nodeSwap(BSTreeNode<T>* l,BSTreeNode<T>* r)const
   {
	   T data = l -> _data;
	   l -> _data = r -> _data;
	   r -> _data = data;
   }
};

#endif // BST_H
