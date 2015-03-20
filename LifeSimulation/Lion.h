/* Life Simulation Program
 * Author: Gregory E. Hatt Jr.
 * Date: November 20th, 2014
 * Email: ghattjr@gmail.com
 */

#ifndef LION_H
#define LION_H

#include "Organism.h"


// Class:Lion
// ==================================================================
// Represents an organism on the board. The rules
// which a lion follows are:
// 	1. A lion can move in cross directions (+)
//	2. A lion can eat in all directions (+)
//	3. An lion breeds once its breed counter hits max.
//	4. If no breed location exists then counter is maintained.
//	5. If no eat move has occured in a set amount of time than the lion starves..
// ==================================================================
class Lion : public Organism
{
public:
  
    Lion(World* w, int row, int col);
    ~Lion();

private:

     int daysSinceEating;	// used to track if the organism starves (is removed from grid)		
     void spawn();			// create a new organism within the grid
     void move();			// move organism within the grid
     void starve();			// remove organism from grid if starve counter == n
     int getType();			// return the type 
     
     void noEatMove();		// move without eating (in a cross + pattern).
     void eatMove(std::vector<Directions> eatMoves);	/// move and remove an ant from the board
     
     std::vector< Directions> getBreedMoves();		// returns all available breed positions
     std::vector< Directions> getEatMoves();		// returns a list of locations for all surrounding ants  
};

#endif // LION_H
