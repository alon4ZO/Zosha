#ifndef __ENGINE__
#define __ENGINE__
#include "Animate.h"


#define STEP_INTERVAL_MS (16)

class Engine
{
public:
	void init(BasicObjects * xi_BasicObjects, Display * display); //TODO: change names.
	void gameThread(BasicObjects * BasicObjects, Display * display);

};

#endif __ENGINE__

