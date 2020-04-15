//
// Created by nathan on 10/04/20.
//

#include "PolyhedronsRenderer.h"

#include <jni.h>
#include <GLES2/gl2.h>
#include "../graphics/GLUtils.h"
#include "../graphics/Matrix.h"
//#include "utils/Logger.h"


PolyhedronsRenderer::PolyhedronsRenderer(){
   // logger = new Logger("Polyhedrons Renderer");
}
PolyhedronsRenderer::~PolyhedronsRenderer(){}
void PolyhedronsRenderer::create(){}
void PolyhedronsRenderer::change(int width, int height){}
void PolyhedronsRenderer::draw(){}
void PolyhedronsRenderer::destroy(){}

static PolyhedronsRenderer *renderer;

void PolyhedronsRenderer::printGLString(const char* msg, GLenum gle){

    //logger->LOG_I(msg, gle);
}

extern "C" JNIEXPORT void JNICALL
Java_com_learnopengles_android_Polyhedrons_PolyhedronsRenderer_nativeSurfaceCreate(
        JNIEnv *env, jclass type, jobject asset_manager) {

    GLUtils::setEnvAndAssetManager(env, asset_manager);
    if (renderer) {
        delete renderer;
        renderer = NULL;
    }

    // Print some OpenGL info
    renderer->printGLString("Version", GL_VERSION);
    renderer->printGLString("Vendor", GL_VENDOR);
    renderer->printGLString("Renderer", GL_RENDERER);
    renderer->printGLString("Extensions", GL_EXTENSIONS);

    renderer = new PolyhedronsRenderer();
    renderer->create();

}

extern "C" JNIEXPORT
void JNICALL
Java_com_learnopengles_android_Polyhedrons_PolyhedronsRenderer_nativeSurfaceChange(
        JNIEnv *env, jclass type, jint width, jint height) {

    if (renderer) {
        renderer->change(width, height);
    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_learnopengles_android_Polyhedrons_PolyhedronsRenderer_nativeDrawFrame(
        JNIEnv *env, jclass type) {

    if (renderer) {
        renderer->draw();
    }
}

