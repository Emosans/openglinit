#pragma once
#include "../dependencies/include/glew.h";
#include "../headers/VertexBuffer.h"
#include "../headers/VertexBufferLayout.h"

class VertexArray {
private:

public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
};