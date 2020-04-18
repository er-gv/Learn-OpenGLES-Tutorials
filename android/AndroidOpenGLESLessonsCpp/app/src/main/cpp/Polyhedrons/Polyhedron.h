//
// Created by nathan on 16/04/20.
//

#ifndef ANDROIDOPENGLESLESSONSCPP_POLYHEDRON_H
#define ANDROIDOPENGLESLESSONSCPP_POLYHEDRON_H

#include "graphics/Matrix.h"
#include "graphics/GLUtils.h"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

//#include "../../../../../../../../../../../DevTool/Android-SDK/ndk/21.0.6113669/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/include/GLES2/gl2.h"

namespace Polyhedrons {

    class Polyhedron {

    protected:
        static const int BYTES_PER_FLOAT = sizeof(GLfloat);
        static const int BYTES_PER_SHORT = sizeof(GLshort);
        glm::vec3 *vertices;
        glm::vec3 *vertexNormals;
        glm::vec3 mPosition;
        GLuint vbo[1];
        GLuint ibo[1];

        virtual void buildVertices() = 0;

        virtual void buildNormals() = 0;

        virtual void buildBuffers() = 0;

    public:
        Polyhedron();

        virtual ~Polyhedron();

        void init();

        virtual void render() = 0;

        virtual void sendDataToGPU() = 0;
        void setPosition(float x, float y, float z);
        void setPosition(const glm::vec3& pos);

        void translate(float dx, float dy, float dz) ;
        void translate(const glm::vec3& delta);

        virtual void scale(float s) = 0;

        void  rotate(float angleInDegrees, float rx, float ry, float rz);
        void  rotate(float angleInDegrees, glm::vec3& axis);

        class Polygon {

        private:
            int *mIndices;
            glm::vec3 mNormal;
        public:
            Polygon(int vertices[]);

            ~Polygon();

            glm::vec3& getVertex(const Polyhedron &parent, int index);

            const glm::vec3 &getNormal();

            void setNormal(const glm::vec3 &normal);
        };


    };
}


#endif //ANDROIDOPENGLESLESSONSCPP_POLYHEDRON_H
