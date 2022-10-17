#ifndef __ENGINE__
#define __ENGINE__
#include "Animate.h"


#define STEP_INTERVAL_MS (5)

class Engine
{
public:
	void init(Animate * animate, Display * display); //TODO: change names.
	void gameThread(Animate * animate, Display * display);

};

#endif __ENGINE__

