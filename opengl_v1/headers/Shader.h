#pragma once
#include <string>
#include <iostream>
using namespace std;

#include "../headers/VertexBuffer.h"

struct ShaderProgramSource {
	string VertexShader;
	string FragmentShader;
};

class Shader {
private:
	unsigned int shader_id;
	const string& filepath;
public:
	Shader(const string& filepath);
	~Shader();
	void setUniform4f(const string& name,float v1,float v2,float v3,float v4);
	void Bind() const;
	void Unbind() const;
private:
	unsigned int CompileShader(unsigned int type, const string& source);
	ShaderProgramSource ShaderSource(const string& filepath);
	unsigned int CreateShader(const string& vertexShader, const string& fragmentShader);
	int GetUniformLocation(const string& name);
};