#include <stdio.h>
#include <math.h>
#include "SymplecticEuler.h"
#include "DebugHelpers.h"

bool SymplecticEuler::stepScene( TwoDScene& scene, scalar dt )
{
  /* Add milestone 2 code here.      */
    
    VectorXs& pos = scene.getX();
    VectorXs& velocity = scene.getV();
    VectorXs mass = scene.getM();    
    
    int numberOfDimensions = 2;
    int numberOfParticles = pos.rows() / numberOfDimensions;
        
#if SYM_DEBUG_MODE
    printf("Number of particles: %d\n", numberOfParticles);    
    printf("size: %d\n", pos.size());
    printf("pos:\n");    
    DEBUGPrintVector(pos);
    printf("velocity:\n");
    DEBUGPrintVector(velocity);
#endif    
    
    VectorXs gravity(numberOfDimensions * numberOfParticles);
    gravity.setZero();
    
    //gravity.resize(numberOfDimensions);    

#if SYM_DEBUG_MODE
    printf("Gravity initialized:\n");
    DEBUGPrintVector(gravity);            
#endif
    
    scene.accumulateGradU(gravity);
    
    for(int i = 0; i < numberOfParticles; i++) {
        if(!scene.isFixed(i)) {
            int ix = i * numberOfDimensions + 0;
            int iy = i * numberOfDimensions + 1;       
            
            scalar massX = mass[ix];        
            scalar massY = mass[iy];            

            velocity[ix] += (-gravity[ix] / massX) * dt;     
            velocity[iy] += (-gravity[iy] / massY) * dt;   
            
            pos[ix] += velocity[ix] * dt;
            pos[iy] += velocity[iy] * dt;            
        }
    }            
  
  return true;
}






