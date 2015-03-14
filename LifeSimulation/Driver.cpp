/* Life Simulation Program
 * Author: Gregory E. Hatt Jr.
 * Date: November 20th, 2014
 * Email: ghattjr@gmail.com
 */

#include "Driver.h"


// Start()
// =================================================
// Initializes the world and runs the simulation. 
// The world's move() method simulates all moving, 
// breeding and starving of the organisms. 
// =================================================
void Driver::start()
{
	double numberOfExtinctionEvents = 0; 
	double numberOfSets = 0; // keep track of number of runs
	int currentDay = 1; 
	
	srand(time(NULL)); // random number generator
	
	bool finished = false;
	
	while(!finished) { // loop while user desires
	
		World *w = new World();
		
		currentDay = 1; 
		
		do  {
			showState(w, currentDay);
			Sleep(100); 
			w->move(); // simulate a a round on all organisms
			currentDay++;
			
		} while(currentDay < MAX_DAYS && w->getRemAnts() > 0 && w->getRemLions() > 0);
	
		// check for extinction events
		if(w->getRemAnts() == 0|| w->getRemLions() == 0) {
		  showState(w, currentDay);	
		  numberOfExtinctionEvents++;
		}
			
		numberOfSets++;
		
		showExtinctionRate(numberOfSets, numberOfExtinctionEvents);
		
		finished = !anotherSet(); // prompt for another run

		delete w; // remove old world
	}
}

// ShowExtinctionRate()
// =================================================
// Shows the percentage of runs which have resulted in 
// all ants or all lions dying before a pre-set number of
// days defined as a constant.
// =================================================
void Driver::showExtinctionRate(const double& numberOfSets, const double& numberOfExtincts)
{
	if(numberOfSets > 0 && numberOfExtincts > 0){
		float f = ((numberOfExtincts/numberOfSets) * 100);
		printf("EXTINCTION RATE: %%%.2f \n", f);
	}
}

// anotherSet()
// ==================================================
// Prompts the user for another round.
// ===================================================
bool Driver::anotherSet(){

	string response = "";

	do{
		cout << "Show a new universe for " << MAX_DAYS << " days?" << std::endl;
		cin >> response;

		if (cin.eof() == 1) { // fixes control z issue
			cin.clear();
		}
		
	} while (!isValidResponse(response));

	return(response == "Y" || response == "y");
};

// showState()
// =============================================
// Displays to standard output the state of the world;
// the number of ants/lions that remain and the current
// day.
// ==============================================
void Driver::showState(World * w, int curDay)
{
	system("cls");
	printWorld(w);
	std::cout << std::endl;
    cout << "\tDAY: " <<  curDay << std::endl;
    cout << "\t"<< w-> getRemAnts() << " ANTS" << std::endl;
    cout << "\t"<< w->getRemLions() << " LIONS" << std::endl;
}

// isValidResponse()
// ===================================================
// Ensures that the response is a valid yY/nN response.
// ===================================================
bool Driver::isValidResponse(string response){

	if (response.length() > 1){
		return false;
	}

	// ascii for yY and nN
	if (!(int(response[0]) == 121 || int(response[0]) == 89
		|| int(response[0]) == 78 || int(response[0]) == 110)){
		return false;
	}

	return true;
};

void Driver::printWorld(World * w)
{
	string world = w->toString();

	for (int i = 0; i < world.length(); i++)
	{
		setConsoleColour(world[i]);
		std::cout << world[i];
		setConsoleColour(' ');
	}
}

void Driver::setConsoleColour(const char c)
{

	HANDLE hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	switch (c)
	{
	case ANT_TOKEN:
		SetConsoleTextAttribute(hConsole, ANT_COLOUR);
		break;
	case LION_TOKEN:
		SetConsoleTextAttribute(hConsole, LION_COLOUR);
		break;
	default :
		SetConsoleTextAttribute(hConsole, NO_COLOUR);
		break;
	}
}