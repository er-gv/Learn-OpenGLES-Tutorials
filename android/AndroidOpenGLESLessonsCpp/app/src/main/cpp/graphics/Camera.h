//
// Created by nathan on 05/04/20.
//

#ifndef ANDROIDOPENGLESLESSONSCPP_CAMERA_H
#define ANDROIDOPENGLESLESSONSCPP_CAMERA_H


#include <GLES2/gl2.h>
#include "./Matrix.h"

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

};


#endif //ANDROIDOPENGLESLESSONSCPP_CAMERA_H
