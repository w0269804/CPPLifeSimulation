#ifndef _Driver_H
#define _Driver_H

#include <iostream> /* cout */
#include <time.h>   /* rand seed */
#include <cstdlib>  /* null */
#include <Windows.h>
#include <stdio.h> /* printf */

#include "World.h"
#include "Ant.h"
#include "Lion.h"

using std::cout;
using std::cin;
using std::string;

const int LION_COLOUR = 4;
const int ANT_COLOUR = 6;
const int NO_COLOUR = 7;

const int MAX_DAYS = 100;

class Driver {
	
public:
	
	void start();
	
private:	
	void showState(World *w, int curDay); 	// show the status
	bool anotherSet();			// prompt for another round
	bool isValidResponse(string response);	// check if response is yY or nN
	void showExtinctionRate(const double &numberOfSets, 
				const double &numberOfExtincts); // shows events/extinctions
	
	
	void setConsoleColour(const char c);
	void resetConsoleColour(); 
	void printWorld(World * w);
};


#endif