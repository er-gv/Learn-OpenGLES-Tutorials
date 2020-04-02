//
// Created by nathan on 02/04/20.
//

#include "AbstractSurfaceRendererNative.h"
#include <jni.h>
#include <cstdlib>

/*
#define  LOG_TAG    "AbstractSurface"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
*/



AbstractSurfaceRendererNative::AbstractSurfaceRendererNative() {
    mModelMatrix = NULL;
    mMVPMatrix = NULL;
    mProjectionMatrix = NULL;
    mViewMatrix = NULL;
    mProgram = -1;
}

AbstractSurfaceRendererNative::~AbstractSurfaceRendererNative() {
    delete mModelMatrix;
    mModelMatrix = NULL;
    delete mMVPMatrix;
    mMVPMatrix = NULL;
    delete mProjectionMatrix;
    mProjectionMatrix = NULL;
    delete mViewMatrix;
    mViewMatrix = NULL;
}

void AbstractSurfaceRendererNative::change(int width, int height) {

    glViewport(0, 0, width, height);

    // Create a new perspective projection matrix. The height will stay the same
    // while the width will vary as per aspect ratio.
    float ratio = (float) width / height;
    float left = -ratio;
    float right = ratio;
    float bottom = -1.0f;
    float top = 1.0f;
    float near = 1.0f;
    float far = 2.0f;

    mProjectionMatrix = Matrix::newFrustum(left, right, bottom, top, near, far);
}


/*

static AbstractSurfaceRendererNative *renderer;

extern "C" JNIEXPORT void JNICALL
Java_com_learnopengles_android_AbstractSurfaceRendererNative_nativeSurfaceCreate(
        JNIEnv *env,  jclass type, jobject assetManager) {

GLUtils::setEnvAndAssetManager(env, assetManager);
    if (renderer) {
        delete renderer;
        renderer = NULL;
    }
    //renderer = new QuantizedColorNative();
    //renderer->create();
}


extern "C" JNIEXPORT void JNICALL
Java_com_learnopengles_android_AbstractSurfaceRendererNative_nativeSurfaceChange(
        JNIEnv *env, jclass type, jint width, jint height) {

    if (renderer != nullptr) {
        renderer->change(width, height);
    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_learnopengles_android_AbstractSurfaceRendererNative_nativeDrawFrame(
        JNIEnv *env,jclass type) {

    if (renderer != nullptr) {
        renderer->draw();
    }
}

*/
