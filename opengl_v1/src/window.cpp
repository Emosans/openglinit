#include "../dependencies//include/glew.h"
#include "../dependencies/include/glfw3.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
using namespace std;

// create a cirlce
static vector<float> generatePointsForCircle(float centerX, float centerY, float radius, int numberofsegments,float offsetX,float offsetY) {
    vector<float> vertices;

    for (int i = 0; i <= numberofsegments; ++i) {
        float angle = 2.0f * 3.14f * i / numberofsegments;

        float x = centerX + offsetX + radius * cos(angle);
        float y = centerY + offsetY + radius * sin(angle);

        vertices.push_back(x);
        vertices.push_back(y);
    }
    return vertices;
}


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
    float time = 0.0f;
    
    
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

        float offsetX = 0.3f * cos(time);
        float offsetY = 0.3f * sin(time);

        vector<float> circle = generatePointsForCircle(0, 0, 0.5, 50, offsetX, offsetY);
        glBufferData(GL_ARRAY_BUFFER, circle.size() * sizeof(float), circle.data(), GL_STATIC_DRAW);

        // draw arrays
        glDrawArrays(GL_TRIANGLE_FAN, 0, circle.size()/2);

        glfwSwapBuffers(window);

        glfwPollEvents();

        time += 0.01f;
    }
    glDeleteProgram(shaders);
    glfwTerminate();
    return 0;
}