#ifndef ANIFORGE_OPENGL_RENDERER_H
#define ANIFORGE_OPENGL_RENDERER_H

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <android/native_window.h>

namespace aniforge {

class OpenGLRenderer {
private:
    EGLDisplay eglDisplay;
    EGLContext eglContext;
    EGLSurface eglSurface;
    
    GLuint programHandle;
    GLuint VAO, VBO;
    
    bool initialized;

public:
    OpenGLRenderer();
    ~OpenGLRenderer();
    
    bool init(ANativeWindow* window);
    void render();
    void cleanup();
    
    bool isInitialized() const { return initialized; }

private:
    bool setupEGL(ANativeWindow* window);
    bool setupShaders();
    bool setupBuffers();
    void cleanupEGL();
};

}

#endif
