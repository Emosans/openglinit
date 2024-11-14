#include "../dependencies//include/glew.h"
#include "../dependencies/include/glfw3.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

// struct for shader
struct ShaderProgramSource {
    string VertexShaderSource;
    string FragmentShaderSource;
};

// read shaders from .shader file
static ShaderProgramSource ShaderSource(const string& filepath) {
    ifstream stream(filepath);

    // create an enum to store index
    enum ShaderType {
        NONE=-1, VERTEX=0, FRAGMENT=1
    };

    string line;
    ShaderType type = ShaderType::NONE;
    stringstream ss[2];

    while (getline(stream, line)) {
        if (line.find("#shader") != string::npos) {
            if (line.find("vertex") != string::npos) {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != string::npos) {
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            ss[int(type)] << line << "\n";
        }
    }
    return { ss[0].str(), ss[1].str() };
}

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

    // create a buffer
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer); // args - type of binding since triangle array contains the points of the vertices(positions)
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    // create a vertex attrib pointer
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    // create a shader (if user specific, create funciton above) 

    ShaderProgramSource source = ShaderSource("res/shaders/Basic.shader");

    unsigned int shaders = CreateShader(source.VertexShaderSource,source.FragmentShaderSource);
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