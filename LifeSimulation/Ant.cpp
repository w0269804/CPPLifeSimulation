/* Life Simulation Program
 * Date: November 20th, 2014
*/

#include "Ant.h"
#include "World.h"

// Constructor
// =====================================================
// Sets the ants row and col and sets the world
// pointer.
// =====================================================
Ant::Ant(World* w, int row, int col): Organism(w, row, col){}

// Destructor
Ant::~Ant(){}

// getType()
// =====================================================
// Returns the type of the organism so that 
// the move, breed, etc routines can be called
// on separate organisms at seperate times. 
// =====================================================
int Ant::getType()
{
  return ANT_TYPE;
}

// move()
// =====================================================
// Moves the ant within the grid. The ant
// can move into any non-diagonal adjacent
// position (+). Uses the getMoves() function
// to get a list of possible moves and picks one
// at random.
// =====================================================
void Ant::move()
{
 
  this->moved = true;
  
  vector < Directions > moves = getMoves();
  
  if(moves.empty())				// exit if not moves available
    return;
   
  int moveRow = row;				// temp variables for move positions
  int moveCol = col;
  
  int randomDir = rand() % moves.size();	// get a random index of the vector
  Directions direction = moves[randomDir];	// use index to get a random direction
  
  if(direction == North)
     moveRow --;
   
  if(direction == East)
      moveCol++;
  
  if(direction == West)
      moveCol--;
  
  if(direction == South)
      moveRow++;
  
  world->setOrg(world->getOrg(row, col), moveRow, moveCol);	// create new pointer
  world->setOrg(NULL, row, col);				// remove old pointer
  
  row = moveRow;
  col = moveCol;

  
}

// spawn()
// =====================================================
// Creates a new ant in an adjacent grid position. Uses 
// the getMoves() method to retrieve a vector of all 
// possible  moves. Ants are able to spawn if their spawn 
// counter reaches the required days. If there is no room 
// to spawn then their breed counter gets reset to 0.
// =====================================================
void Ant::spawn()
{
  
  breedCounter++;
  
  if(breedCounter != ANT_BREED_DAYS)
    return;
  
  breedCounter = 0;	// ants do not hold onto breed counter
  
  vector < Directions > locations = getMoves();	// get all empty spots
  
  if(locations.empty()){ // return if there are no available locations
    return;
  }
  
  int breedRow = this->row;
  int breedCol = this->col;
  
  int breedIndex = rand() % locations.size();
  Directions breedDirection = locations[breedIndex];
  
  if(breedDirection == North)
    breedRow--;
  
  if(breedDirection == South)
    breedRow++;
  
  if(breedDirection == East)
    breedCol++;
  
  if(breedDirection == West)
    breedCol--;
  
  
  world->setOrg(new Ant(world, breedRow, breedCol), breedRow, breedCol);
  world->setRemAnts(world->getRemAnts() + 1);
}
