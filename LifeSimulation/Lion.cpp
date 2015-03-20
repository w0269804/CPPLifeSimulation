
/* Life Simulation Program
* Author: Gregory E. Hatt Jr.
* Date: November 20th, 2014
* Email: ghattjr@gmail.com
*/

#include "Lion.h"
#include "World.h"

Lion::~Lion()
{

}

Lion::Lion(World* w, int row, int col): Organism(w, row, col)
{

}

// getType()
// =====================================================
// Returns the type of the organism so that
// the move, breed, etc routines can be called
// on separate organisms at seperate times.
// =====================================================
int Lion::getType()
{
    return LION_TYPE;
}


// spawn()
//=========================================
// If a spot is available and the lion is able
// to breed then a new lion is created in an 
// adjacent cell. Otherwhise the breed counter
// is simply increased.
//=========================================
void Lion::spawn()
{

    breedCounter++;

    if(breedCounter >= LION_BREED_DAYS && !getBreedMoves().empty()) { 			// check if gestation is complete

        vector <Directions> breedMoves = getBreedMoves(); // gets all available breed locations

        breedCounter = 0;

        int breedRow = row;
        int breedCol = col;

        int breedIndex = rand() % breedMoves.size();
        Directions breedDirection = breedMoves[breedIndex];

        if(breedDirection == North || breedDirection == NorthEast || breedDirection == NorthWest)
            breedRow--;

        if(breedDirection == South || breedDirection == SouthEast || breedDirection == SouthWest)
            breedRow++;

        if(breedDirection == East || breedDirection == SouthEast || breedDirection == NorthEast)
            breedCol++;

        if(breedDirection == West || breedDirection == SouthWest || breedDirection == NorthWest)
            breedCol--;
	
	
        world->setOrg(new Lion(world, breedRow, breedCol), breedRow, breedCol);
        world->setRemLions(world->getRemLions() + 1);
	
    }
    
    
      // Check if the lion has not eaten in a number of days.
    if(daysSinceEating >= LION_NO_EAT_DAYS) {
        starve();
		return;
    }

}

// move()
//=========================================
// Will either move the lion to a cell containing
// an ant to eat or will move to an empty cell.
//=========================================
void Lion::move()
{
    moved = true;

    vector <Directions> eatMoves = getEatMoves();

    if(eatMoves.empty()) {
        noEatMove();
    } else {
        eatMove(eatMoves);
    }
     
}

// starve()
//=========================================
// Remove the lion from the grid and decrement
// the organism count of the world.
//=========================================
void Lion::starve()
{
	world->setRemLions(world->getRemLions() - 1);
    world->removeOrganism(row, col);

}

// eatMove()
//=========================================
// Moves the lion to an adjacent cell containing
// an ant to eat. Different from a non-eat move
// in that the lion can east in all directions
//=========================================
void Lion::eatMove(vector< Directions > eatMoves)
{

    daysSinceEating = 0;
    
    int eatRow = row;
    int eatCol = col;

    int eatIndex = rand() % eatMoves.size();
    Directions eatDirection = eatMoves[eatIndex];

    if(eatDirection == North || eatDirection == NorthEast || eatDirection == NorthWest)
        eatRow--;

    if(eatDirection == South || eatDirection == SouthEast || eatDirection == SouthWest)
        eatRow++;

    if(eatDirection == East || eatDirection == SouthEast || eatDirection == NorthEast)
        eatCol++;

    if(eatDirection == West || eatDirection == SouthWest || eatDirection == NorthWest)
        eatCol--;

    
    world->removeOrganism(eatRow, eatCol);
    world->setRemAnts(world->getRemAnts() - 1);
    
    world->setOrg(world->getOrg(row, col), eatRow, eatCol);
    world->setOrg(NULL, row, col);

    row = eatRow;
    col = eatCol;
}



// noEatMove()
//=========================================
// The lion's move behaviour if not ants are
// found to eat in all the adjacent cells.
//=========================================
void Lion::noEatMove()
{

    daysSinceEating++;

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

// getBreedMoves()
//=========================================
// Returns a list of all possible positions
// into which a Lion can breed.
//=========================================
vector< Directions > Lion::getBreedMoves()
{
    vector <Directions> breedMoves = getMoves();	// get non diagonal free spaces

    if(row > 0 && col > 0) {
        if(world->getOrg(row -1, col -1) == NULL) {
            breedMoves.push_back(NorthWest);
        }
    }

    if(row > 0 && col < (GRID_W - 1)) {
        if(world->getOrg(row - 1, col + 1) == NULL) {
            breedMoves.push_back(NorthEast);
        }
    }

    if(row < (GRID_H - 1) && col > 0) {
        if(world->getOrg(row + 1, col -1) == NULL) {
            breedMoves.push_back(SouthWest);
        }
    }

    if(row < (GRID_H - 1) && col < (GRID_W - 1)) {
        if(world->getOrg(row + 1, col + 1) == NULL) {
            breedMoves.push_back(SouthEast);
        }
    }

    return breedMoves;

}


// getEatMoves()
//=========================================
// Returns the position of all available ants
// Used by the lion to decide if it can eat and
// for generating a list of all available eat moves.
// TODO This method is long, consider ways to shorten.
//==========================================
vector< Directions > Lion::getEatMoves()
{

    vector< Directions> moves;		// holds available moves

    if(row > 0) {
        if(world->getOrg(row - 1, col) != NULL && world->getOrg(row - 1, col)->getType() == ANT_TYPE) {
            moves.push_back(North);
        }
    }

    if(row < GRID_H - 1) {
        if(world->getOrg(row + 1, col) != NULL && world->getOrg(row + 1, col)->getType() == ANT_TYPE) {
            moves.push_back(South);
        }
    }

    if(col < GRID_W - 1) {
        if(world->getOrg(row, col + 1) != NULL && world->getOrg(row, col + 1)->getType() == ANT_TYPE) {
            moves.push_back(East);
        }
    }

    if(col > 0) {
        if(world->getOrg(row, col - 1) != NULL && world->getOrg(row, col - 1)->getType() == ANT_TYPE) {
            moves.push_back(West);
        }
    }

    if(row > 0 && col > 0) {
        if(world->getOrg(row -1, col -1) != NULL && world->getOrg(row -1, col -1)->getType() == ANT_TYPE) {
            moves.push_back(NorthWest);
        }
    }

    if(row > 0 && col < (GRID_W - 1)) {
        if(world->getOrg(row - 1, col + 1) != NULL && (world->getOrg(row - 1, col + 1)->getType() == ANT_TYPE)) {
            moves.push_back(NorthEast);
        }
    }

    if(row < (GRID_H - 1) && col > 0) {
        if(world->getOrg(row + 1, col -1) != NULL && world->getOrg(row + 1, col -1)->getType() == ANT_TYPE) {
            moves.push_back(SouthWest);
        }
    }

    if(row < (GRID_H - 1) && col < (GRID_W - 1)) {
        if(world->getOrg(row + 1, col + 1) != NULL && world->getOrg(row + 1, col + 1)->getType() == ANT_TYPE) {
            moves.push_back(SouthEast);
        }
    }

    return moves;
}
