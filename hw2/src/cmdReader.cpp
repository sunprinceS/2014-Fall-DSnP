/****************************************************************************
  FileName     [ cmdReader.cpp ]
  PackageName  [ cmd ]
  Synopsis     [ Define command line reader member functions ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2007-2014 LaDs(III), GIEE, NTU, Taiwan ]
****************************************************************************/
#include <cassert>
#include <cstring>
#include "cmdParser.h"

using namespace std;

//----------------------------------------------------------------------
//    Extrenal funcitons
//----------------------------------------------------------------------
void mybeep();
char mygetc(istream&);
ParseChar checkChar(char, istream&);


//----------------------------------------------------------------------
//    Member Function for class Parser
//----------------------------------------------------------------------
void
CmdParser::readCmd()
{ 
    if (_dofile.is_open()) {
      readCmdInt(_dofile);
      _dofile.close();
   }
   else
      readCmdInt(cin);
}

void
CmdParser::readCmdInt(istream& istr)
{ 
   resetBufAndPrintPrompt();

   while (1) {
      char ch = mygetc(istr);
      ParseChar pch = checkChar(ch, istr);
      if (pch == INPUT_END_KEY) break;
      switch (pch) {
         case LINE_BEGIN_KEY :
         case HOME_KEY       : moveBufPtr(_readBuf); break;
         case LINE_END_KEY   :
         case END_KEY        : moveBufPtr(_readBufEnd); break;
         case BACK_SPACE_KEY : if(moveBufPtr(_readBufPtr-1)){deleteChar();}break;
         case DELETE_KEY     : deleteChar(); break;
         case NEWLINE_KEY    : addHistory();
                               cout << char(NEWLINE_KEY);
							  /*for debug*/
							  //for(int i=0;i<_history.size();++i)
							  // {cout << "History[" <<i << "] = " << _history[i] << endl;}
							  resetBufAndPrintPrompt(); break;
         case ARROW_UP_KEY   : moveToHistory(_historyIdx - 1); break;
         case ARROW_DOWN_KEY : moveToHistory(_historyIdx + 1); break;
         case ARROW_RIGHT_KEY: moveBufPtr(_readBufPtr+1); break;
         case ARROW_LEFT_KEY : moveBufPtr(_readBufPtr-1); break;
         case PG_UP_KEY      : moveToHistory(_historyIdx - PG_OFFSET); break;
         case PG_DOWN_KEY    : moveToHistory(_historyIdx + PG_OFFSET); break;
		 case TAB_KEY        : insertChar(char(32),TAB_POSITION-((_readBufPtr-_readBuf)%TAB_POSITION)); break;
         case INSERT_KEY     : // not yet supported; fall through to UNDEFINE
         case UNDEFINED_KEY:   mybeep(); break;
         default:  // printable character
            insertChar(char(pch)); break;
      }
      #ifdef TA_KB_SETTING
      taTestOnly();
      #endif
   }
}


// This function moves _readBufPtr to the "ptr" pointer
// It is used by left/right arrowkeys, home/end, etc.
//
// Suggested steps:
// 1. Make sure ptr is within [_readBuf, _readBufEnd].
//    If not, make a beep sound and return false. (DON'T MOVE)
// 2. Move the cursor to the left or right, depending on ptr
// 3. Update _readBufPtr accordingly. The content of the _readBuf[] will
//    not be changed
//
// [Note] This function can also be called by other member functions below
//        to move the _readBufPtr to proper position.
bool
CmdParser::moveBufPtr(char* const ptr)
{
	//// TODO...(ok) 
   if(ptr>=_readBuf && ptr<=_readBufEnd)//control range
   {
	   if(ptr < _readBufPtr) //to backspace
	   {
		   for (int i = 0; i < (_readBufPtr-ptr); ++i) {
				cout << "\b";
		   }
	   }
	   else //print the current char,to move to the next position
	   {
			for (int i = 0; i < (ptr-_readBufPtr) ; ++i) {
				cout << *(_readBufPtr+i);
			}
	   }
	   _readBufPtr = ptr;
	   //cout << _readBufPtr-_readBuf << endl;
	   return true;
   }
   else  //out of range
   {
	   mybeep();
	   return false;
   }

}


// [Notes]
// 1. Delete the char at _readBufPtr
// 2. mybeep() and return false if at _readBufEnd
// 3. Move the remaining string left for one character
// 4. The cursor should stay at the same position
// 5. Remember to update _readBufEnd accordingly.
// 6. Don't leave the tailing character.
// 7. Call "moveBufPtr(...)" if needed.
//
// For example,
//
// cmd> This is the command
//              ^                (^ is the cursor position)
//
// After calling deleteChar()---
//
// cmd> This is he command
//              ^
//
bool
CmdParser::deleteChar()
{
   // TODO...
   int remainSize =_readBufEnd-_readBufPtr;
   if(_readBufPtr == _readBufEnd){mybeep();return false;} 
   else if (_readBufPtr < _readBufEnd && _readBufPtr >=_readBuf)
   {
	   char* tmp = new char[remainSize];
		for(int i=0;i<remainSize;++i){
			tmp[i] = *(_readBufPtr+1+i);
			if(i==remainSize-1) break; //prevent ^@
			cout << tmp[i];

		}
		for(int i=0;i<remainSize;++i){
			*(_readBufPtr+i) = tmp[i];
		}
		cout << " ";
		for(int i=0;i<(remainSize);++i)
			cout << '\b';
		//release the memory & control the buffer range
		delete []tmp;
		--_readBufEnd;
		return true;
   }
   else {cout << "Some ERROR in cursor manage" << endl;return false;} 
}

// 1. Insert character 'ch' for "repeat" times at _readBufPtr
// 2. Move the remaining string right for "repeat" characters
// 3. The cursor should move right for "repeats" positions afterwards
// 4. Default value for "repeat" is 1. You should assert that (repeat >= 1).
//
// For example,
//
// cmd> This is the command
//              ^                (^ is the cursor position)
//
// After calling insertChar('k', 3) ---
//
// cmd> This is kkkthe command
//                 ^
//
void
CmdParser::insertChar(char ch, int repeat)
{
	//TODO (ok)
	int remainSize = _readBufEnd - _readBufPtr+1;

   	char* tmpSubStr = new char[remainSize];
	//cout << remainSize << endl;
	for(int i =0;i<remainSize;++i) //store remaining string
	{
		tmpSubStr[i] = *(_readBufPtr+i);
	}
	//cout << repeat;
	assert(repeat >= 1);
	for(int i=0;i<repeat;++i)//insert
	{
		*(_readBufPtr) = ch;
		cout << ch;
		++_readBufPtr;
		++_readBufEnd;
		//*(_readBufEnd) = 0;
		//cout << _readBufEnd - _readBufPtr; 
	}

	for(int i =0;i<remainSize;++i)
	{
		*(_readBufPtr+i) = tmpSubStr[i];
		if(i == remainSize-1) break; //to prevent ^@ (the NULL character output)
		cout << tmpSubStr[i];
	}
	
	for(int i=0;i<(remainSize-1);++i)
		cout << '\b';
	//release the momory	
	delete []tmpSubStr;

}

// 1. Delete the line that is currently shown on the screen
// 2. Reset _readBufPtr and _readBufEnd to _readBuf
// 3. Make sure *_readBufEnd = 0
//
// For example,
//
// cmd> This is the command
//              ^                (^ is the cursor position)
//
// After calling deleteLine() ---
//
// cmd>
//      ^
//
void
CmdParser::deleteLine()
{
   // TODO...
	for(int i=0;i<_readBufPtr - _readBuf;++i)//back to front
		cout << '\b';
    for(int i=0;i<(_readBufEnd - _readBuf);++i)//delete the words
		cout << " ";
    for(int i=0;i<(_readBufEnd - _readBuf);++i)//move cursor back to front
		cout << '\b';
	//reset
    _readBufPtr = _readBufEnd = _readBuf;
    *_readBufPtr = 0;
}


// This functions moves _historyIdx to index and display _history[index]
// on the screen.
//
// Need to consider:
// If moving up... (i.e. index < _historyIdx)
// 1. If already at top (i.e. _historyIdx == 0), beep and do nothing.
// 2. If at bottom, temporarily record _readBuf to history.
//    (Do not remove spaces, and set _tempCmdStored to "true")
// 3. If index < 0, let index = 0.
//
// If moving down... (i.e. index > _historyIdx)
// 1. If already at bottom, beep and do nothing
// 2. If index >= _history.size(), let index = _history.size() - 1.
//
// Assign _historyIdx to index at the end.
//
// [Note] index should not = _historyIdx
//
void
CmdParser::moveToHistory(int index)
{
	//cout << "MOVE OT HIS" << index ;
   //TODO...
   bool beepOrNot = false;
   if(_tempCmdStored)
   {
	   if(index>=0 && index <=_history.size()-1)
	   {
		   _historyIdx = index;
		   retrieveHistory();
		   if(index == _history.size()-1) //back to current input
		   {
			   _history.erase(_history.end()-1);//remind should add "-1"
			   _tempCmdStored = false;
		   }
	   }
	   else 
	   {
		   if(index < 0)
		   {
			   if(_historyIdx == 0) {beepOrNot = true;}
			   else
			   {
				   _historyIdx = 0;
				   retrieveHistory();
			   }
		   }
		   else
		   {
			   if(_historyIdx == _history.size()-1) {beepOrNot = true;}
			   else
			   {
				   _historyIdx = _history.size()-1;
				   retrieveHistory();
				   _history.erase(_history.end()-1);//remind should add "-1"
				   _tempCmdStored = false;
			   }
			   
		   }
	   }
   }
   else //without adding the tmp history
   {
		if(index<_history.size() && index >=0)//normal browse the history 
		{
			_history.push_back(_readBuf);//store current input
			_tempCmdStored = true;
			_historyIdx = index;//locate the position in history
			retrieveHistory();
		}
		else
		{
			if(index < 0)
			{
				_history.push_back(_readBuf);//store current input
				_tempCmdStored = true;
				_historyIdx = 0;
				retrieveHistory();
			}
			else
			{
				if(_historyIdx == _history.size()) {beepOrNot = true;}
			}
		}
   }
   if(beepOrNot) {mybeep();}
}


// This function adds the string in _readBuf to the _history.
// The size of _history may or may not change. Depending on whether 
// there is a temp history string.
//
// 1. Remove ' ' at the beginning and end of _readBuf
// 2. If not a null string, add string to _history.
//    Be sure you are adding to the right entry of _history.
// 3. If it is a null string, don't add anything to _history.
// 4. Make sure to clean up "temp recorded string" (added earlier by up/pgUp,
//    and reset _tempCmdStored to false
// 5. Reset _historyIdx to _history.size() // for future insertion
// 6. Reset _readBufPtr and _readBufEnd to _readBuf
// 7. Make sure *_readBufEnd = 0 ==> _readBuf becomes null string
//
void
CmdParser::addHistory()
{
	//cout << "ADDHISTORY";
	bool inputOrNot = false;
	if(*_readBuf != char(0))
	{
		for(int i=0;i<_readBufEnd - _readBuf;++i)
		{
			if(_readBuf[i]!=' ')
			{
				inputOrNot = true;
				break;
			}
		} 
	}
	if(inputOrNot)
    {
	   int startPos,endPos;
	   //eliminate nonsense space
	   for(int i=0;i<_readBufEnd - _readBuf;++i)
	   {
		   if (_readBuf[i]!=' ')
		   {
			   startPos = i;
			   break;
		   }
	   }
	   for(int i=(_readBufEnd-1) - _readBuf;i>=0;--i)
	   {
		   if(_readBuf[i]!=' ')
		   {
			   endPos = i;
			   break;
		   }
	   }
	   //After modify ->store correct buf 
	   char* _readBufCorrect = new char [READ_BUF_SIZE];
	   for(int i=startPos,j=0;i<=endPos+1;++i,++j)
	   {
		   if(i == endPos+1){
			   _readBufCorrect[j]=char(0);
			   break;
		   }
		   _readBufCorrect[j] = _readBuf[i];
	   }


		if(_tempCmdStored) // in previous history
		{
			_history.erase(_history.end()-1);//remind should add "-1"
			_tempCmdStored = false;
			_history.push_back(_readBufCorrect);
			
		}
		else //in current input
		{
			_history.push_back(_readBufCorrect);

		}
		delete [] _readBufCorrect;
   }
   else
   {
		if(_tempCmdStored) // in previous history
		{
			_history.erase(_history.end()-1);//remind should add "-1"
			_tempCmdStored = false;
		}
   }
		//reset
		_historyIdx = _history.size();
		_readBufPtr = _readBufEnd = _readBuf;
	
}


// 1. Replace current line with _history[_historyIdx] on the screen
// 2. Set _readBufPtr and _readBufEnd to end of line
//
// [Note] Do not change _history.size().
//
void
CmdParser::retrieveHistory()
{
   deleteLine();
   strcpy(_readBuf, _history[_historyIdx].c_str());
   cout << _readBuf;
   _readBufPtr = _readBufEnd = _readBuf + _history[_historyIdx].size();
}
