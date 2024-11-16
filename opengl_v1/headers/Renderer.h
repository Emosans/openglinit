#pragma once
#include <iostream>
#include "../dependencies/include/glew.h";
using namespace std;

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearErrors();\
	x;\
	ASSERT(GLLogCall())

void GLClearErrors();
bool GLLogCall();