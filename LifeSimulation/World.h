/* Life Simulation Program
 * Author: Gregory E. Hatt Jr.
 * Date: November 20th, 2014
 * Email: ghattjr@gmail.com
 */

#ifndef WORLD_H
#define WORLD_H


#include <cstdlib>
#include <string>
#include <windows.h> // WinApi header

using std::string;

const int GRID_H = 20;			// grid height
const int GRID_W = 20;			// grid width

const int ANT_TYPE = 1;			// type identifier
const int LION_TYPE = 2;		// type identifier

const char ANT_TOKEN = 'X';		// tokens for printing
const char LION_TOKEN = 'O';	
const char NO_TOKEN = '-';

//const string ANSI_OPEN = "\033[1;";	// for printing with colour
//const string ANSI_CLOSE = "\033[0m";	
//const string LION_ANSI = "31m";		// specific colour for organisms 
//const string ANT_ANSI = "34m";




const int NUM_ANTS = 100;			// number of initial ants
const int NUM_LIONS = 4;		// number of initial lions

const int ANT_BREED_DAYS = 3;		// number of days for ant to breed;
const int LION_BREED_DAYS = 9;		// number of days for lion to breed;
const int LION_NO_EAT_DAYS = 3;		// days without eating before lion starves


class Organism; 			// forward declaration

// World
// ================================================================
// Class to hold organisms and to control life flow. Has an array
// of organisms. Calls move, spawn and starve on the organisms 
// contained within the grid. The full rules for each organism are
// defined within their specific headers.
// ================================================================

class World
{
public:
    World();				// constructor
    ~World();				// destructor
    void move();			// move all organisms
      
    void setOrg(Organism * org, int r, int c); 	// sets a grid location to organism
    Organism * getOrg(int r, int c);		// gets organism at specified location
    void removeOrganism(int r, int c);
    
    int getRemAnts() { return remAnts;}; // get/set remaining ants
    void setRemAnts(int remAnts) { this->remAnts = remAnts;};	
    
    int getRemLions() { return remLions;}; // get/set remaining lions
    void setRemLions(int remLions) { this->remLions = remLions;};
    
    string toString();
    
private:
  
  Organism * grid[GRID_H][GRID_W];	// array of organisms
  
  void setMovedToFalse();		// set moved to false for all organisms
  void moveType(int orgType);		// move only specific organisms
  void spawnType(int orgType);		// spawn only specific organisms
  
  void placeAnts();			// initialize grid with organisms
  void placeLions();		
  
  void World::setConsoleColour(bool lionType);
  int remAnts = 0;				// track remaining organisms
  int remLions = 0;
  
};

#endif // WORLD_H
