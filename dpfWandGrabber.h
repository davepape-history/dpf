#ifndef _dpfGrabber_h_
#define _dpfGrabber_h_

#include <Performer/pf/pfDCS.h>

class dpfGrabber : public pfDCS
	{
	public:
	 dpfGrabber();
	 virtual void grab(void);
	 virtual void release(void);
	 virtual int isGrabbed(void);
	 virtual void update(void);
	/* Stuff required to make this a Performer class */
	 static void init(void);
	 static pfType* getClassType(void){ return classType_; };
	private:
	 static pfType* classType_;
	protected:
	 int grabbed_;
	 pfMatrix grabMat_;
	 void GetWandMatrix(pfMatrix&);
	 void GetInverseWandMatrix(pfMatrix&);
	};

#endif
