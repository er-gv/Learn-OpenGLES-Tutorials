//
// Created by nathan on 16/04/20.
//

#ifndef ANDROIDOPENGLESLESSONSCPP_TETRAHEDRON_H
#define ANDROIDOPENGLESLESSONSCPP_TETRAHEDRON_H



#include <cmath>
#include <string>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <GLES2/gl2.h>
#include <android/log.h>

#include "Polyhedron.h"
#include "graphics/GLUtils.h"

namespace Polyhedrons {

    class Tetrahedron : public Polyhedron {
        std::string  LogTag;
        static const int POSITION_DATA_SIZE = 3;
    static const int NORMAL_DATA_SIZE = 3;
    static const int TEX_DATA_SIZE = 2;
    static const int VERTEX_DATA_SIZE = BYTES_PER_FLOAT*(TEX_DATA_SIZE +NORMAL_DATA_SIZE +POSITION_DATA_SIZE);


    float* verticesData;
    GLuint materialProgram;
    GLuint wireframeProgram;

    // Attributes and uniforms handlers for the tetrahedron's material
    GLint positionAttributeHandle;
    GLint normalAttributeHandle;
    GLint lightPositionHandler;
    GLint brickColorHandler;
    GLint mortarColorHandler;
    GLint brickSizeHandler;
    GLint ptcSizeHandler;

    // Attributes and uniforms for the tetrahedron's wireframe
    GLint wireframeVetexAtributeHandle;
    GLint wireframeColorUniformHandle;

    GLint mMVPMatrixHandle;
    GLint mMVMatrixHandle;
    short trianglesIndexBuffer[4*3];// ={0,1,2, 3,1,0, 0,2,3, 3,2,1};
    short wireFrameLinesIndexBuffer[4*3]; //= {0,1,0,2,0,3,1,2,1,3,2,3};

    void buildBuffers();
    void initShaders();


    public:
        Tetrahedron();

        ~Tetrahedron();

        void create();
        virtual void render();

        void destroy();

        void printGLString(const char *msg, GLenum gle);
        void buildGeometry();
        void buildNormals();
        void sendDataToGPU();
    };
}

#endif //ANDROIDOPENGLESLESSONSCPP_TETRAHEDRON_H
