#include "dpfStack.h"

/************************************************************************/
/* Performer type data
*/

pfType *dpfStack::classType_ = NULL; 

void dpfStack::init(void)
{
 if (classType_ == NULL)
	{
        pfList::init();				/* Initialize the parent class */
        classType_ =  new pfType(pfList::getClassType(), "dpfStack");	/* Create the new pfType for this class, based on the parent class's type */
	}
}
/************************************************************************/



dpfStack::dpfStack(void)
{
 setType(classType_);  /* set the Performer type of this instance */
}

dpfStack::dpfStack(int eltSize,int listLength) : pfList(eltSize,listLength)
{
 setType(classType_);  /* set the Performer type of this instance */
}


void dpfStack::push(void *v)
{
 add(v);
}


void * dpfStack::pop(void)
{
 int top = getNum() - 1;
 void *v;
 if (top < 0)
	return (void *) -1;
 v = get(top);
 removeIndex(top);
 return v;
}


void * dpfStack::top(void)
{
 int top = getNum() - 1;
 if (top < 0)
	return (void *) -1;
 return get(top);
}


int dpfStack::isEmpty(void)
{
 return (getNum() <= 0);
}
