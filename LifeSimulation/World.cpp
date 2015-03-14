/* Life Simulation Program
 * Author: Gregory E. Hatt Jr.
 * Date: November 20th, 2014
 * Email: ghattjr@gmail.com
 */

#include "World.h"
#include "Organism.h"
#include "Ant.h"
#include "Lion.h"

World::World()
{
  remAnts = NUM_ANTS;
  remLions = NUM_LIONS;
  
    
    for(int row = 0; row < GRID_H; row++) {
        for(int col = 0; col < GRID_W; col++) {
            grid[row][col] = NULL;
        }
    }
  
  placeAnts();
  placeLions();

}

World::~World()
{
    for(int row = 0; row < GRID_H; row++) {
        for(int col = 0; col < GRID_W; col++) {
            delete grid[row][col];
        }
    }
}

// placeAnts() 
// =====================================================
// Places all ants on board randomly.
// =====================================================
void World::placeAnts()
{
  // Place all ants on board

    int antsToPlace = NUM_ANTS;

    while(antsToPlace > 0) {

        int col = rand() % GRID_W;
        int row = rand() % GRID_H;

        if(getOrg(row, col) == NULL) {
            setOrg(new Ant(this, row, col), row, col);
            antsToPlace--;
        }
    }
}

// placeLions()
// =====================================================
// Places all lions on board randomly.
// TODO See if a different place routine
// affects the extinction rate
// =====================================================
void World::placeLions()
{
  
    int lionsToPlace = NUM_LIONS;

   while(lionsToPlace > 0) {

      int col = rand() % GRID_W;
      int row = rand() % GRID_H;
	
        if(getOrg(row, col) == NULL) {
            setOrg(new Lion(this, row, col), row, col);
            lionsToPlace--;
        }
    } 
 
}

// move()
// =====================================================
// The main logic of the program. Moves through the major
// steps of the program; primes all organisms for move, 
// move ants, lions -- spawns ants, lions and then checks
// for starve conditions on the lions.
// =====================================================
void World::move()
{
    setMovedToFalse();
 
    moveType(LION_TYPE);
    moveType(ANT_TYPE);
    spawnType(LION_TYPE);
    spawnType(ANT_TYPE);
}


// setMovedToFalse()
// =====================================================
// Sets the moved variable to false on the organism so
// that it is able to move. (A check is performed in the 
// move method to ensure that the organisms move variable 
// is switched to false.
// =====================================================
void World::setMovedToFalse()
{
    for(int row = 0; row < GRID_H; row++) {
        for(int col = 0; col <GRID_W; col++) {
            if(grid[row][col] != NULL) {
                grid[row][col]->moved = false;
                grid[row][col]->daysAlive++;
            }
        }
    }

}

// moveType()
// =====================================================
// Moves all organisms with a matching type. Type is 
// used so that the flow of the "step" can be controlled.
// A check is made to ensure that newly bred organisms 
// are not moved and that an organism isn't moved twice
// in one round of moving.
// =====================================================
void World::moveType(int orgType)
{
    for(int row = 0; row < GRID_H; row++) {
        for(int col = 0; col <GRID_W; col++) {

            if(getOrg(row, col) != NULL && getOrg(row, col)->getType() == orgType &&
               getOrg(row, col)->daysAlive > 0 && getOrg(row, col)->moved == false) {
                getOrg(row,col)->move();
            }
        }
    }

}

// spawnType()
// =====================================================
// Calls the spawn method on all organisms who have a 
// matching type. The type is defined as a constant with
// the world.h file. Days alive must be greater than 0
// and moved must be true to avoid calling spawn on an
// organism which was created from another's spawn.
// =====================================================
void World::spawnType(int orgType)
{ 
      for(int row = 0; row < GRID_H; row++) {
        for(int col = 0; col <GRID_W; col++) {
            if(getOrg(row, col) != NULL	 && getOrg(row, col)->daysAlive > 0 && getOrg(row, col)->moved == true && getOrg(row, col)->getType() == orgType) {
                getOrg(row,col)->spawn();
            }
        }
    }

}

// setOrg()
// =====================================================
// Sets the grid co-ordinate r, c to an organism.
// Used by the world to place organism and organisms
// to spawn new organisms.
// =====================================================
void World::setOrg(Organism* org, int r, int c)
{  
      grid[r][c] = org;
}

// getOrg()
// =====================================================
// Returns organism at specified co-ordinates.
// =====================================================
Organism* World::getOrg(int r, int c)
{
    return grid[r][c];
}

// removeOrganism()
// =====================================================
// Removes an organism from the specified co-ordinate.
// =====================================================
void World::removeOrganism(int r, int c)
{
  if(grid[r][c] != NULL){
      delete grid[r][c];
      grid[r][c] = NULL;
  }
}

// toString()
// =====================================================
// Returns a string representation of the world for
// printing. 
// TODO Maybe an overloaded outstream operator (<<).
// =====================================================
string World::toString()
{
    string worldString = "";
    
    for(int i =0 ; i <= GRID_W + 1; i++)
      worldString += '=';
      worldString += '\n';

    for(int row = 0; row < GRID_H; row++) {
      
    worldString += '|';
      
        for(int col = 0; col <GRID_W; col++) {

            if(grid[row][col] == NULL) {
                worldString += NO_TOKEN;
            } else if (grid[row][col]->getType() == ANT_TYPE) {
				worldString += ANT_TOKEN; // ANSI_OPEN + ANT_ANSI + ANT_TOKEN + ANSI_CLOSE;
            } else if (grid[row][col]->getType() == LION_TYPE){
				worldString += LION_TOKEN;// ANSI_OPEN + LION_ANSI + LION_TOKEN + ANSI_CLOSE;
	    }
        }
        
        worldString += '|';
        worldString+= "\n";
    }
    
      for(int i =0 ; i <= GRID_W + 1; i++)
      worldString += '=';
      worldString += '\n';

    return worldString;
}

