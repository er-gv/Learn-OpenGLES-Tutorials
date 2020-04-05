//
// Created by nathan on 05/04/20.
//

#ifndef ANDROIDOPENGLESLESSONSCPP_LOGGER_H
#define ANDROIDOPENGLESLESSONSCPP_LOGGER_H

#include <android/log.h>

#define INFO ANDROID_LOG_INFO
#define WARNS ANDROID_LOG_WARN
#define DEBUG ANDROID_LOG_DEBUG
#define ERROR ANDROID_LOG_ERROR
#define ASSERT ANDROID_LOG_VERBOSET

#define  LOGGER(SEVERITY, TAG, ...)  __android_log_print(SEVERITY ,LOG_TAG,__VA_ARGS__)

/*class Logger {
    const char* log_tag;
public:
    Logger(const char* tag);
    ~Logger();
    void printGLString(const char *name, GLenum s);

    void checkGlError(const char *op) ;
    void LOG(int argc, int type, ...);
    void inline LOGI(int argc, ...);
    void inline LOGD(int argc, ...);
    void inline  LOGE(int argc, ...);

};
*/

#endif //ANDROIDOPENGLESLESSONSCPP_LOGGER_H
