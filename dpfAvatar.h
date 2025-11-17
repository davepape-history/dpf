#ifndef _dpfAvatar_h_
#define _dpfAvatar_h_

#include <cave.h>
#include <Performer/pf/pfGroup.h>
#include <Performer/pr/pfList.h>

class dpfAvatar : public pfGroup
	{
	public:
	 dpfAvatar(CAVE_USER_ST *user,char *headFile="Head.iv",
		char *handFile="Hand.iv",char *bodyFile="Body.iv");
	 void setUser(CAVE_USER_ST *user);
	 virtual void update(void);
	/* Stuff required to make this a Performer class */
	 static void init(void);
	 static pfType* getClassType(void){ return classType_; };
	private:
	 static pfType* classType_;
	protected:
	 CAVE_USER_ST *user_;
	 pfList *dcsList_;
	 pfDCS *bodyDCS_;
	 pfNode *headObject_,*handObject_,*bodyObject_;
	};

#endif
