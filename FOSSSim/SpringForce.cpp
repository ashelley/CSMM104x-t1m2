#include <stdio.h>
#include <math.h>
#include "SpringForce.h"
#include "DebugHelpers.h"

void SpringForce::addEnergyToTotal( const VectorXs& x, const VectorXs& v, const VectorXs& m, scalar& E )
{
  assert( x.size() == v.size() );
  assert( x.size()%2 == 0 );
  assert( m_endpoints.first >= 0 );  assert( m_endpoints.first < x.size()/2 );
  assert( m_endpoints.second >= 0 ); assert( m_endpoints.second < x.size()/2 );   
    

  // Add milestone 2 code here.

  #if DEBUG_MODE    
    printf("hello world");  
  #endif    
    
  printf("hello world");      
}

void SpringForce::addGradEToTotal( const VectorXs& x, const VectorXs& v, const VectorXs& m, VectorXs& gradE )
{
  assert( x.size() == v.size() );
  assert( x.size() == gradE.size() );
  assert( x.size()%2 == 0 );
  assert( m_endpoints.first >= 0 );  assert( m_endpoints.first < x.size()/2 );
  assert( m_endpoints.second >= 0 ); assert( m_endpoints.second < x.size()/2 );
    
  // Add milestone 2 code here.
    
  #if DEBUG_MODE    
    printf("endpoint 1: %d\n", m_endpoints.first);  
    printf("endpoint 2: %d\n", m_endpoints.second); 
  #endif
    
  int indexX1 = m_endpoints.first * 2;
  int indexY1 = indexX1 + 1;
    
  int indexX2 = m_endpoints.second * 2;
  int indexY2 = indexX2 + 1;
    
  scalar x1 = x[indexX1];
  scalar y1 = x[indexY1];
                  
  scalar x2 = x[indexX2];
  scalar y2 = x[indexY2];  
    
  scalar velocityX1 = v[indexX1];
  scalar velocityY1 = v[indexY1];
    
  scalar velocityX2 = v[indexX2];
  scalar velocityY2 = v[indexY2];
    
    
  #if DEBUG_MODE    
    printf("x1,x2: %.4f,%.4f\n", x1,y1);  
    printf("y1,y2 2: %.4f,%.4f\n", x2,y2); 
  #endif    
    
  scalar vx = x2-x1;
  scalar vy = y2-y1;
    
  scalar lengthV = sqrt((vx * vx)+(vy * vy));
    
  #if DEBUG_MODE    
    printf("lengthV %.4f\n", lengthV);  
  #endif      
    
  scalar energy = 0.5 * m_k * ((lengthV - m_l0) * (lengthV - m_l0));
    
  #if DEBUG_MODE  
    printf("size of gradE, %ld", gradE.size());
    printf("energy %.4f\n", energy);  
  #endif          
    
  scalar nx = vx / lengthV;
  scalar ny = vy / lengthV;
    
  #if DEBUG_MODE  
    printf("nx,ny %.4f,%.4f\n", nx, ny);  
  #endif    
    
  scalar gradientX = m_k * (lengthV - m_l0) * nx;
  scalar gradientY = m_k * (lengthV - m_l0) * ny;   
    
  scalar BnX = m_b * nx;
  scalar BnY = m_b * ny;
  
  scalar velocityDeltaX = (velocityX1 - velocityX2);
  scalar velocityDeltaY = (velocityY1 - velocityY2);
    
  scalar dotted = (BnX * velocityDeltaX) + (BnY * velocityDeltaY);
            
  scalar dampingX = nx * dotted;  
  scalar dampingY = ny * dotted;
    
  #if DEBUG_MODE
    printf("B: %.4f\n", m_b);      
    printf("velocity1: %.4f,%.4f\n", velocityX1,velocityY1);
    printf("velocity2: %.4f,%.4f\n", velocityX2,velocityY2);
    printf("dampingX: %.4f\n", dampingX);
    printf("dampingY: %.4f\n", dampingY);
  #endif
  
  gradE[indexX1] -= (gradientX - dampingX);
  gradE[indexY1] -= (gradientY - dampingY);
    
  gradE[indexX2] += (gradientX - dampingX);
  gradE[indexY2] += (gradientY - dampingY);    
    
  #if DEBUG_MODE  
    printf("energy gradientX,Y: %.4f,%.4f\n", gradientX, gradientY);  
    printf("energy gradientX,Y: %.4f,%.4f\n", gradientX, gradientY);  
  #endif      

}
