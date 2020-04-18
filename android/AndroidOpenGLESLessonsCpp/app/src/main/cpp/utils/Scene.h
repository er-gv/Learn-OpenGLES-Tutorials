//
// Created by nathan on 09/04/20.
//

#ifndef ANDROIDOPENGLESLESSONSCPP_SCEANE_H
#define ANDROIDOPENGLESLESSONSCPP_SCEANE_H

#include "../graphics/GLUtils.h"
#include <jni.h>

struct Bounderies{

    GLint64 front, back, left, right, top, bottom;
};

class Scene {

    //light sources
    //list of models
    //camera
    //gl surface interface
public:
    Scene();
    ~Scene();
    Bounderies bounderyBox;

};


#endif //ANDROIDOPENGLESLESSONSCPP_SCEANE_H
