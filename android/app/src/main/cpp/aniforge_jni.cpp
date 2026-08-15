#include <jni.h>
#include <string>
#include <android/log.h>

#define LOG_TAG "AniForge"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

extern "C" {
    JNIEXPORT void JNICALL
    Java_com_aniforge_engine_MainActivity_nativeInit(JNIEnv *env, jobject obj) {
        LOGI("AniForge Engine Initialized!");
    }

    JNIEXPORT void JNICALL
    Java_com_aniforge_engine_MainActivity_nativeSetupGraphics(JNIEnv *env, jobject obj, 
                                                               jint width, jint height) {
        LOGI("Graphics Setup: %dx%d", width, height);
    }

    JNIEXPORT void JNICALL
    Java_com_aniforge_engine_MainActivity_nativeCleanup(JNIEnv *env, jobject obj) {
        LOGI("Cleaning up AniForge Engine");
    }
}
