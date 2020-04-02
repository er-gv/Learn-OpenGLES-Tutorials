//
// Created by nathan on 30/03/20.
//

#ifndef ANDROIDOPENGLESLESSONSCPP_QUANTIZEDCOLORNATIVE_H
#define ANDROIDOPENGLESLESSONSCPP_QUANTIZEDCOLORNATIVE_H



#include <GLES2/gl2.h>
#include "../graphics/Matrix.h"
#include "AbstractSurfaceRendererNative.h"

class QuantizedColorNative: public AbstractSurfaceRendererNative {

public:

    QuantizedColorNative();

    ~QuantizedColorNative();

    virtual void create();

    void change(int width, int height);

    virtual void draw();

    void drawTriangle(const GLfloat *verticesData, const GLfloat quanta);

private:


    GLuint mPositionHandle;
    GLuint mColorHandle;
    GLfloat mQuantaHandle;

    static GLfloat *getTriangleData(uint8_t triangleIndex) {
        static constexpr GLfloat triangleVerticesData[][18] = {
                // X, Y, Z,
                // R, G, B
                {//t1
                        -0.5f, -0.25f, 0.0f,
                        1.0f, 1.0f, 1.0f,

                        0.5f, -0.25f, 0.0f,
                        0.5f, 0.5f, 0.5f,

                        0.0f, 0.559016994f, 0.0f,
                        0.0f, 0.0f, 0.0f},

                {//t2
                        // X, Y, Z,
                        // R, G, B
                        -0.5f, -0.25f, 0.0f,
                        1.0f, 0.0f, 0.0f,

                        0.5f, -0.25f, 0.0f,
                        0.0f, 0.0f, 1.0f,

                        0.0f, 0.559016994f, 0.0f,
                        0.0f, 1.0f, 0.0f },
                {
                        // X, Y, Z,
                        // R, G, B, A
                        -0.5f, -0.25f, 0.0f,
                        1.0f, 1.0f, 0.0f,

                        0.5f, -0.25f, 0.0f,
                        0.0f, 1.0f, 1.0f,

                        0.0f, 0.559016994f, 0.0f,
                        1.0f, 0.0f, 1.0f}

        };
        return (GLfloat *) triangleVerticesData[triangleIndex];

    }


};
// This triangle is white, gray, and black.

#endif //ANDROIDOPENGLESLESSONSCPP_QUANTIZEDCOLORNATIVE_H

