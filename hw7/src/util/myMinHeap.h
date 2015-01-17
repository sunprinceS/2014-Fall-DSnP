/****************************************************************************
  FileName     [ myMinHeap.h ]
  PackageName  [ util ]
  Synopsis     [ Define MinHeap ADT ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2014 LaDs(III), GIEE, NTU, Taiwan ]
****************************************************************************/

#ifndef MY_MIN_HEAP_H
#define MY_MIN_HEAP_H

#include <algorithm>
#include <vector>
using namespace std;


template <class Data>
class MinHeap
{
public:
   MinHeap() : _data(0) {}
   MinHeap(size_t s) {
      _data.reserve(s);
      for (size_t i = 0; i < s; ++i) _data.push_back(Data());
      sort(_data.begin(), _data.end());
   }
   ~MinHeap() {}

   // For the following member functions,
   // We don't respond for the case vector "_data" is empty!
   const Data& operator [] (size_t i) const { return _data[i]; }   
   Data& operator [] (size_t i) { return _data[i]; }

   size_t size() const { return _data.size(); }

   // TODO
   const Data& min() const {
        return _data[0];
   }
   void insert(const Data& d) 
   {
        _data.push_back(d);
        floatUp(_data.size()-1);
   }
   void delMin()
   {
       if(!_data.empty())
       {
           if(nodeSwap(0,((_data.size())-1))){
               _data.pop_back();
               sink(0);
           }
       }


   }
   //void print()
   //{
       //for (size_t i = 0;i<_data.size();++i) {
           //cout << _data[i] << " \t ";
       //}     
       //cout << endl;
   //}
   void delData(size_t i)
   {
       if(i <= _data.size()-1){
           if(nodeSwap((_data.size()-1),i)){
               _data.pop_back();
               if(_data[i] < _data[(i-1)/2]){
                   floatUp(i);
               }
               else {
                   sink(i);
               }
           }
       }
            
   } // remove _data[i]
    
private:
   /***Helper function***/
   bool nodeSwap(size_t a,size_t b)
   {
       Data tmp = _data[a];
       _data[a] = _data[b];
       _data[b] = tmp;
       return true;
   }
   void sink(size_t node)
   {
       if (node*2+2 >= _data.size()) { //sink to deep
           if(node*2+1 == _data.size()-1 && _data[node*2+1] < _data[node]){
                nodeSwap(node,node*2+1);
           }
           return ;
       }

       //sink to the correct layer
       if(!(_data[node*2+1] < _data[node]) && !(_data[node*2+2] < _data[node]))
           return;

       else {
           if(_data[node*2+1] < _data[node*2+2]){ //sink to left
               nodeSwap(node,node*2+1);
               sink(node*2+1);
           }
           else {
               nodeSwap(node,node*2+2);
               sink(node*2+2);
           }
           return;
       }
   }
   void floatUp(size_t node)
   {
       if(node == 0)//to the top
           return ;
       else
       {
           if(_data[node] < _data[(node-1)/2]){
               nodeSwap(node,(node-1)/2);
               floatUp((node-1)/2);
           }
           else
               return ;
       }
   }
   // DO NOT add or change data members
   vector<Data>   _data;
};

#endif // MY_MIN_HEAP_H
