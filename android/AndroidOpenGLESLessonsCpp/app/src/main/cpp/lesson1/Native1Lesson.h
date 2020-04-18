//
// Created by biezhihua on 2017/7/9.
//

#ifndef OPENGLLESSON_NATIVE1LESSON_H
#define OPENGLLESSON_NATIVE1LESSON_H

#include <GLES2/gl2.h>
#include "../graphics/Matrix.h"
#include <glm/vec2.hpp>
class Native1Lesson {

public:

    Native1Lesson();

    ~Native1Lesson();

    void create();

    void change(int width, int height);

    void draw();

    void drawTriangle(GLfloat *verticesData);

private:

    Matrix *mViewMatrix;
    Matrix *mModelMatrix;
    Matrix *mProjectionMatrix;
    Matrix *mMVPMatrix;

    GLuint mProgram;

    GLuint mMVPMatrixHandle;
    GLuint mPositionHandle;
    GLuint mColorHandle;
    glm::vec2 hey, bee, see;


};

#endif //OPENGLLESSON_NATIVE1LESSON_H
