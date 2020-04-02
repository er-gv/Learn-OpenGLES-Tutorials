//
// Created by nathan on 30/03/20.
//

#ifndef ANDROIDOPENGLESLESSONSCPP_BRICKSSHADERNATIVERENDERER_H
#define ANDROIDOPENGLESLESSONSCPP_BRICKSSHADERNATIVERENDERER_H



#include <GLES2/gl2.h>
#include "../graphics/Matrix.h"

class BricksShaderNativeRenderer {

public:

    BricksShaderNativeRenderer();

    ~BricksShaderNativeRenderer();

    void create();

    void change(int width, int height);

    void draw();

    void drawTriangle(const GLfloat *verticesData);

private:

    Matrix *mViewMatrix;
    Matrix *mModelMatrix;
    Matrix *mProjectionMatrix;
    Matrix *mMVPMatrix;

    GLuint mProgram;

    GLuint mMVPMatrixHandle;
    GLuint mPositionHandle;
    GLuint mColorHandle;

    static const GLfloat* getModelData(int modelIndex) {

// This triangle is red, green, and blue.
        static constexpr GLfloat triangleVerticesData[] = {


// This triangle is yellow, cyan, and magenta.

                // X, Y, Z,
                // R, G, B, A
                -0.5f, -0.25f, 0.0f,
                1.0f, 1.0f, 0.0f, 1.0f,

                0.5f, -0.25f, 0.0f,
                0.0f, 1.0f, 1.0f, 1.0f,

                0.0f, 0.559016994f, 0.0f,
                1.0f, 0.0f, 1.0f, 1.0f,

// This triangle is red, green and blue.
                // X, Y, Z,
                // R, G, B, A
                -0.5f, -0.25f, 0.0f,
                1.0f, 0.0f, 0.0f, 1.0f,

                0.5f, -0.25f, 0.0f,
                0.0f, 0.0f, 1.0f, 1.0f,

                0.0f, 0.559016994f, 0.0f,
                0.0f, 1.0f, 0.0f, 1.0f,
// This triangle is white, gray, and black.
                // X, Y, Z,
                // R, G, B, A
                -0.5f, -0.25f, 0.0f,
                1.0f, 1.0f, 1.0f, 1.0f,

                0.5f, -0.25f, 0.0f,
                0.5f, 0.5f, 0.5f, 1.0f,

                0.0f, 0.559016994f, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f};


        return  &triangleVerticesData[modelIndex*21];
    }

};

#endif //ANDROIDOPENGLESLESSONSCPP_BRICKSSHADERNATIVERENDERER_H
