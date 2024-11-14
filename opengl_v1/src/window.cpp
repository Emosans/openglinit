#include "../dependencies//include/glew.h"
#include "../dependencies/include/glfw3.h"

#include <iostream>
using namespace std;

// compile shader
static unsigned int compileShader(unsigned int type, const string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // error handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = new char[length];
        glGetShaderInfoLog(id, length, &length, message);
        cout << "Failed to compile shader!" << endl;
        cout << message << endl;
        delete[] message;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

// create shader
static unsigned int CreateShader(const string& vertexshader, const string& fragmentshader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexshader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentshader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    // delete shaders
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // create array of positions
    float positions[6] = {
        -0.5f,-0.5f,
        0.0f,0.5f,
        0.5f,-0.5f
    };

    if (glewInit() != GLEW_OK) {
        cout << "Error";
    }
    cout << glGetString(GL_VERSION);

    // create a buffer
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer); // args - type of binding since triangle array contains the points of the vertices(positions)
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    // create a vertex attrib pointer
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    // create a shader (if user specific, create funciton above) 
    string vertexshader =
        "#version 330 core\n"
        "\n"
        "layout(location=0) in vec4 position;\n"
        "\n"
        "void main()\n"
        "{\n"
        "   gl_Position = position;\n"
        "}\n";

    string fragmentshader =
        "#version 330 core\n"
        "\n"
        "layout(location=0) out vec4 color;\n"
        "\n"
        "void main()\n"
        "{\n"
        "   color = vec4(1.0,0.0,0.0,1.0);\n"
        "}\n";

    unsigned int shaders = CreateShader(vertexshader, fragmentshader);
    glUseProgram(shaders);
    // vertex shader(repeated 3 times(since triangle) fragment shader(one or each pixel)
    // create a compile shader function(with type unsigned int) that creates the shader and returns the id of the shader

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        // draw arrays
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}