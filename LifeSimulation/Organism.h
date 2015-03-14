/* Life Simulation Program
 * Author: Gregory E. Hatt Jr.
 * Date: November 20th, 2014
 * Email: ghattjr@gmail.com
 */

#ifndef ORGANISM_H
#define ORGANISM_H

#include "Direction_Enum.h"
#include <vector> 
#include <stdlib.h>     /* srand, rand */

using std::vector;

class World;

class Organism
{
public:
    Organism();
    Organism(World * w, int row, int col);
    virtual ~Organism();
    int getDaysAlive(){ return daysAlive;}
    virtual int getType() = 0;				// get organism type
    friend class World;
    
protected:
  
  virtual vector<Directions> getMoves();		// get list of available moves

  virtual void move() = 0;				// move organism in grid
  virtual void spawn() = 0;				// create new organism in grid
  
  World * world;
  int row, col;						// position within grid
  int daysAlive;					// used to prevent calling spawn on new orgs
  int breedCounter;					// used to check if org can breed.
  bool moved;						// used to prevent moving org twice
    
};

#endif // ORGANISM_H
