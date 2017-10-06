#include <stdio.h>
#include <math.h>
#include "GravitationalForce.h"
#include "DebugHelpers.h"

void GravitationalForce::addEnergyToTotal( const VectorXs& x, const VectorXs& v, const VectorXs& m, scalar& E )
{
  assert( x.size() == v.size() );
  assert( x.size() == m.size() );
  assert( x.size()%2 == 0 );
  assert( m_particles.first >= 0 );  assert( m_particles.first < x.size()/2 );
  assert( m_particles.second >= 0 ); assert( m_particles.second < x.size()/2 );

  // Add milestone 2 code here.

}

void GravitationalForce::addGradEToTotal( const VectorXs& x, const VectorXs& v, const VectorXs& m, VectorXs& gradE )
{
  assert( x.size() == v.size() );
  assert( x.size() == m.size() );
  assert( x.size() == gradE.size() );
  assert( x.size()%2 == 0 );
  assert( m_particles.first >= 0 );  assert( m_particles.first < x.size()/2 );
  assert( m_particles.second >= 0 ); assert( m_particles.second < x.size()/2 );

  // Add milestone 2 code here.

  #if DEBUG_MODE    
    printf("endpoint 1: %d\n", m_particles.first);  
    printf("endpoint 2: %d\n", m_particles.second); 
  #endif
    
  int indexX1 = m_particles.first * 2;
  int indexY1 = indexX1 + 1;
    
  int indexX2 = m_particles.second * 2;
  int indexY2 = indexX2 + 1;
    
  scalar x1 = x[indexX1];
  scalar y1 = x[indexY1];
                  
  scalar x2 = x[indexX2];
  scalar y2 = x[indexY2];  
    
  scalar m1 = m[m_particles.first * 2];
  scalar m2 = m[m_particles.second * 2];
    
  #if DEBUG_MODE    
    printf("x1,y2: %.4f,%.4f\n", x1,y1);  
    printf("x2,y2 2: %.4f,%.4f\n", x2,y2); 
  #endif    
    
  scalar vx = x2-x1;
  scalar vy = y2-y1;
    
  scalar lengthV = sqrt((vx * vx)+(vy * vy));
    
  #if DEBUG_MODE    
    printf("lengthV %.4f\n", lengthV);  
  #endif      
    
  scalar nx = vx / lengthV;
  scalar ny = vy / lengthV;      
    
  scalar gradientX = ((m_G * m1 * m2) / (lengthV * lengthV)) * nx;
  scalar gradientY = ((m_G * m1 * m2) / (lengthV * lengthV)) * ny;
    
  #if DEBUG_MODE  
    printf("gradient x,y %.4f,%.4f", gradientX, gradientY);
  #endif          
    
  gradE[indexX1] -= gradientX;
  gradE[indexY1] -= gradientY;
    
  gradE[indexX2] += gradientX;
  gradE[indexY2] += gradientY;      
            
}
