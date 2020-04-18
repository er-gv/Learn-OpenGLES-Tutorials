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

    glm::mat4 camera(float Translate, glm::vec2 const & Rotate)
    {
        glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);
        glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
        View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
        View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
        return Projection * View * Model;
    }
};


#endif //ANDROIDOPENGLESLESSONSCPP_CAMERA_H
