#ifndef _dpfStack_h_
#define _dpfStack_h_

#include <Performer/pr/pfList.h>

class dpfStack : public pfList
	{
	public:
	 dpfStack(void);
	 dpfStack(int eltSize,int listLength);
	 void push(void *);
	 void * pop(void);
	 void * top(void);
	 int isEmpty(void);
	private:
	/* Stuff required to make this a Performer class */
	public:
	 static void init(void);
	 static pfType* getClassType(void){ return classType_; };
	private:
	 static pfType* classType_;
	};

#endif
