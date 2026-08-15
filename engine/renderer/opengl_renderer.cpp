#include "opengl_renderer.h"
#include <android/log.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define LOG_TAG "AniForge-Renderer"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

namespace aniforge {

const char* VERTEX_SHADER = R"glsl(
attribute vec3 aPosition;
attribute vec3 aColor;

varying vec3 vColor;

uniform mat4 uMVPMatrix;

void main() {
    gl_Position = uMVPMatrix * vec4(aPosition, 1.0);
    vColor = aColor;
}
)glsl";

const char* FRAGMENT_SHADER = R"glsl(
precision mediump float;

varying vec3 vColor;

void main() {
    gl_FragColor = vec4(vColor, 1.0);
}
)glsl";

OpenGLRenderer::OpenGLRenderer() 
    : eglDisplay(EGL_NO_DISPLAY), 
      eglContext(EGL_NO_CONTEXT), 
      eglSurface(EGL_NO_SURFACE),
      programHandle(0),
      VAO(0),
      VBO(0),
      initialized(false) {
}

OpenGLRenderer::~OpenGLRenderer() {
    cleanup();
}

bool OpenGLRenderer::init(ANativeWindow* window) {
    LOGI("Initializing OpenGL Renderer...");
    
    if (!setupEGL(window)) {
        LOGE("Failed to setup EGL");
        return false;
    }
    
    if (!setupShaders()) {
        LOGE("Failed to setup shaders");
        return false;
    }
    
    if (!setupBuffers()) {
        LOGE("Failed to setup buffers");
        return false;
    }
    
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    
    initialized = true;
    LOGI("OpenGL Renderer initialized successfully");
    return true;
}


bool OpenGLRenderer::setupEGL(ANativeWindow* window) {
    eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (eglDisplay == EGL_NO_DISPLAY) {
        LOGE("Failed to get EGL display");
        return false;
    }
    
    EGLint majorVersion, minorVersion;
    if (!eglInitialize(eglDisplay, &majorVersion, &minorVersion)) {
        LOGE("Failed to initialize EGL");
        return false;
    }
    
    LOGI("EGL Version: %d.%d", majorVersion, minorVersion);
    
    const EGLint attribs[] = {
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_BLUE_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_RED_SIZE, 8,
        EGL_DEPTH_SIZE, 24,
        EGL_NONE
    };
    
    EGLConfig config;
    EGLint numConfigs;
    if (!eglChooseConfig(eglDisplay, attribs, &config, 1, &numConfigs)) {
        LOGE("Failed to choose EGL config");
        return false;
    }
    
    const EGLint contextAttribs[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };
    
    eglContext = eglCreateContext(eglDisplay, config, EGL_NO_CONTEXT, contextAttribs);
    if (eglContext == EGL_NO_CONTEXT) {
        LOGE("Failed to create EGL context");
        return false;
    }
    
    eglSurface = eglCreateWindowSurface(eglDisplay, config, window, NULL);
    if (eglSurface == EGL_NO_SURFACE) {
        LOGE("Failed to create EGL surface");
        return false;
    }
    
    if (!eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext)) {
        LOGE("Failed to make EGL current");
        return false;
    }
    
    eglSwapInterval(eglDisplay, 1);
    return true;
}


bool OpenGLRenderer::setupShaders() {
    // Compile vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &VERTEX_SHADER, NULL);
    glCompileShader(vertexShader);
    
    GLint compiled = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        LOGE("Vertex shader compilation failed");
        char log[1024];
        glGetShaderInfoLog(vertexShader, sizeof(log), NULL, log);
        LOGE("Shader log: %s", log);
        return false;
    }
    
    // Compile fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &FRAGMENT_SHADER, NULL);
    glCompileShader(fragmentShader);
    
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        LOGE("Fragment shader compilation failed");
        char log[1024];
        glGetShaderInfoLog(fragmentShader, sizeof(log), NULL, log);
        LOGE("Shader log: %s", log);
        return false;
    }
    
    // Link program
    programHandle = glCreateProgram();
    glAttachShader(programHandle, vertexShader);
    glAttachShader(programHandle, fragmentShader);
    glLinkProgram(programHandle);
    
    GLint linked = 0;
    glGetProgramiv(programHandle, GL_LINK_STATUS, &linked);
    if (!linked) {
        LOGE("Program linking failed");
        char log[1024];
        glGetProgramInfoLog(programHandle, sizeof(log), NULL, log);
        LOGE("Program log: %s", log);
        return false;
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    return true;
}


bool OpenGLRenderer::setupBuffers() {
    // Triangle vertices
    float vertices[] = {
        // Position          Color
        0.0f, 0.5f, 0.0f,    1.0f, 0.0f, 0.0f,  // Top (Red)
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // Bottom Left (Green)
        0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f   // Bottom Right (Blue)
    };
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // Position attribute
    GLint posLocation = glGetAttribLocation(programHandle, "aPosition");
    glEnableVertexAttribArray(posLocation);
    glVertexAttribPointer(posLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    
    // Color attribute
    GLint colorLocation = glGetAttribLocation(programHandle, "aColor");
    glEnableVertexAttribArray(colorLocation);
    glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 
                         (void*)(3 * sizeof(float)));
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    return true;
}


void OpenGLRenderer::render() {
    if (!initialized) return;
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glUseProgram(programHandle);
    
    // Setup MVP matrix
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 mvp = projection * view * model;
    
    GLint mvpLocation = glGetUniformLocation(programHandle, "uMVPMatrix");
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(mvp));
    
    // Draw triangle
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    eglSwapBuffers(eglDisplay, eglSurface);
}

void OpenGLRenderer::cleanup() {
    LOGI("Cleaning up OpenGL Renderer");
    cleanupEGL();
    initialized = false;
}

void OpenGLRenderer::cleanupEGL() {
    if (eglDisplay != EGL_NO_DISPLAY) {
        eglMakeCurrent(eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (eglContext != EGL_NO_CONTEXT) {
            eglDestroyContext(eglDisplay, eglContext);
        }
        if (eglSurface != EGL_NO_SURFACE) {
            eglDestroySurface(eglDisplay, eglSurface);
        }
        eglTerminate(eglDisplay);
    }
}

}
