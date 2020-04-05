//
// Created by biezhihua on 2017/7/15.
//

#ifndef OPENGLLESSON_NATIVEFOURLESSON_H
#define OPENGLLESSON_NATIVEFOURLESSON_H

#include <GLES2/gl2.h>
#include <graphics/Matrix.h>

class Native4Lesson {

public:

    Native4Lesson();

    virtual ~Native4Lesson();

    virtual void create();

    void change(int width, int height);

    virtual void draw();

private:

    GLsizei mWidth;
    GLsizei mHeight;

    Matrix *mLightModelMatrix;

    GLuint mMVPMatrixHandle;
    GLuint mMVMatrixHandle;
    GLuint mLightPosHandle;
    GLuint mPositionHandle;
    GLuint mColorHandle;
    GLuint mNormalHandle;
    GLuint mTextureUniformHandle;
    GLuint mTextureCoordinateHandle;

    GLuint mTextureDataHandle;

    GLuint mPerVertexProgramHandle;
    GLuint mPointProgramHandle;

    float mLightPosInModelSpace[4];
    float mLightPosInWorldSpace[4];
    float mLightPosInEyeSpace[4];

    Matrix *mViewMatrix;
    Matrix *mModelMatrix;
    Matrix *mProjectionMatrix;
    Matrix *mMVPMatrix;
    GLuint mProgram;

    void drawCube();

    void drawLight();
};

#endif //OPENGLLESSON_NATIVEFOURLESSON_H
