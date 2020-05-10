//
// Created by nathan on 09/04/20.
//

#ifndef ANDROIDOPENGLESLESSONSCPP_SCEANE_H
#define ANDROIDOPENGLESLESSONSCPP_SCEANE_H

#include "../graphics/GLUtils.h"
#include <jni.h>
#include <vector>
#include "graphics/Camera.h"
#include "Polyhedrons/Polyhedron.h"
#include "graphics/Model.h"


struct Bounderies{

    GLfloat front, back, left, right, top, bottom;
    Bounderies(GLfloat front, GLfloat back, GLfloat left, GLfloat right, GLfloat top, GLfloat bottom);
    Bounderies();
};

class Scene {

    std::vector<Model*> models;
    Camera camera;

    glm::mat4 MVmatrix;
    glm::mat4 MVPmatrix;

    //light sources
    //list of modelsmodels;    //camera
    //gl surface interface
public:
    Scene();
    ~Scene();


    void render();
    void setBounderies( Bounderies b);
    void addModel(Model* const m);
    void setupCamera();
    void setLights();
    void viewport(int width, int height);

    Bounderies bounderyBox;
};


#endif //ANDROIDOPENGLESLESSONSCPP_SCEANE_H
