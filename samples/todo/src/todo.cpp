#include <jni.h>

extern "C" jstring Java_libnative_ui_MainActivity_stringFromJNI(JNIEnv *env, jobject /* this */)
{
    return env->NewStringUTF("Hello from C++");
}
