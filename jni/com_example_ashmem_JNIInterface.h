/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_example_ashmem_JNIInterface */

#ifndef _Included_com_example_ashmem_JNIInterface
#define _Included_com_example_ashmem_JNIInterface
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_example_ashmem_JNIInterface
 * Method:    initAndGetFd2Ashmem
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_example_ashmem_JNIInterface_initAndGetFd2Ashmem
  (JNIEnv *, jclass);


/*
 * Class:     com_example_ashmem_JNIInterface
 * Method:    doOperaNow
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_example_ashmem_JNIInterface_doOperaNow
  (JNIEnv *, jclass);

/*
 * Class:     com_example_ashmem_JNIInterface
 * Method:    doOperaLater
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_example_ashmem_JNIInterface_doOperaLater
  (JNIEnv *, jclass, jint);

#ifdef __cplusplus
}
#endif
#endif