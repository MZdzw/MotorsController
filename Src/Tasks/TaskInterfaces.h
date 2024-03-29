#ifndef __TASKINTERFACES_H_
#define __TASKINTERFACES_H_
#include "MovementElement.h"

// This file contains all variable which will be (are) shared
// between tasks located in this directory. The access to these
// variables should consider effects like race conditions
//
// The variables will be declared in main.cpp to ensure that they are
// ready immediately to use (at least before tasks creation)
//

// These variables should have common prefix (_sh - shared)

extern TaskHandle_t MovementElementTaskHanle_sh;

extern PositionMmX100 setPosition_sh;


#endif
