//
// Created by nathan on 09/04/20.
//

#ifndef ANDROIDOPENGLESLESSONSCPP_JULIASETRENDERER_H
#define ANDROIDOPENGLESLESSONSCPP_JULIASETRENDERER_H


#include <jni.h>
#include <GLES2/gl2.h>
#include <string>
#include "../graphics/GLUtils.h"
#include "../graphics/Matrix.h"
#include "../utils/Logger.h"
//#include <glm/mat4x4.hpp>


class JuliaSetRenderer {

private:

    Logger *JuliaLogger;
    /** some matrix objects for transformations */
    Matrix* mModelMatrix;
    Matrix* mViewMatrix;
    Matrix* mProjectionMatrix;
    Matrix* mMVPMatrix;
    Matrix* mLightModelMatrix;

    /** handlers for shader attribs and uniforms. */
    GLuint mMVPMatrixHandle;
    GLuint mMVMatrixHandle;
    GLuint mLightPosHandle;
    GLuint mTextureUniformHandle;

    GLuint mPositionHandle;
    GLuint mColorHandle;
    GLuint mNormalHandle;
    GLuint mTextureCoordinateHandle;
    GLuint mJuliaSeedHandle;

    /** and the two handlers for the point light the julia shader programs */
    GLuint mJuliaProgramHandle;
    GLuint mLightProgramHandle;

    /** This will be used to pass in seed complex position for the julia renderer. */


    /** How many bytes per float. */
    static int const mBytesPerFloat = sizeof(float );

    /** Size of the position data in elements. */
    static const int mPositionDataSize = 3;

    /** Size of the color data in elements. */
    static const int mColorDataSize = 4;

    /** Size of the normal data in elements. */
    static const int mNormalDataSize = 3;

    /** Size of the texture coordinate data in elements. */
    static const int mTextureCoordinateDataSize = 2;

    /** Used to hold a light centered on the origin in model space. We need a 4th coordinate so we can get translations to work when
     *  we multiply this by our transformation matrices. */

    GLfloat mLightPosInWorldSpace[4];
    GLfloat mLightPosInEyeSpace[4];

    static constexpr float sqrt2_over_2 = M_SQRT2/2.0f;
    /** This is a handle to our texture data. */
    int mTextureDataHandle;

    //scene dimensions
    GLsizei mWidth;
    GLsizei mHeight;


    static GLfloat* getCubeGeometry();
    static GLfloat* getCubeColors();
    static GLfloat* getCubeNormals();
    static GLfloat* getCubeTexData();

    void create();
    bool compileShaders();
    void drawCube(const float seed[]);
    void drawLight();

public:
    static constexpr char TAG[] = "JuliaSetRenderer";
    JuliaSetRenderer();
    ~JuliaSetRenderer();

    void drawScene();

    void init();
    static void nativeSurfaceCreate();
    void surfaceChange(int width, int height);

    static void printGLString(const char *name, GLenum s) ;

    static void checkGlError(const char *op) ;


};


#endif //ANDROIDOPENGLESLESSONSCPP_JULIASETRENDERER_H
