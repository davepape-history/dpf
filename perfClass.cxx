#include <Performer/pf/pfTraverser.h>
#include "perfClass.h"

/************************************************************************/
/* Performer type data
*/

pfType *perfClass::classType_ = NULL; 

void perfClass::init(void)
{
 if (classType_ == NULL)
	{
        pfGroup::init();				/* Initialize the parent class */
        classType_ =  new pfType(pfGroup::getClassType(), "perfClass");	/* Create the new pfType for this class, based on the parent class's type */
	}
}
/************************************************************************/



perfClass::perfClass(void)
{
 setType(classType_);  /* set the Performer type of this instance */
}


int perfClass::app(pfTraverser *trav)
{
 return pfGroup::app(trav);
}

int perfClass::needsApp(void)
{
 return TRUE;
}
