/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
#include "FileOperate.h"
#include "MyLog.h"


/* Header for class com_brunjoy_jni_JNI */

#ifndef _Included_com_brunjoy_jni_JNI
#define _Included_com_brunjoy_jni_JNI

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_brunjoy_jni_JNI
 * Method:    a
 * Signature: ([BI)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_brunjoy_jni_JNI_readFile(JNIEnv * env,
		jclass obj, jstring fileName) {
	LOGI("开始读取文件");
	const char *file = env->GetStringUTFChars(fileName, 0);

	FileOpear mFileOpear;
	const char* content = mFileOpear.read(file);
	LOGI("开始读取文件 完成");
	return env->NewStringUTF(content);

}



/*
 * Class:     com_brunjoy_jni_JNI
 * Method:    b
 * Signature: (DDII)Ljava/lang/String;
 */
/*JNIEXPORT jstring JNICALL Java_com_brunjoy_jni_JNI_b(JNIEnv * env, jclass obj,
 jdouble paramDouble1, jdouble paramDouble2, jint paramInt1,
 jint paramInt2) {

 }*/

#ifdef __cplusplus
}
#endif
#endif
