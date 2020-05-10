//
// Created by nathan on 05/04/20.
//

#ifndef ANDROIDOPENGLESLESSONSCPP_CAMERA_H
#define ANDROIDOPENGLESLESSONSCPP_CAMERA_H


#include <GLES2/gl2.h>
#include "./Matrix.h"
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

class Camera {
    GLfloat m_eye[3];
    GLfloat m_lookat[3];
    GLfloat m_up[3];


public:
    Camera();
    Camera(GLfloat eye[3], GLfloat lookat[3], GLfloat up[3]);
    Camera(GLfloat eyex, GLfloat eyey, GLfloat eyez,
           GLfloat lookatx, GLfloat lookaty, GLfloat lookatz,
           GLfloat upx, GLfloat upy,  GLfloat upz);
    ~Camera();

    glm::mat4 projection(float fov, float ratio, float near, float far);

    glm::mat4 projection();
    glm::mat4 viewport();

};


#endif //ANDROIDOPENGLESLESSONSCPP_CAMERA_H
