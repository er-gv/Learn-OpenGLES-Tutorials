//
// Created by nathan on 16/04/20.
//

#include "Polyhedron.h"

namespace Polyhedrons {

    Polyhedron::Polyhedron() {
        mPosition = glm::vec3(0.0f, 0.0f, 0.0f);
        vertices = nullptr;
        vertexNormals = nullptr;
    }

    Polyhedron::~Polyhedron() {
        if(nullptr != vertices) {
            delete vertices;
        }
        if(nullptr != vertexNormals) {
            delete vertexNormals;
        }

    }

    void Polyhedron::init() {
         buildVertices();
         buildNormals();
         buildBuffers();
    }

    void Polyhedron::setPosition(float x, float y, float z){
        mPosition = glm::vec3(x, y, z);
    }

    void Polyhedron::setPosition(const glm::vec3& pos){
        mPosition = pos;
    }

    void Polyhedron::translate(float dx, float dy, float dz) {
        mPosition.x += dx;
        mPosition.y += dy;
        mPosition.z += dz;
        glm::vec3 v;
        mPosition+= v;
    }

    void Polyhedron::translate(const  glm::vec3& delta) {
        mPosition+= delta;
    }


    void  Polyhedron::rotate(float angleInDegrees, float rx, float ry, float rz) {
        glm::mat4 mat = glm::mat4(1.0f);
        glm::rotate(glm::mat4(1.0f), glm::radians(angleInDegrees), glm::vec3(rx, ry, rz));
        //mPosition*= mat;
    }

    void  Polyhedron::rotate(float angleInDegrees, glm::vec3& axis){
        glm::mat4 mat = glm::mat4(1.0f);
        glm::rotate(glm::mat4(1.0f), glm::radians(angleInDegrees), axis);
       // mPosition*= mat;
    }


/**********************************************************
 *  Inner class Polygon
 *
 ***********************************************************/


    Polyhedron::Polygon::Polygon(int indices[]) {
        mIndices = new int[sizeof(indices)/ sizeof(int)];
        mNormal = glm::vec3(0.0f, 0.0f, 0.0f);
    }

    Polyhedron::Polygon::~Polygon() {
        delete mIndices;
    }

    glm::vec3& Polyhedron::Polygon::getVertex(const Polyhedron& parent, int index) {
        return parent.vertices[mIndices[index]];
    }

    const glm::vec3&  Polyhedron::Polygon::getNormal() {
        return mNormal;
    }

    void Polyhedron::Polygon::setNormal(const glm::vec3& normal) {
        mNormal = normal;
    }
}