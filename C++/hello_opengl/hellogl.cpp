#include "hellogl.h"

// 创建VAO,VBO对象
GLuint vao, vbo;

// 顶点数据
GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f
};

GLuint shaderProgram;

// Shader源码
const GLchar* vertexShaderSource
    = "#version 330 core\n"
      "layout (location = 0) in vec3 pos;\n"
      "void main(void) { gl_Position = vec4(pos.x, pos.y, pos.z, 1.0); }\n\0";

const GLchar* fragmentShaderSource
    = "#version 330 core\n"
      "out vec4 fragColor;\n"
      "void main(void) { fragColor = vec4(144.0f/255, 230.0f/255, 252.0f/255, 1.0f); }\n\0";

HelloGL::HelloGL(QWidget* parent)
    : QOpenGLWidget(parent)
{
}

void HelloGL::initializeGL()
{
    // 找到本地的函数，初始化函数指针
    initializeOpenGLFunctions();

    // VAO,VBO对象绑定ID
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    // 绑定VAO,VBO对象
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // 在显存内创建GL_ARRAY_BUFFER的data区，并用vertices的数据初始化之
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 告知显卡如何解释缓冲区里的数据
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

    // 开启VAO管理的第一个属性
    glEnableVertexAttribArray(0);

    // 释放两个对象
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // 创建两个Shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // 链接两个Shader
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // 删除两个不用的Shader
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void HelloGL::paintGL()
{
    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
