import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.List;

public class FasmWrapper {
    private static final int DEFAULT_MEMORY_SIZE = 65536;
    private static final int DEFAULT_PASS_LIMIT = 100;

    private static native int fasmAssemble(byte[] source, ByteBuffer memoryBuffer, int memorySize, int passesLimit);

    static {
        System.loadLibrary("fasmwrapper");
    }

    private StringBuilder assemblyString;
    private List<Thread> threadHandles;
    private int memorySize;
    private int passLimit;

    public FasmWrapper() {
        assemblyString = new StringBuilder("use32\n");
        threadHandles = new ArrayList<>();
        memorySize = DEFAULT_MEMORY_SIZE;
        passLimit = DEFAULT_PASS_LIMIT;
    }

    public void addLine(String line) {
        assemblyString.append(line).append("\n");
    }

    public void add(String line) {
        assemblyString.append(line);
    }

    public void clear() {
        assemblyString = new StringBuilder("use32\n");
    }

    public byte[] assemble() {
        return assemble(assemblyString.toString(), memorySize, passLimit);
    }

    public static byte[] assemble(String source) {
        return assemble(source, DEFAULT_MEMORY_SIZE, DEFAULT_PASS_LIMIT);
    }

    public static byte[] assemble(String source, int memorySize, int passLimit) {
        ByteBuffer memoryBuffer = ByteBuffer.allocateDirect(memorySize);
        byte[] sourceBytes = source.getBytes(StandardCharsets.UTF_8);
        int result = fasmAssemble(sourceBytes, memoryBuffer, memorySize, passLimit);

        if (result != 0) {
            throw new RuntimeException("Assembly failed! Error code: " + result);
        }

        byte[] bytecode = new byte[memoryBuffer.remaining()];
        memoryBuffer.get(bytecode);
        return bytecode;
    }
}

#include <jni.h>
#include "FasmWrapper.h"
#include "fasm.h"

extern "C" JNIEXPORT jint JNICALL Java_FasmWrapper_fasmAssemble(JNIEnv *env, jclass, jbyteArray source, jobject memoryBuffer, jint memorySize, jint passesLimit) {
    jbyte *sourceBytes = env->GetByteArrayElements(source, nullptr);
    int sourceLength = env->GetArrayLength(source);
    void *memoryPtr = env->GetDirectBufferAddress(memoryBuffer);

    int result = fasm_Assemble(reinterpret_cast<char *>(sourceBytes), memoryPtr, memorySize, passesLimit);

    env->ReleaseByteArrayElements(source, sourceBytes, JNI_ABORT);

    return result;
}
