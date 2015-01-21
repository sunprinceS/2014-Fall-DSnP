/****************************************************************************
  FileName     [ dlist.h ]
  PackageName  [ util ]
  Synopsis     [ Define doubly linked list package ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2005-2014 LaDs(III), GIEE, NTU, Taiwan ]
****************************************************************************/

#ifndef DLIST_H
#define DLIST_H

#include <cassert>

template <class T> class DList;

// DListNode is supposed to be a private class. User don't need to see it.
// Only DList and DList::iterator can access it.
//
// DO NOT add any public data member or function to this class!!
//
template <class T>
class DListNode
{
   friend class DList<T>;
   friend class DList<T>::iterator;

   DListNode(const T& d, DListNode<T>* p = 0, DListNode<T>* n = 0):
      _data(d), _prev(p), _next(n) {}

   T              _data;
   DListNode<T>*  _prev;
   DListNode<T>*  _next;
};


template <class T>
class DList
{
public:
   DList() {
      _head = new DListNode<T>(T());
      _head->_prev = _head->_next = _head; // _head is a dummy node
   }
   ~DList() { clear(); delete _head; }

   // DO NOT add any more data member or function for class iterator
   class iterator
   {
      friend class DList;

   public:
      iterator(DListNode<T>* n= 0): _node(n) {}
      iterator(const iterator& i) : _node(i._node) {}
      ~iterator() {} // Should NOT delete _node

      // TODO: implement these overloaded operators
      const T& operator * () const { return _node->_data; }
      T& operator * () { return _node->_data; }
      iterator& operator ++ () {_node = _node->_next; return *(this); }
      iterator operator ++ (int) {
		  iterator tmp = iterator(*this);
		  _node = _node->_next;
		  return tmp; 
	  }
      iterator& operator -- () {_node = _node->_prev; return *(this); }
      iterator operator -- (int) {
		  iterator tmp = iterator(*this);
		  _node = _node->_prev;
		  return tmp; 
	  }

      iterator& operator = (const iterator& i) { _node=i._node;return *this;}
      bool operator != (const iterator& i) const{return (_node != i._node);}
      bool operator == (const iterator& i) const {return (_node == i._node);}

   private:
      DListNode<T>* _node;
   };

   // TODO: implement these functions
   iterator begin() const { return iterator(_head->_next);}
   iterator end() const { return iterator(_head); }
   bool empty() const { return (begin() == end()); }
   size_t size() const 
   {
	   size_t ctr = 0;
	   for(iterator it= begin();it!=end();++it){++ctr;}
	   return ctr;
   }

   void push_back(const T& x)
   {
	   DListNode<T>* tmp = new DListNode<T>(x,_head->_prev,_head);
	   _head->_prev->_next = tmp;
	   _head->_prev = tmp;
   }
   void pop_front() 
   {
	   if (!empty()) {
		   DListNode<T>* tmp = _head->_next;
		   _head->_next = tmp->_next;
		   tmp->_next->_prev = _head;
		   delete tmp;
	   }	
   }
   void pop_back()
   {
	   if (!empty()) {
		   DListNode<T>* tmp = _head->_prev;
		   _head->_prev = tmp->_prev;
		   tmp->_prev->_next = _head;
		   delete tmp;
	   }	
   }

   // return false if nothing to erase
   bool erase(iterator pos){
		if (!empty()) {
///???why no need to check pos!=end()///
		   DListNode<T>* tmp = pos._node;
		   pos._node->_prev->_next = tmp->_next;
		   pos._node->_next->_prev = tmp->_prev;
		   delete tmp;
		   return true;
		}
	   return false;
   }

   bool erase(const T& x) { 
	   iterator it = findElm(x);
	   if( it != NULL ){
	   	  return erase(it);
	   }
	   else //not found
		   return false;
   }

   void clear() {
	   iterator it = begin();
   		while(it != end())
		{
			DListNode<T>* tmp = it._node;
			++it;
			delete tmp;
		}
		_head -> _prev =  _head -> _next= _head;
   }  // delete all nodes except for the dummy node

   void sort() const {//use selection sort
		iterator curNodeIt = begin();
		iterator minNodeIt = curNodeIt;
		while(curNodeIt != end())
		{
			for(iterator it = curNodeIt;it !=end();++it)
			{
				if(it._node->_data < minNodeIt._node->_data)
					minNodeIt  = it;
			}
			nodeSwap(minNodeIt._node,curNodeIt._node);
			++curNodeIt;
			minNodeIt = curNodeIt;
		}
   }

private:
   DListNode<T>*  _head;  // = dummy node if list is empty

   // [OPTIONAL TODO] helper functions; called by public member functions
   iterator findElm(const T& x)const
   {
	   for(iterator it = begin();it !=end();++it)
	   {
		   if(it._node->_data == x)
				return it;
	   }
	   return NULL;
   }
   void nodeSwap(DListNode<T>* l,DListNode<T>* r)const
   {
	   T data = l -> _data;
	   l -> _data = r -> _data;
	   r -> _data = data;
   }
};
#endif // DLIST_H
