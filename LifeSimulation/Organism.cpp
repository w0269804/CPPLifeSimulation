/* Life Simulation Program
 * Author: Gregory E. Hatt Jr.
 * Date: November 20th, 2014
 * Email: ghattjr@gmail.com
 */

#include "Organism.h"
#include "World.h"
#include  <iostream>

Organism::Organism(World* w, int r, int c) : world(w), row(r), col(c)
{
  breedCounter = 0;
  daysAlive = 0;
  moved = false;
}


Organism::~Organism()
{

}

// getMoves()
// ======================================
// Returns a vector of available free positions
// in a cross pattern surrounding the organism.
// ======================================
vector< Directions > Organism::getMoves()
{ 
    vector< Directions> moves;	

    if(row > 0) 
        if(world->getOrg(row - 1, col) == NULL) 
            moves.push_back(North);
        
    if(row < GRID_H - 1) 
        if(world->getOrg(row + 1, col) == NULL) 
            moves.push_back(South);
        
    if(col < GRID_W - 1) 
        if(world->getOrg(row, col + 1) == NULL) 
            moves.push_back(East);
        
    if(col > 0) 
        if(world->getOrg(row, col - 1) == NULL) 
            moves.push_back(West);

    return moves;
}

