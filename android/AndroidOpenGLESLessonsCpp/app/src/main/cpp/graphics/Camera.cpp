//
// Created by nathan on 05/04/20.
//

#include "Camera.h"
#include <cstring>
#include <android/log.h>
#include <GLES2/gl2.h>

Camera::Camera(){
    m_eye[0]=m_eye[1]=m_eye[2]=0.0;
    m_up[0]=0.0f; m_up[1]=1.0f; m_up[2]=0.0f;
    m_lookat[0]=0.0f; m_lookat[1]=0.0f; m_lookat[2]=-1.0f;

}

Camera::Camera(GLfloat eye[3], GLfloat lookat[3], GLfloat up[3]){
    memcpy(m_eye,eye, sizeof(eye));
    memcpy(m_up,up, sizeof(m_up));
    memcpy(m_lookat, lookat, sizeof(m_lookat));

}

Camera::Camera(GLfloat eyex, GLfloat eyey, GLfloat eyez,
        GLfloat lookatx, GLfloat lookaty, GLfloat lookatz,
GLfloat upx, GLfloat upy,  GLfloat upz){

    m_eye[0]=eyex;    m_eye[1]=eyey;    m_eye[2]=eyez;
    m_up[0]=upx;      m_up[1]=upy;      m_up[2]=upz;
    m_lookat[0]=lookatx; m_lookat[1]=lookaty; m_lookat[2]=lookatz;

}

Camera::~Camera(){}

glm::mat4 Camera::projection(float fov, float ratio, float near, float far) {
    return glm::perspective(fov, ratio, near, far);
}


glm::mat4 Camera::projection() {
    return glm::mat4();
}

glm::mat4 Camera::viewport() {
    return glm::mat4();
}



