//
// Created by nathan on 16/04/20.
//

#include "Tetrahedron.h"
#include <GLES2/gl2.h>
#include <android/log.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>

namespace Polyhedrons {
    Tetrahedron::Tetrahedron() : Polyhedron(), LogTag("TETRAHEDRON"){

        vertexNormals = new glm::vec3[4];
        vertices = new glm::vec3[4];

    }

    Tetrahedron::~Tetrahedron() {
        destroy();
    }

    void Tetrahedron::create() {
        buildGeometry();
        buildBuffers();
        initShaders();
    }

    void Tetrahedron::initShaders() {
        {
            const char *vertex_shader = GLUtils::openTextFile(
                    "/shaders/vertex/color_vertex_shader");
            const char *fragment_shader = GLUtils::openTextFile(
                    "/shaders/fragment/color_vertex_shader");
            wireframeProgram = GLUtils::createProgram(&vertex_shader, &fragment_shader);

        }
        {
            const char *vertex_shader = GLUtils::openTextFile(
                    "/shaders/vertex/bricks_vertex_shader");
            const char *fragment_shader = GLUtils::openTextFile(
                    "/shaders/fragment/bricks_vertex_shader");
            materialProgram = GLUtils::createProgram(&vertex_shader, &fragment_shader);
        }
        if (wireframeProgram && materialProgram) {

            // Bind Attributes and uniforms for the tetrahedron's material
            positionAttributeHandle = glGetAttribLocation(materialProgram, "MCvertex");
            normalAttributeHandle = glGetAttribLocation(materialProgram, "MCnormal");
            lightPositionHandler = glGetUniformLocation(materialProgram, "u_LightPosition");
            brickColorHandler = glGetUniformLocation(materialProgram, "u_BrickColor");
            mortarColorHandler = glGetUniformLocation(materialProgram, "u_MortarColor");
            brickSizeHandler = glGetUniformLocation(materialProgram, "u_BrickSize");
            ptcSizeHandler = glGetUniformLocation(materialProgram, "u_LightPosition");
            mMVPMatrixHandle = glGetUniformLocation(materialProgram, "u_MVPMatrix");
            mMVMatrixHandle = glGetUniformLocation(materialProgram, "u_MVMatrix");


            // Bind Attributes and uniforms for the tetrahedron's wireframe
            wireframeVetexAtributeHandle = glGetAttribLocation(wireframeProgram, "a_Position");
            wireframeColorUniformHandle = glGetUniformLocation(wireframeProgram, "a_Color");
        }
    }


    void Tetrahedron::destroy() {
        delete vertices;
        delete vertexNormals;
        if (nullptr != verticesData)
            delete verticesData;
    }

    void Tetrahedron::buildGeometry() {
        float phiAngles = -19.471220333f; /* the phi angle needed for generation */

        float r = 1.0f; /* any radius in which the polyhedron is inscribed */
        /* first vertex */
        float phiRadians = glm::radians(phiAngles);
        float deltaTheta = glm::radians(120.0f);
        vertices[0] = glm::vec3(0.0f, 0.0f, r);
        float theta = 0.0f;
        float rCosPhi = r * cos(phiRadians);
        float rMultsinPhi = r * sin(phiRadians);
        for (int i = 1; i < 4; i++) {
            vertices[i] = glm::vec3(cos(theta * 2) * rCosPhi, rMultsinPhi,
                                    sin(theta * 2) * rCosPhi);
            theta += deltaTheta;
        }
        {
            char buffer[100];
            for (int i = 0; i < 4; i++) {
                sprintf(buffer, "vertices[%d] = (%f, %f, %f).", i, vertices[i].x, vertices[i].y,
                        vertices[i].z);
                __android_log_print(ANDROID_LOG_INFO, Tetrahedron::LogTag.c_str(), "jjj", buffer);
            }
        }
    }

    void Tetrahedron::render() {

        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

        glEnableVertexAttribArray(positionAttributeHandle);
        glEnableVertexAttribArray(normalAttributeHandle);


        glVertexAttribPointer(positionAttributeHandle, POSITION_DATA_SIZE, GL_FLOAT, false,
                              VERTEX_DATA_SIZE, verticesData);
        glVertexAttribPointer(normalAttributeHandle, NORMAL_DATA_SIZE, GL_FLOAT, false,
                              VERTEX_DATA_SIZE, verticesData+POSITION_DATA_SIZE*BYTES_PER_FLOAT);

        /*glVertexAttribPointer(texAttributeHandle, TEX_DATA_SIZE, GL_FLOAT, false, VERTEX_DATA_SIZE,
                              24);**/

        //pass in cloud and sky color.
        int skyColorLoc = glGetUniformLocation(7, "u_skyColor");
        int cloudColorLoc = glGetUniformLocation(7, "u_cloudColor");
        glUniform3f(cloudColorLoc, 0.8f, 0.8f, 0.8f);
        glUniform3f(skyColorLoc, 0.0f, 0.0f, 0.65f);


        // Set the active texture unit to texture unit 0.
        //GLES20.glActiveTexture(GLES20.GL_TEXTURE0);


        //draw triangles
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo[0]);

        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_SHORT, 0);

        //draw wireframe
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo[1]);
        glDrawElements(GL_LINES, 12, GL_UNSIGNED_SHORT, 0);

        //unbind the buffers and the vertices attribs
        glDisableVertexAttribArray(normalAttributeHandle);
        glDisableVertexAttribArray(positionAttributeHandle);
        //glDisableVertexAttribArray(texAttributeHandle);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void Tetrahedron::printGLString(const char *msg, GLenum gle) {
        __android_log_print(ANDROID_LOG_INFO, Tetrahedron::LogTag.c_str(), msg, gle);
    }

    void Tetrahedron::buildBuffers() {


        verticesData = new float[TEX_DATA_SIZE + NORMAL_DATA_SIZE + POSITION_DATA_SIZE];
        memcpy(verticesData,
               (float[]){

                       ////////////////////////////////////////////////////////////
                       //vertex 0
                       //
                       vertices[0].x, vertices[0].y, vertices[0].z, //spatial data 0
                       vertexNormals[0].x, vertexNormals[0].y, vertexNormals[0].z, //normal data 0
                       0.5f, 0.5f, //tex data 0

                       ////////////////////////////////////////////////////////////
                       //vertex 1
                       //
                       vertices[1].x, vertices[1].y, vertices[1].z, //spatial data 1
                       vertexNormals[1].x, vertexNormals[1].y, vertexNormals[1].z, //normal data 1
                       0.0f, 0.0f, //tex data 1

                       ////////////////////////////////////////////////////////////
                       //vertex 2
                       //
                       vertices[2].x, vertices[2].y, vertices[2].z, //spatial data 2
                       vertexNormals[2].x, vertexNormals[2].y, vertexNormals[2].z, //normal data 2
                       1.0f, 0.0f, //tex data 2

                       ////////////////////////////////////////////////////////////
                       //vertex 3
                       //
                       vertices[3].x, vertices[3].y, vertices[3].z, //spatial data 3
                       vertexNormals[3].x, vertexNormals[3].y, vertexNormals[3].z, //normal data 3
                       0.5f, 1.0f //tex data 3

               }, VERTEX_DATA_SIZE);

        short trianglesIndexBuffer[] = {0, 1, 2, 3, 1, 0, 0, 2, 3, 3, 2, 1};
        short wireFrameLinesIndexBuffer[] = {0, 1, 0, 2, 0, 3, 1, 2, 1, 3, 2, 3};
    }

    void Tetrahedron::sendDataToGPU() {
        glGenBuffers(1, vbo);
        glGenBuffers(2, ibo);

        if (vbo[0] > 0 && ibo[0] > 0) {
            glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
            glBufferData(GL_ARRAY_BUFFER, VERTEX_DATA_SIZE, verticesData, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo[0]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(trianglesIndexBuffer),
                         trianglesIndexBuffer, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo[1]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(wireFrameLinesIndexBuffer),
                         wireFrameLinesIndexBuffer, GL_STATIC_DRAW);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

    }


    void Tetrahedron::buildNormals() {
        Polyhedron::Polygon faces[] = {
                /* map vertices to 4 faces */
                Polygon((int[]){0, 1, 2}),
                Polygon((int[]){0, 2, 3}),
                Polygon((int[]){0, 3, 1}),
                Polygon((int[]){1, 2, 3})
        };
        int nFaces = 4;
        glm::vec3 *faceNormals = new glm::vec3[nFaces];

        for (int i = 0; i < nFaces; i++) {
            glm::vec3 const &v0 = faces[i].getVertex(*this, 0);
            glm::vec3 const &v1 = faces[i].getVertex(*this, 1);
            glm::vec3 const &v2 = faces[i].getVertex(*this, 2);
            faceNormals[i] = glm::cross(v0 -v1, v0 -v2);
        }


        /*vertexNormals[0] = faceNormals[0]+ faceNormals[1];
        //+faceNormals[2])/3.0f;
        vertexNormals[1] = Vector3D.avarage(new Vector3D[]{faceNormals[0], faceNormals[2], faceNormals[3]});
        vertexNormals[2] = Vector3D.avarage(new Vector3D[]{faceNormals[0], faceNormals[1], faceNormals[3]});
        vertexNormals[3] = Vector3D.avarage(new Vector3D[]{faceNormals[1], faceNormals[2], faceNormals[3]})
        */
        for (int i = 0; i < 4; i++) {
            glm::normalize(vertexNormals[i]);
        }
        {
            char buffer[100];
            for (int i = 0; i < 4; i++) {
                sprintf(buffer, "normal[%d] = (%f, %f, %f).", i,
                        vertexNormals[i].x, vertexNormals[i].y, vertexNormals[i].z);
                __android_log_print(ANDROID_LOG_INFO, Tetrahedron::LogTag.c_str(), "format", buffer);
            }
        }

    }
}
