//
// Created by nathan on 05/04/20.
//

#include "Logger.h"

/*
Logger::Logger(const char* tag) {
    log_tag = strdup(tag);
}

Logger::~Logger(){}

void Logger::printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI(2, "GL %s = %s \n", name, v);
}

void Logger::checkGlError(const char *op) {
    for (GLint error = glGetError(); error; error = glGetError()) {
        LOGI(2, "after %s() glError (0x%x)\n", op, error);
    }
}

#define abc __android_log_print(ANDROID_LOG_INFO,log_tag, __VA_ARGS__)
void  Logger::LOG(int argc, int type, ...) {
    va_list args;
    __android_log_print(type, log_tag, "__VA_ARGS__");
}

void  Logger::LOGI(int argc, ...)  {va_list args; LOG(argc, ANDROID_LOG_INFO, args);}
void  Logger::LOGD(int argc, ...)  {va_list args; LOG(argc, ANDROID_LOG_DEBUG, args);}
void  Logger::LOGE(int argc, ...)  {va_list args; LOG(argc, ANDROID_LOG_ERROR, args);}


*/