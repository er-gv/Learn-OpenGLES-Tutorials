//
// Created by nathan on 02/04/20.
//

#ifndef ANDROIDOPENGLESLESSONSCPP_ABSTRACTSURFACERENDERERNATIVE_H
#define ANDROIDOPENGLESLESSONSCPP_ABSTRACTSURFACERENDERERNATIVE_H

#include <jni.h>
#include <GLES2/gl2.h>
#include "graphics/Matrix.h"

class AbstractSurfaceRendererNative {
public:
    AbstractSurfaceRendererNative();
    ~AbstractSurfaceRendererNative();

    virtual void create()=0;

    void change(int width, int height);
    virtual void draw()=0;

    protected:
        Matrix *mViewMatrix;
        Matrix *mModelMatrix;
        Matrix *mProjectionMatrix;
        Matrix *mMVPMatrix;
        GLuint mProgram;
        GLuint mMVPMatrixHandle;
};


#endif //ANDROIDOPENGLESLESSONSCPP_ABSTRACTSURFACERENDERERNATIVE_H
