#include<fstream>
#include <sstream>

#include "../headers/Renderer.h"
#include "../headers/Shader.h"

Shader::Shader(const string& filepath) :filepath(filepath), shader_id(0) {
    ShaderProgramSource source = ShaderSource(filepath);
    shader_id = CreateShader(source.VertexShader, source.FragmentShader);
}
Shader::~Shader() {

}
ShaderProgramSource Shader::ShaderSource(const string& filepath) {
    ifstream stream(filepath);

    // create an enum to store index
    enum ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
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

unsigned int Shader::CompileShader(unsigned int type, const string& source) {
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

unsigned int Shader::CreateShader(const string& vertexshader, const string& fragmentshader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexshader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentshader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    // delete shaders
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

void Shader::Bind() const {
    GLCall(glUseProgram(shader_id));
}

void Shader::Unbind() const {
    GLCall(glUseProgram(0));
}

void Shader::setUniform4f(const string& name, float v1, float v2, float v3, float v4) {
    GLCall(glUniform4f(GetUniformLocation(name), v1, v2, v3, v4));
}

int Shader::GetUniformLocation(const string& name) {
    GLCall(int location = glGetUniformLocation(shader_id, name.c_str()));
    if (location == -1) {
        cout << "Error";
    }
    return location;
}