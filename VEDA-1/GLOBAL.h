#pragma once

#include "UserData.h"
#include "eyeAnimation.h"

#define LOADING(ui) EyeAnimation* eyeAnimation = new EyeAnimation(##ui);
#define CLOSE_LOADING delete eyeAnimation;

extern bool USER_ENTERED ;
extern UserData* MAIN_USER_POINTER;
extern int CURRENT_EXP;
extern QString SERVER;
