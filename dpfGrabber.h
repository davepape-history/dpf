#ifndef _dpfGrabber_h_
#define _dpfGrabber_h_

#include <cave_ogl.h>
#include <Performer/pf/pfDCS.h>

class dpfGrabber : public pfDCS
	{
	public:
	 dpfGrabber(CAVE_SENSOR_ST *sensor=CAVESENSOR(1));
	 void setSensor(CAVE_SENSOR_ST *sensor);
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
	 CAVE_SENSOR_ST *sensor_;
	 int grabbed_;
	 pfMatrix grabMat_;
	 void GetSensorMatrix(pfMatrix&);
	 void GetInverseSensorMatrix(pfMatrix&);
	};

#endif
