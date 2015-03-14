/* Life Simulation Program
 * Author: Gregory E. Hatt Jr.
 * Date: November 20th, 2014
 * Email: ghattjr@gmail.com
 */

#ifndef ANT_H
#define ANT_H

#include "Organism.h"

// Class: Ant
// ==================================================================
// Represents an organism on the board. The rules
// which an ant follows are:
// 	1. An ant can move in cross directions (+)
//	2. An ant can breed in cross directions (+)
//	3. An ant breeds once its breed counter hits max.
//	4. If no breed location is empty its breed counter is reset.
// ==================================================================
class Ant : public Organism
{
public:
    Ant(World * w, int row, int col);
    ~Ant();

private:
  
  int getType();				// get organism type
  void move();					// move organism in grid
  void spawn();					// create new organism in grid
};

#endif // ANT_H
