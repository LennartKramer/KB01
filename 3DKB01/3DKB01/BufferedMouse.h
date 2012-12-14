#ifndef _BufferedMouse_H
#define _BufferedMouse_H

#include "BufferedMouse.h"

struct BufferedMouse
{
	public:
	int positionX;
	int positionY;
	int z;
	bool button0;
	bool button1;
	bool button2;
	bool button3;
	bool button4;
	bool button5;
	bool button6;
	bool button7;
};

#endif