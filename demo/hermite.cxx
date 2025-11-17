#include <cave_ogl.h>
#include "dpfHermiteCurve.h"

dpfHermiteCurve curve;

void drawfn(void)
{
 float t;
 pfVec3 p0(0,0,-5),p1(0,10,-5),p2(10,0,0),p3(10,0,0);
 pfVec3 p;
 glClearColor(0.0,0.0,0.0,0.0);
 glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
 CAVEGetPosition(CAVE_WAND,p0.vec);
 CAVEGetVector(CAVE_WAND_FRONT,p2.vec);
 p2 *= 10.0f;
 if (CAVEptr->num_sensors > 2)
	{
	CAVEGetSensorPosition(CAVESENSOR(2),CAVE_TRACKER_FRAME,p1.vec);
	CAVEGetSensorVector(CAVESENSOR(2),CAVE_FRONT,p3.vec);
	p3 *= 10.0f;
	}	
 curve.setControlPoints(p0,p1,p2,p3);
 glColor3f(1,1,1);
 glBegin(GL_LINE_STRIP);
 for (t=0.0; t<1.0; t+=0.01)
	{
	p = curve.value(t);
	glVertex3fv(p.vec);
	}
 glEnd();
 glColor3f(1,1,0);
 glBegin(GL_LINES);
 for (t=0.0; t<1.0; t+=0.1)
	{
	pfVec3 tangent;
	p = curve.value(t);
	glVertex3fv(p.vec);
	tangent = curve.tangent(t);
	tangent.normalize();
	p += tangent;
	glVertex3fv(p.vec);
	}
 glEnd();
}

main(int argc,char **argv)
{
 CAVEConfigure(&argc,argv,NULL);
 CAVEInit();
 CAVEDisplay(drawfn,0);
 while (!CAVEgetbutton(CAVE_ESCKEY))
	{
	sginap(1);
	}
 CAVEExit();
 return 0;
}
