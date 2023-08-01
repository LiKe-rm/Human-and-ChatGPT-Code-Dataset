import static com.googlecode.javacpp.Loader.sizeof;
import com.googlecode.javacpp.annotation.Cast;
import com.googlecode.javacpp.annotation.Name;
import com.googlecode.javacpp.annotation.Platform;
import com.googlecode.javacpp.annotation.Properties;

import java.nio.IntBuffer;
import java.util.ArrayList;
import java.util.List;

import static org.lwjgl.egl.EGL.*;
import static org.lwjgl.egl.EGL10.*;
import static org.lwjgl.egl.EGL12.*;
import static org.lwjgl.egl.EGL14.*;
import static org.lwjgl.system.MemoryUtil.*;
import static org.lwjgl.system.MemoryStack.*;

import org.lwjgl.PointerBuffer;
import org.lwjgl.system.MemoryStack;
import org.lwjgl.system.Platform;

@Properties(inherit = org.bytedeco.javacpp.presets.egl.class, value = {
        @Platform(include = "<EGL/egl.h>"),
        @Platform(value = "android", link = "EGL")
})
public class EglJava {

    static class Egl {
        static long eglInitialize(long display, IntBuffer major, IntBuffer minor) {
            return eglInitialize(display, major, minor);
        }

        static long eglGetConfigs(long display, PointerBuffer configs, int configSize, IntBuffer numConfig) {
            return eglGetConfigs(display, configs, configSize, numConfig);
        }

        static long eglChooseConfig(long display, IntBuffer attribList, PointerBuffer configs, int configSize,
                                     IntBuffer numConfig) {
            return eglChooseConfig(display, attribList, configs, configSize, numConfig);
        }

        static long eglGetConfigAttrib(long display, long config, int attribute, IntBuffer value) {
            return eglGetConfigAttrib(display, config, attribute, value);
        }

        static long eglCreateWindowSurface(long display, long config, long nativeWindow, IntBuffer attribList) {
            return eglCreateWindowSurface(display, config, nativeWindow, attribList);
        }

        static long eglCreatePbufferSurface(long display, long config, IntBuffer attribList) {
            return eglCreatePbufferSurface(display, config, attribList);
        }

        static long eglCreatePbufferFromClientBuffer(long display, int buftype, long buffer, long config,
                                                     IntBuffer attribList) {
            return eglCreatePbufferFromClientBuffer(display, buftype, buffer, config, attribList);
        }

        static long eglCreatePixmapSurface(long display, long config, long nativePixmap, IntBuffer attribList) {
            return eglCreatePixmapSurface(display, config, nativePixmap, attribList);
        }

        static long eglQuerySurface(long display, long surface, int attribute, IntBuffer value) {
            return eglQuerySurface(display, surface, attribute, value);
        }

        static long eglCreateContext(long display, long config, long shareContext, IntBuffer attribList) {
            return eglCreateContext(display, config, shareContext, attribList);
        }

        static long eglQueryContext(long display, long context, int attribute, IntBuffer value) {
            return eglQueryContext(display, context, attribute, value);
        }
    }
}
