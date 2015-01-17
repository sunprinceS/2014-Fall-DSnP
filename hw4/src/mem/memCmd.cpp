/****************************************************************************
  FileName     [ memCmd.cpp ]
  PackageName  [ mem ]
  Synopsis     [ Define memory test commands ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2007-2014 LaDs(III), GIEE, NTU, Taiwan ]
****************************************************************************/
#include <iostream>
#include <iomanip>
#include "memCmd.h"
#include "memTest.h"
#include "cmdParser.h"
#include "util.h"

using namespace std;

extern MemTest mtest;  // defined in memTest.cpp

bool
initMemCmd()
{
   if (!(cmdMgr->regCmd("MTReset", 3, new MTResetCmd) &&
         cmdMgr->regCmd("MTNew", 3, new MTNewCmd) &&
         cmdMgr->regCmd("MTDelete", 3, new MTDeleteCmd) &&
         cmdMgr->regCmd("MTPrint", 3, new MTPrintCmd)
      )) {
      cerr << "Registering \"mem\" commands fails... exiting" << endl;
      return false;
   }
   return true;
}


//----------------------------------------------------------------------
//    MTReset [(size_t blockSize)]
//----------------------------------------------------------------------
CmdExecStatus
MTResetCmd::exec(const string& option)
{
   // check option
   string token;
   if (!CmdExec::lexSingleOption(option, token))
      return CMD_EXEC_ERROR;
   if (token.size()) {
      int b;
      if (!myStr2Int(token, b) || b < int(sizeof(MemTestObj))) {
         cerr << "Illegal block size (" << token << ")!!" << endl;
         return CmdExec::errorOption(CMD_OPT_ILLEGAL, token);
      }
      #ifdef MEM_MGR_H
      mtest.reset(toSizeT(b));//promote the multiple of size_ts
      #else
      mtest.reset();
      #endif // MEM_MGR_H
   }
   else
      mtest.reset();
   return CMD_EXEC_DONE;
}

void
MTResetCmd::usage(ostream& os) const
{  
   os << "Usage: MTReset [(size_t blockSize)]" << endl;
}

void
MTResetCmd::help() const
{  
   cout << setw(15) << left << "MTReset: " 
        << "(memory test) reset memory manager" << endl;
}


//----------------------------------------------------------------------
//    MTNew <(size_t numObjects)> [-Array (size_t arraySize)]
//----------------------------------------------------------------------
CmdExecStatus
MTNewCmd::exec(const string& option)
{

   // TODO(ok)
   vector<string> options;
   int numObj = 0;
   int arraySize = 0;
   if (!CmdExec::lexOptions(option, options)){
	  return CMD_EXEC_ERROR;}
   if(options.size() == 0) {
	   return CmdExec::errorOption(CMD_OPT_MISSING,"");}

   if((myStrNCmp("-Array", options[0], 2) == 0)){ 
  		if(options.size() == 1){
			return CmdExec::errorOption(CMD_OPT_MISSING,options[0]);}
		else if(options.size() == 2){
			if((!(myStr2Int(options[1],arraySize)) || arraySize <= 0)){
				return	CmdExec::errorOption(CMD_OPT_ILLEGAL,options[0]);}
			else
				return CmdExec::errorOption(CMD_OPT_MISSING,options[1]);
		}
		else{ // size>=3
			if((!(myStr2Int(options[1],arraySize)) || arraySize <= 0)){
				return CmdExec::errorOption(CMD_OPT_ILLEGAL,options[1]);}
			else{
				if((!(myStr2Int(options[2],numObj)) || numObj <= 0)){
					return CmdExec::errorOption(CMD_OPT_ILLEGAL,options[2]);}
				else if(options.size() == 3){
					mtest.newArrs(numObj,arraySize);
				}
				else{
				   return CmdExec::errorOption(CMD_OPT_EXTRA,options[2]);}
			}
			
		}

   }
   else if((myStr2Int(options[0],numObj)) && numObj > 0){
	   if(options.size() == 1){ // mtn 8
			mtest.newObjs(numObj);
	   }

	   else if(options.size() == 2){
		   if((myStrNCmp("-Array", options[1], 2) == 0)){ 
			   return CmdExec::errorOption(CMD_OPT_MISSING,options[1]);}
		   else{
			   return CmdExec::errorOption(CMD_OPT_EXTRA,options[1]);}
	   }

	   else{ //size >=3
		   if((myStrNCmp("-Array", options[1], 2) == 0)){ 
			   if((!(myStr2Int(options[2],arraySize)) || arraySize <= 0)){
				   return CmdExec::errorOption(CMD_OPT_ILLEGAL,options[0]);}
			   else if (options.size() == 3){
				   mtest.newArrs(numObj,arraySize);
			   }
			   else {
				   return CmdExec::errorOption(CMD_OPT_EXTRA,options[2]);}
		   }
		   else{
			   return CmdExec::errorOption(CMD_OPT_EXTRA,options[1]);}
	   }
   }

   else {
	   return CmdExec::errorOption(CMD_OPT_ILLEGAL,options[0]);}

   return CMD_EXEC_DONE;
}

void
MTNewCmd::usage(ostream& os) const
{  
   os << "Usage: MTNew <(size_t numObjects)> [-Array (size_t arraySize)]\n";
}

void
MTNewCmd::help() const
{  
   cout << setw(15) << left << "MTNew: " 
        << "(memory test) new objects" << endl;
}


//----------------------------------------------------------------------
//    MTDelete <-Index (size_t objId) | -Random (size_t numRandId)> [-Array]
//----------------------------------------------------------------------
CmdExecStatus
MTDeleteCmd::exec(const string& option)
{
	int objId = -1;
	int ranId = -1;

	// TODO(ok)
	vector<string> options;
	if (!CmdExec::lexOptions(option, options))
		return CMD_EXEC_ERROR;

	if(options.size() == 0){
		return CmdExec::errorOption(CMD_OPT_MISSING,"");}

	if((myStrNCmp("-Array", options[0], 2) == 0)){ 
		if(options.size() == 1){
			return CmdExec::errorOption(CMD_OPT_MISSING,options[0]);}

		else if(options.size() == 2){

			if((myStrNCmp("-Index", options[1], 2) == 0) ||
			  (myStrNCmp("-Random", options[1], 2) == 0)){
				return CmdExec::errorOption(CMD_OPT_MISSING,options[1]);}

			else{
				return CmdExec::errorOption(CMD_OPT_ILLEGAL,options[1]);}
		}

		else{ // size>=3
			if(myStrNCmp("-Index", options[1], 2) == 0){
				if((!(myStr2Int(options[2],objId)) || objId < 0)){
					return CmdExec::errorOption(CMD_OPT_ILLEGAL,options[2]);}
				else if (options.size() == 3){
					///???Need to add size check
					if(size_t(objId) < mtest.getArrListSize())
						mtest.deleteArr(size_t(objId));
					else{
						cerr<<"Size of array list" <<"("<<mtest.getArrListSize()							<<") is <=" << objId << "!!" << endl;
						return CmdExec::errorOption(CMD_OPT_ILLEGAL,options[2]);
					}
				}
				else{
					return CmdExec::errorOption(CMD_OPT_EXTRA,options[2]);}
			}
			else if(myStrNCmp("-Random", options[1], 2) == 0){
				if((!(myStr2Int(options[2],ranId)) || ranId <= 0)){
					return CmdExec::errorOption(CMD_OPT_ILLEGAL,options[2]);
				}
				else if (options.size() == 3){
					///???Need to add size check
					if(mtest.getArrListSize() > 0)
					{
						for(size_t i=0;i<size_t(ranId);++i)
						{
							const int Id = rnGen(mtest.getArrListSize());
							mtest.deleteArr(Id);
						}
					}
					else{
						cerr << "Size of array is 0!!" << endl;
						return CmdExec::errorOption(CMD_OPT_ILLEGAL,options[1]);
					}
				}
				else{
					return CmdExec::errorOption(CMD_OPT_EXTRA,options[2]);
				}
			}	
			else{
				return CmdExec::errorOption(CMD_OPT_ILLEGAL,options[1]);}
		}
	}
	else if((myStrNCmp("-Index", options[0], 2) == 0)){ 
		if(options.size() == 1){
			return CmdExec::errorOption(CMD_OPT_MISSING,options[0]);
		}
		else if(options.size() == 2){
			if((!(myStr2Int(options[1],objId)) || objId < 0)){
				return CmdExec::errorOption(CMD_OPT_ILLEGAL,options[1]);
			}
			else{
				if(size_t(objId) < mtest.getObjListSize())
						mtest.deleteObj(size_t(objId));
				else{
					cerr<<"Size of array list" <<"("<<mtest.getObjListSize()							<<") is <=" << objId << "!!" << endl;
				}
			}
		}
		else{ // size >=3
			if((!(myStr2Int(options[1],objId)) || objId < 0)){
				return CmdExec::errorOption(CMD_OPT_ILLEGAL,options[1]);
			}
			else if((myStrNCmp("-Array", options[2], 2) == 0)){
				if(options.size() == 3){
					if(size_t(objId) < mtest.getArrListSize())
						mtest.deleteArr(size_t(objId));
					else{
						cerr<<"Size of array list" <<"("<<mtest.getArrListSize()							<<") is <=" << objId << "!!" << endl;
						return CmdExec::errorOption(CMD_OPT_ILLEGAL,options[1]);
					}
				}
				else
					return CmdExec::errorOption(CMD_OPT_EXTRA,options[2]);
			}
			else{ 
				return CmdExec::errorOption(CMD_OPT_ILLEGAL,options[2]);
			}
		}
	}
	else if((myStrNCmp("-Random", options[0], 2) == 0)){ 
		if(options.size() == 1){
			return CmdExec::errorOption(CMD_OPT_MISSING,options[0]);
		}
		else if(options.size() == 2){
			if((!(myStr2Int(options[1],ranId)) || ranId < 0)){
				return CmdExec::errorOption(CMD_OPT_ILLEGAL,options[1]);
			}
			else{ 
				if(mtest.getObjListSize() > 0)
				{
					for(size_t i=0;i<size_t(ranId);++i)
					{
						const int Id = rnGen(mtest.getObjListSize());
						mtest.deleteObj(Id);
					}
				}
				else{
					cerr << "Size of object is 0!!" << endl;
					return CmdExec::errorOption(CMD_OPT_ILLEGAL,options[0]);
				}
			}
		}
		else{ // size >=3
			if((!(myStr2Int(options[1],ranId)) || ranId < 0)){
				return CmdExec::errorOption(CMD_OPT_ILLEGAL,options[1]);
			}
			else if((myStrNCmp("-Array", options[2], 2) == 0)){
				if(options.size() == 3){
					if(mtest.getArrListSize() > 0)
					{
						for(size_t i=0;i<size_t(ranId);++i)
						{
							const int Id = rnGen(mtest.getArrListSize());
							mtest.deleteArr(Id);
						}
					}
					else{
						cerr << "Size of array is 0!!" << endl;
						return CmdExec::errorOption(CMD_OPT_ILLEGAL,options[0]);
					}
				}
				else
					return CmdExec::errorOption(CMD_OPT_EXTRA,options[2]);
			}
			else{ 
				return CmdExec::errorOption(CMD_OPT_ILLEGAL,options[2]);
			}
		}
	}
   else {
	   return CmdExec::errorOption(CMD_OPT_ILLEGAL,options[0]);
   }

   return CMD_EXEC_DONE;

}

void
MTDeleteCmd::usage(ostream& os) const
{  
   os << "Usage: MTDelete <-Index (size_t objId) | "
      << "-Random (size_t numRandId)> [-Array]" << endl;
}

void
MTDeleteCmd::help() const
{  
   cout << setw(15) << left << "MTDelete: " 
        << "(memory test) delete objects" << endl;
}


//----------------------------------------------------------------------
//    MTPrint
//----------------------------------------------------------------------
CmdExecStatus
MTPrintCmd::exec(const string& option)
{
   // check option
   if (option.size())
      return CmdExec::errorOption(CMD_OPT_EXTRA, option);
   mtest.print();

   return CMD_EXEC_DONE;
}

void
MTPrintCmd::usage(ostream& os) const
{  
   os << "Usage: MTPrint" << endl;
}

void
MTPrintCmd::help() const
{  
   cout << setw(15) << left << "MTPrint: " 
        << "(memory test) print memory manager info" << endl;
}
