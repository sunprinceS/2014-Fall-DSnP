/****************************************************************************
  FileName     [ array.h ]
  PackageName  [ util ]
  Synopsis     [ Define dynamic array package ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2005-2014 LaDs(III), GIEE, NTU, Taiwan ]
****************************************************************************/

#ifndef ARRAY_H
#define ARRAY_H

#include <cassert>
#include <algorithm>

using namespace std;

// NO need to implement class ArrayNode
//
template <class T>
class Array
{
public:
   Array() : _data(0), _size(0), _capacity(0) {}
   ~Array() { delete []_data; }

   // DO NOT add any more data member or function for class iterator
   class iterator
   {
      friend class Array;

   public:
      iterator(T* n= 0): _node(n) {}
      iterator(const iterator& i): _node(i._node) {}
      ~iterator() {} // Should NOT delete _node

      // TODO: implement these overloaded operators
      const T& operator * () const { return *_node; }
      T& operator * () { return *_node; }
      iterator& operator ++ () { _node++;return *(this) ; }
      iterator operator ++ (int) {
		  iterator tmp  = iterator(*this);
		  _node++;
		  return tmp; 
	  }//dummy int
      iterator& operator -- () { _node--;return *(this); }
      iterator operator -- (int) {
		  iterator tmp = iterator(*this);
		  _node--;
		  return tmp; }//dummy int

      iterator operator + (int i) const {
		  iterator result = iterator(*this);
		  result._node +=i;
		  return result ; }
      iterator& operator += (int i) { _node+=i;return (*this); }

      iterator& operator = (const iterator& i) { _node = i._node;return (*this); }

      bool operator != (const iterator& i) const { return (_node != i._node); }
      bool operator == (const iterator& i) const { return (_node == i._node); }

   private:
      T*    _node;
   };

   // TODO: implement these functions
   iterator begin() const { return iterator(_data); }
   iterator end() const { return iterator(_data+_size); }
   bool empty() const { return (_size == 0); }
   size_t size() const { return _size; }

   T& operator [] (size_t i) { return _data[i]; }
   const T& operator [] (size_t i) const { return _data[i]; }

   void push_back(const T& x) 
   {
	   if(_size == _capacity) //need to expand
		   expand();
		
	   _data[_size] = x;
	   ++_size;
   }
   void pop_front() {
	   if(!empty()){
		   --_size;
		   for(size_t i=0;i<_size;++i){
			   _data[i] = _data_ori[i+1];
		   }
	   }
   }
   void pop_back() {
	   if(!empty()){
		   --_size;
	   }
	}

   bool erase(iterator pos) { 
	   if(!empty()){
		   --_size;
		   size_t subSize = end()._node - pos._node;
		   size_t curPos = _size - subSize;
		   for(size_t i=0;i<subSize;++i)
		   {
			   _data[i + curPos] = _data[i+curPos +1];
		   }
		   return true;
	   }
	   return false; }

   bool erase(const T& x) {//DON't --size again!!!!!
	   iterator it = findElm(x);
	   if(it != NULL)
		   return erase(it);
	   else
		   return false;
   }

   void clear() {_size=0; }

   // This is done. DO NOT change this one.
   void sort() const { if (!empty()) ::sort(_data, _data+_size); }

   // Nice to have, but not required in this homework...
   // void reserve(size_t n) { ... }
   // void resize(size_t n) { ... }

private:
   T*           _data;
   size_t       _size;       // number of valid elements
   size_t       _capacity;   // max number of elements

   // [OPTIONAL TODO] Helper functions; called by public member functions
   iterator findElm(const T& x) const
   {
	   for(size_t i=0;i<_size;++i)
	   {
		   if(x == _data[i])
			   return (begin() + i);
	   }
	   return NULL;
   }
   void expand()
   {
	   assert(_size == _capacity);
	   if(_capacity == 0)	{_capacity = 1;}//0 -> 1
	   else	{_capacity *= 2;}

	   T* _data_ori = _data;
	   _data = new T[_capacity];
	   for(size_t i=0;i<_size;++i)
	   {
			_data[i] = _data_ori[i];
	   }
	   if(_data_ori != NULL){
		   delete []_data_ori;
	   }
   }
};

#endif // ARRAY_H
