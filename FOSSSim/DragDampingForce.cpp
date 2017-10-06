#include <stdio.h>
#include "DragDampingForce.h"
#include "DebugHelpers.h"

void DragDampingForce::addGradEToTotal( const VectorXs& x, const VectorXs& v, const VectorXs& m, VectorXs& gradE )
{
  assert( x.size() == v.size() );
  assert( x.size() == m.size() );
  assert( x.size() == gradE.size() );
  assert( x.size()%2 == 0 );
    
  // Add milestone 2 code here.
      
  int numPositions = x.size()/2;
    
  #if DAMPING_DEBUG_MODE 
    printf("numPositions,size : %d,%ld\n", numPositions, x.size());  
  #endif    
    
  for(int i = 0; i < numPositions; i++) {
      int indexX = i * 2;
      int indexY = indexX + 1;
      
      scalar forceX = -(v[indexX] * m_b);
      scalar forceY = -(v[indexY] * m_b);
      
      gradE[indexX] -= forceX;
      gradE[indexY] -= forceY;
      
  }

}
