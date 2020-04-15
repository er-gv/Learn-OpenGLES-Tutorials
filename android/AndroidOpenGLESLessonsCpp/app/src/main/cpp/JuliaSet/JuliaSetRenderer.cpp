//
// Created by nathan on 09/04/20.
//

#include "JuliaSetRenderer.h"
#include <jni.h>
#include "utils/Logger.h"
#include "graphics/GLUtils.h"
#include "utils/Scene.h"
#include <cmath>
#define  JULIA_TAG "JuliaSetRenderer"

static constexpr GLfloat defaultSeed[]= {0.5f, 0.5f};
static constexpr float  mLightPosInModelSpace[] ={0.0f, 0.0f, 0.0f, 1.0f};

JuliaSetRenderer::JuliaSetRenderer(){
    Scene s;
    JuliaLogger = new Logger(JULIA_TAG);
}

JuliaSetRenderer::~JuliaSetRenderer(){
    delete  JuliaLogger;

    if(mModelMatrix)
        delete mModelMatrix;
    if(mViewMatrix)
        delete mViewMatrix;
    if(mProjectionMatrix)
        delete mProjectionMatrix;
    if(mMVPMatrix)
        delete mMVPMatrix;
    if(mLightModelMatrix)
        delete mLightModelMatrix;
}

bool JuliaSetRenderer::compileShaders(){
    // Set program handles
    const char* vertex_shader = GLUtils::openTextFile("shaders/vertex/per_pixel_vertex_shader.glsl");
    const char* fragment_shader = GLUtils::openTextFile("shaders/fragment/per_pixel_julia_fragment_shader.glsl");
    mJuliaProgramHandle = GLUtils::createProgram(&vertex_shader, &fragment_shader);
    if (!mJuliaProgramHandle) {
        LOG_I(JULIA_TAG, "Could not create program");
        return false;
    }

    // Set Point program handle
    vertex_shader = GLUtils::openTextFile("shaders/vertex/point_vertex_shader.glsl");
    fragment_shader = GLUtils::openTextFile("shaders/fragment/point_fragment_shader.glsl");
    mLightProgramHandle = GLUtils::createProgram(&vertex_shader, &fragment_shader);
    if (!mLightProgramHandle) {
        LOG_D(JULIA_TAG, "Could not create program");
        return false;
    }
    return true;
}

void JuliaSetRenderer::init(){
    if(compileShaders())
        create();
}

void JuliaSetRenderer::create(){
    LOG_D(JULIA_TAG, "Renderer create");

    // Set the background clear color to black.
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

   // Enable texture mapping
    glEnable(GL_TEXTURE_2D);
    // Use culling to remove back face.
    glEnable(GL_CULL_FACE);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    mLightModelMatrix = new Matrix();
    mModelMatrix = new Matrix();
    mMVPMatrix = new Matrix();

    // Position the eye in front of the origin.
    float eyeX = 0.0f;
    float eyeY = 0.0f;
    float eyeZ = 1.5f;

    // We are looking at the origin
    float centerX = 0.0f;
    float centerY = 0.0f;
    float centerZ = -5.0f;

    // Set our up vector.
    float upX = 0.0f;
    float upY = 1.0f;
    float upZ = 0.0f;

    // Set the view matrix.
    mViewMatrix = Matrix::newLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);

    // Load the texture
    mTextureDataHandle = GLUtils::loadTexture("texture/bumpy_bricks_public_domain.jpg");
}

void JuliaSetRenderer::surfaceChange(int width, int height){
    JuliaLogger->checkGlError("knjhkjhkj");
    LOG_D(JULIA_TAG, "@JuliaSetRenderer::nativeSurfaceChange");

    mWidth = width;
    mHeight = height;

    glViewport(0, 0, mWidth, mHeight);

    // Create a new perspective projection matrix. The height will stay the same
    // while the width will vary as per aspect ratio.
    float ratio = (float) width / height;
    float left = -ratio;
    float right = ratio;
    float bottom = -1.0f;
    float top = 1.0f;
    float near = 1.0f;
    float far = 10.0f;

    mProjectionMatrix = Matrix::newFrustum(left, right, bottom, top, near, far);
}

void JuliaSetRenderer::drawScene(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Do a complete rotation every 10 seconds.
    long time = GLUtils::currentTimeMillis() % 10000L;
    float angleInDegrees = (360.0f / 10000.0f) * ((int) time);
    double radians = angleInDegrees*(M_PI/180.0f);
    // Set our per-vertex lighting program.
    char buff[80];
    char* msg = strdup(buff);
    sprintf(buff, "DEG/RAD %f / %f.\n", angleInDegrees, radians);
    __android_log_print(ANDROID_LOG_INFO, JULIA_TAG, "%s", msg);
    free (msg);
    glUseProgram(mJuliaProgramHandle);

    // Set program handles for cube drawing.
    // attribs
    mPositionHandle = glGetAttribLocation(mJuliaProgramHandle, "a_Position");
    mColorHandle = glGetAttribLocation(mJuliaProgramHandle, "a_Color");
    mNormalHandle = glGetAttribLocation(mJuliaProgramHandle, "a_Normal");
    mTextureCoordinateHandle = glGetAttribLocation(mJuliaProgramHandle, "a_TexCoordinate");

    //uniforms
    mMVPMatrixHandle = glGetUniformLocation(mJuliaProgramHandle, "u_MVPMatrix");
    mMVMatrixHandle = glGetUniformLocation(mJuliaProgramHandle, "u_MVMatrix");
    mLightPosHandle = glGetUniformLocation(mJuliaProgramHandle, "u_LightPos");
    mTextureUniformHandle = glGetUniformLocation(mJuliaProgramHandle, "u_Texture");
    mJuliaSeedHandle = glGetUniformLocation(mJuliaProgramHandle, "c_seed");


    float rotatedSeed[2]= {defaultSeed[0], defaultSeed[1]};
    // Set the active texture unit to texture unit 0.
    glActiveTexture(GL_TEXTURE0);

    // Bind the texture to this unit.
    glBindTexture(GL_TEXTURE_2D, mTextureDataHandle);

    // Tell the texture uniform sampler to use this texture in the shader by binding to texture unit 0.
    glUniform1i(mTextureUniformHandle, 0);

    // Calculate position of the light. Rotate and then push into the distance.
    mLightModelMatrix->identity();
    mLightModelMatrix->translate(0.0f, 0.0f, -5.0f);
    mLightModelMatrix->rotate(angleInDegrees, 0.0f, 1.0f, 0.0f);
    mLightModelMatrix->translate(0.0f, 0.0f, 2.0f);

    Matrix::multiplyMV(mLightPosInWorldSpace, mLightModelMatrix->mData, mLightPosInModelSpace);
    Matrix::multiplyMV(mLightPosInEyeSpace, mViewMatrix->mData, mLightPosInWorldSpace);

    // Draw some cubes.
    mModelMatrix->identity();
    mModelMatrix->translate(4.0f, 0.0f, -7.0f);
    mModelMatrix->rotate(angleInDegrees, 1.0f, 0.0f, 0.0f);
    rotatedSeed[0]=(float)(cos(radians));
    rotatedSeed[1]=(float)(sin(radians));
    drawCube(defaultSeed);

    mModelMatrix->identity();
    mModelMatrix->translate(-4.0f, 0.0f, -7.0f);
    mModelMatrix->rotate(angleInDegrees, 0.0f, 1.0f, 0.0f);
    drawCube(rotatedSeed);

    mModelMatrix->identity();
    mModelMatrix->translate(0.0f, 4.0f, -7.0f);
    mModelMatrix->rotate(angleInDegrees, 0.0f, 0.0f, 1.0f);
    drawCube(rotatedSeed);

    mModelMatrix->identity();
    mModelMatrix->translate( 0.0f, -4.0f, -7.0f);
    mModelMatrix->rotate(angleInDegrees, 1.0f, 1.0f, 0.0f);
    drawCube(rotatedSeed);

    mModelMatrix->identity();
    mModelMatrix->translate(0.0f, 0.0f, -5.0f);
    mModelMatrix->rotate(angleInDegrees, sqrt2_over_2, sqrt2_over_2, sqrt2_over_2);
    drawCube(defaultSeed);

    // Draw a point to indicate the light.
    drawLight();
}

/** Used for debug logs. */


// X, Y, Z
GLfloat* JuliaSetRenderer::getCubeGeometry(){
    static GLfloat geometry[]= {
                // In OpenGL counter-clockwise winding is default. This means that when we look at a triangle,
                // if the points are counter-clockwise we are looking at the "front". If not we are looking at
                // the back. OpenGL has an optimization where all back-facing triangles are culled, since they
                // usually represent the backside of an object and aren't visible anyways.

                // Front face
                -1.0f, 1.0f, 1.0f,
                -1.0f, -1.0f, 1.0f,
                1.0f, 1.0f, 1.0f,
                -1.0f, -1.0f, 1.0f,
                1.0f, -1.0f, 1.0f,
                1.0f, 1.0f, 1.0f,

                // Right face
                1.0f, 1.0f, 1.0f,
                1.0f, -1.0f, 1.0f,
                1.0f, 1.0f, -1.0f,
                1.0f, -1.0f, 1.0f,
                1.0f, -1.0f, -1.0f,
                1.0f, 1.0f, -1.0f,

                // Back face
                1.0f, 1.0f, -1.0f,
                1.0f, -1.0f, -1.0f,
                -1.0f, 1.0f, -1.0f,
                1.0f, -1.0f, -1.0f,
                -1.0f, -1.0f, -1.0f,
                -1.0f, 1.0f, -1.0f,

                // Left face
                -1.0f, 1.0f, -1.0f,
                -1.0f, -1.0f, -1.0f,
                -1.0f, 1.0f, 1.0f,
                -1.0f, -1.0f, -1.0f,
                -1.0f, -1.0f, 1.0f,
                -1.0f, 1.0f, 1.0f,

                // Top face
                -1.0f, 1.0f, -1.0f,
                -1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, -1.0f,
                -1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, -1.0f,

                // Bottom face
                1.0f, -1.0f, -1.0f,
                1.0f, -1.0f, 1.0f,
                -1.0f, -1.0f, -1.0f,
                1.0f, -1.0f, 1.0f,
                -1.0f, -1.0f, 1.0f,
                -1.0f, -1.0f, -1.0f
        };
    return  geometry;
}

GLfloat* JuliaSetRenderer::getCubeColors() {
// R, G, B, A
    static GLfloat cubeColorData[] = {
            // Front face (red)
            1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 1.0f,

            // Right face (green)
            0.0f, 1.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f, 1.0f,

            // Back face (blue)
            0.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 1.0f,

            // Left face (yellow)
            1.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 0.0f, 1.0f,

            // Top face (cyan)
            0.0f, 1.0f, 1.0f, 1.0f,
            0.0f, 1.0f, 1.0f, 1.0f,
            0.0f, 1.0f, 1.0f, 1.0f,
            0.0f, 1.0f, 1.0f, 1.0f,
            0.0f, 1.0f, 1.0f, 1.0f,
            0.0f, 1.0f, 1.0f, 1.0f,

            // Bottom face (magenta)
            1.0f, 0.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 1.0f
    };
    return cubeColorData;
}

GLfloat* JuliaSetRenderer::getCubeNormals() {
// X, Y, Z
// The normal is used in light calculations and is a vector which points
// orthogonal to the plane of the surface. For a cube model, the normals
// should be orthogonal to the points of each face.
    static GLfloat cubeNormalData[] = {

            // Front face
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,


            // Right face
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,


            // Back face
            0.0f, 0.0f, -1.0f,
            0.0f, 0.0f, -1.0f,
            0.0f, 0.0f, -1.0f,
            0.0f, 0.0f, -1.0f,


            // Left face
            -1.0f, 0.0f, 0.0f,
            -1.0f, 0.0f, 0.0f,
            -1.0f, 0.0f, 0.0f,
            -1.0f, 0.0f, 0.0f,

            // Top face
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,


            // Bottom face
            0.0f, -1.0f, 0.0f,
            0.0f, -1.0f, 0.0f,
            0.0f, -1.0f, 0.0f,
            0.0f, -1.0f, 0.0f
    };
    return cubeNormalData;
}

GLfloat* JuliaSetRenderer::getCubeTexData() {
// S, T (or X, Y)
// Texture coordinate data.
// Because images have a Y axis pointing downward (values increase as you move down the image) while
// OpenGL has a Y axis pointing upward, we adjust for that here by flipping the Y axis.
// What's more is that the texture coordinates are the same for every face.
    static GLfloat cubeTextureCoordinateData[] = {
            // Front face
            0.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f,

            // Right face
            0.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f,

            // Back face
            0.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f,

            // Left face
            0.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f,

            // Top face
            0.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f,

            // Bottom face
            0.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f
    };
    return cubeTextureCoordinateData;
}


/**
 * Draws a cube.
 */
void JuliaSetRenderer::drawCube(const float seed[]){
    // Pass in the position information

    glVertexAttribPointer(mPositionHandle, mPositionDataSize, GL_FLOAT, false,
                                 0, getCubeGeometry());
    glEnableVertexAttribArray(mPositionHandle);

    // Pass in the color information

    glVertexAttribPointer(mColorHandle, mColorDataSize, GL_FLOAT, false,
                                 0, getCubeColors());
    glEnableVertexAttribArray(mColorHandle);

    // Pass in the normal information
    glVertexAttribPointer(mNormalHandle, mNormalDataSize, GL_FLOAT, false,
                                 0, getCubeNormals());
    glEnableVertexAttribArray(mNormalHandle);

    // Pass in the texture coordinate information
    glVertexAttribPointer(mTextureCoordinateHandle,
                          mTextureCoordinateDataSize, GL_FLOAT, false,
                                 0, getCubeTexData());
    glEnableVertexAttribArray(mTextureCoordinateHandle);

    //Multiplies the view by the model matrix and stores the result the MVP matrix.
    // which currently contains model * view
    mMVPMatrix->multiply(*mViewMatrix, *mModelMatrix);

    // Pass in the model view matrix
    glUniformMatrix4fv(mMVMatrixHandle, 1, GL_FALSE, mMVPMatrix->mData);

    // This multiplies the model view matrix by the projection matrix
    // and stores the result in the MVP matrix.
    // which no contains model * view * projection
    mMVPMatrix->multiply(*mProjectionMatrix, *mMVPMatrix);

    // Pass in the model view projection matrix
    glUniformMatrix4fv(  mMVPMatrixHandle, 1, GL_FALSE, mMVPMatrix->mData);

    // Pass in the light position in eye space
    glUniform3f(mLightPosHandle,
            mLightPosInEyeSpace[0],
            mLightPosInEyeSpace[1],
            mLightPosInEyeSpace[2]
    );

    // Draw the cube.
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

/**
 * Draws a point representing the position of the light.
 */
void JuliaSetRenderer::drawLight(){

    const int pointMVPMatrixHandle = glGetUniformLocation(mLightProgramHandle, "u_MVPMatrix");
    const int pointPositionHandle = glGetAttribLocation(mLightProgramHandle, "a_Position");

    // Pass in the position.
    glVertexAttrib3f(pointPositionHandle, mLightPosInModelSpace[0], mLightPosInModelSpace[1], mLightPosInModelSpace[2]);

    // Since we are not using a buffer object, disable vertex arrays for this attribute.
    glDisableVertexAttribArray(pointPositionHandle);

    // Pass in the transformation matrix.
    mMVPMatrix->identity();
    mMVPMatrix->multiply(*mViewMatrix, *mLightModelMatrix);
    mMVPMatrix->multiply(*mProjectionMatrix, *mMVPMatrix);

    glUniformMatrix4fv(
            pointMVPMatrixHandle,
            1,
            GL_FALSE,
            mMVPMatrix->mData
    );

    // Draw the point.
    glUseProgram(mLightProgramHandle);
    glDrawArrays(GL_POINTS, 0, 1);
}


static JuliaSetRenderer *renderer;

extern "C" JNIEXPORT void JNICALL
Java_com_learnopengles_android_JuliaSet_JuliaSetRenderer_nativeSurfaceCreate(
        JNIEnv *env, jclass type, jobject asset_manager) {

    GLUtils::setEnvAndAssetManager(env, asset_manager);
    if (renderer) {
        delete renderer;
        renderer = NULL;
    }
    renderer = new JuliaSetRenderer();
    if (renderer != nullptr) {
        renderer->init();
    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_learnopengles_android_JuliaSet_JuliaSetRenderer_nativeSurfaceChange(
        JNIEnv *env, jclass type, jint width, jint height) {

    if (renderer != nullptr) {
        renderer->surfaceChange(width, height);
    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_learnopengles_android_JuliaSet_JuliaSetRenderer_nativeDrawFrame(JNIEnv *env, jclass type) {

    if (renderer != nullptr) {
        renderer->drawScene();
    }
}
