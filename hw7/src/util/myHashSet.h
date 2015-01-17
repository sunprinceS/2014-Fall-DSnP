/****************************************************************************
  FileName     [ myHashSet.h ]
  PackageName  [ util ]
  Synopsis     [ Define HashSet ADT ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2014 LaDs(III), GIEE, NTU, Taiwan ]
****************************************************************************/

#ifndef MY_HASH_SET_H
#define MY_HASH_SET_H

#include <vector>
#include<cassert>

using namespace std;

//---------------------
// Define HashSet class
//---------------------
// To use HashSet ADT,
// the class "Data" should at least overload the "()" and "==" operators.
//
// "operator ()" is to generate the hash key (size_t)
// that will be % by _numBuckets to get the bucket number.
// ==> See "bucketNum()"
//
// "operator ()" is to check whether there has already been
// an equivalent "Data" object in the HashSet.
// Note that HashSet does not allow equivalent nodes to be inserted
//
template <class Data> class HashSet;

template <class Data>
class HashNode
 {
   // TODO: design your own class!!
   friend class HashSet<Data>;
   friend class HashSet<Data>::iterator;

   HashNode(const Data& d,
		      HashNode<Data>* prev=NULL,HashNode<Data>* next = NULL):
	   _data(d),_prev(prev),_next(next) {}
    
   Data            _data;
   HashNode<Data>* _prev;
   HashNode<Data>* _next;

};

template <class Data>
class HashSet
{
public:
   HashSet() : _numBuckets(0), _buckets(0),
    _dummyEnd(HashNode<Data>(Data("",0))) {}
   HashSet(size_t b) : _numBuckets(0), _buckets(0),
    _dummyEnd(HashNode<Data>(Data("",0))) { init(b); }
   ~HashSet() { reset(); }

   // TODO: implement the HashSet<Data>::iterator
   // o An iterator should be able to go through all the valid Data
   //   in the Hash
   // o Functions to be implemented:
   //   - constructor(s), destructor
   //   - operator '*': return the HashNode
   //   - ++/--iterator, iterator++/--
   //   - operators '=', '==', !="
   //
   class iterator
   {
      friend class HashSet<Data>;

   public:
      iterator(HashNode<Data>* n= 0): _node(n) {}
      iterator(const iterator& i) : _node(i._node) {}
      ~iterator() {} // Should NOT delete _node

      // TODO: implement these overloaded operators
      const Data& operator * () const { return _node->_data; }
      Data& operator * () { return _node->_data; }
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
      HashNode<Data>* _node;
   };

   void init(size_t b) {
      reset(); _numBuckets = b; _buckets = new vector<HashNode<Data>* >[b]; }
   void reset() {
      _dummyEnd._prev = NULL;
      if (_buckets) {
          for(size_t i=0;i<_numBuckets;++i)
          {
              for(size_t j=0;j<_buckets[i].size();++j){
                  delete _buckets[i][j];}
          }
          _numBuckets = 0;
          delete [] _buckets; _buckets = 0;
      }
   }
   size_t numBuckets() const { return _numBuckets; }

   vector<HashNode<Data>* >& operator [] (size_t i) { return _buckets[i]; }
   const vector<HashNode<Data>* >& operator [](size_t i) const { return _buckets[i]; }

   // TODO: implement these functions
   //
   // Point to the first valid data
   iterator begin() const
   {
       for (size_t i = 0;i<_numBuckets;++i) {
           if(!(_buckets[i].empty()))
               return _buckets[i].front();
       }
       return &_dummyEnd; 
   }
   // Pass the end
   iterator end() const {
       return &_dummyEnd; 
   }//the real end node 's next is NULL
   // return true if no valid data
   bool empty() const { return (begin() == end()); }
   // number of valid data
   size_t size() const
   {
	   size_t ctr = 0;
	   for(iterator it= begin();it!=end();++it){++ctr;}
	   return ctr;
   }
    
   // check if d is in the hash...
   // if yes, return true;
   // else return false;
   bool check(const Data& d) const { 
       size_t bkNum = bucketNum(d); 
        for (size_t i = 0;i<_buckets[bkNum].size();++i) {
            if(d == _buckets[bkNum][i]->_data)
                return true;
        }   
        return false;
   }

   // query if d is in the hash...
   // if yes, replace d with the data in the hash and return true;
   // else return false;
   bool query(Data& d) const { 
       size_t bkNum = bucketNum(d);
       for (size_t i = 0;i<_buckets[bkNum].size();++i) {
           if (d == _buckets[bkNum][i]->_data) {
               d = _buckets[bkNum][i]->_data;
               return true;
           }
       }
       return false;
   }

   // update the entry in hash that is equal to d
   // if found, update that entry with d and return true;
   // else insert d into hash as a new entry and return false;
   bool update(const Data& d) {
       size_t bkNum = bucketNum(d);
        for (size_t i = 0;i<_buckets[bkNum].size();++i) {
            if(d == _buckets[bkNum][i]->_data){
                _buckets[bkNum][i]->_data = d;
                return true;
            }
        }
        insert(d);
        return false;
   }

   // return true if inserted successfully (i.e. d is not in the hash)
   // return false is d is already in the hash ==> will not insert
   bool insert(const Data& d)
   {
        if(!check(d)) //not exist
        {
            size_t bkNum = bucketNum(d);
            HashNode<Data>* newNode = new HashNode<Data>(d);
            
            //set prev
            if(_buckets[bkNum].empty())
            {
                 HashNode<Data>* prev = findPrev(newNode);
                 newNode->_prev = prev;
                 if(prev!=NULL)
                    prev->_next = newNode;
            }
            else
            {
                 size_t size = _buckets[bkNum].size();
                 HashNode<Data>* prev = _buckets[bkNum][size-1];
                 newNode->_prev = prev;
                 assert(prev!=NULL);
                 prev->_next = newNode;
            }
            //set next
            HashNode<Data>* next = findNext(newNode);
            newNode->_next = next;
            next->_prev = newNode;

            _buckets[bkNum].push_back(newNode);
            return true;
        }
        else 
            return false;
   }

private:
   // Do not add any extra data member
   size_t            _numBuckets;
   vector<HashNode<Data>* >* _buckets;
   mutable HashNode<Data> _dummyEnd;
    /***Helper Function***/
   size_t bucketNum(const Data& d) const {
      return (d() % _numBuckets); }
    HashNode<Data>* findPrev(const HashNode<Data>* curNode)const
    {
        size_t curBk = bucketNum(curNode->_data);
        for (size_t i = 1;i<=curBk;++i) {
            if(!(_buckets[curBk-i].empty())){
                return (_buckets[curBk -i].back());
            }
        }
        return NULL;
    }
    HashNode<Data>* findNext(const HashNode<Data>* curNode)const
    {
        size_t curBk = bucketNum(curNode->_data);
        assert(curBk < _numBuckets);
        for (size_t i = curBk+1;i<_numBuckets;++i) {
            if(!(_buckets[i].empty())){
                return (_buckets[i].front());}
        }
        return &(_dummyEnd);
    }
};

#endif // MY_HASH_SET_H
