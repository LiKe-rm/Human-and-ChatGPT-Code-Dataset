#include <jni.h>
#include <android/log.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

// 定义日志标签
#define LOG_TAG "dyn"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

// 将 Lua 数据类型转换为 JNI 数据类型的辅助函数
jvalue lua_to_jvalue(JNIEnv *env, lua_State *L, int index, jclass clazz);

// JNI 方法包装器
int l_call_object_method(lua_State *L);

// 初始化 Lua 扩展库
int luaopen_dyn(lua_State *L);

// Lua 函数映射表
static const luaL_Reg dyn_lib[] ={
    {"call_object_method", l_call_object_method},
    {NULL, NULL}
};

// 将 Lua 数据类型转换为 JNI 数据类型的辅助函数实现
jvalue lua_to_jvalue(JNIEnv *env, lua_State *L, int index, jclass clazz) {
    jvalue jval;
    if (env->IsAssignableFrom(clazz, env->FindClass("java/lang/String"))) {
        const char *str = luaL_checkstring(L, index);
        jval.l = env->NewStringUTF(str);
    } else {
        // 其他类型转换可以在这里添加
    }
    return jval;
}

// JNI 方法包装器实现
int l_call_object_method(lua_State *L) {
    JNIEnv *env;
    JavaVM *jvm;
    jobject obj;
    jmethodID mid;
    jclass clazz;
    const char *name;
    const char *signature;
    int nargs;
    jvalue *args;
    jobject result;
    const char *result_str;
    int i;

    // 获取 JNI 环境和 JavaVM 实例
    // (请确保已初始化 JNI，并将 JNI 环境和 JavaVM 实例传入全局变量)
    env = ...;
    jvm = ...;

    // 获取参数
    obj = (jobject)lua_touserdata(L, 1);
    name = luaL_checkstring(L, 2);
    signature = luaL_checkstring(L, 3);

    // 获取方法 ID
    clazz = env->GetObjectClass(obj);
    mid = env->GetMethodID(clazz, name, signature);

    // 准备参数数组
    nargs = lua_gettop(L) - 3;
    args = new jvalue[nargs];
    for (i = 0; i < nargs; i++) {
        args[i] = lua_to_jvalue(env, L, i + 4, clazz);
    }

    // 调用方法
    result = env->CallObjectMethodA(obj, mid, args);

    // 处理返回值
    if (env->IsInstanceOf(result, env->FindClass("java/lang/String"))) {
        result_str = env->GetStringUTFChars((jstring)result, NULL);
        lua_pushstring(L, result_str);
        env->ReleaseStringUTFChars((jstring)result, result_str);
    } else {
        // 处理其他类型的返回值
    }

    // 释放资源
    delete[] args;
    return 1;
}

// 初始化 Lua 扩展库实现
int luaopen_dyn(lua_State *L) {
    luaL_newlib(L, dyn_lib);
    return 1;
}

