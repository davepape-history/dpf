#ifndef _perfClass_h_
#define _perfClass_h_

#include <Performer/pf/pfGroup.h>

class perfClass : public pfGroup
	{
	public:
	 perfClass(void);
	private:
	/* Stuff needed for APP traversal of node */
	public:
	 virtual int app(pfTraverser*);
	 virtual int needsApp(void);
	/* Stuff required to make this a Performer class */
	public:
	 static void init(void);
	 static pfType* getClassType(void){ return classType_; };
	private:
	 static pfType* classType_;
	};

#endif
