#pragma once
#include "../dependencies/include/glew.h";
#include "../headers/VertexBuffer.h"
#include "../headers/VertexBufferLayout.h"

class VertexArray {
private:
	unsigned int m_vertexarrayid;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void Bind() const;
	void Unbind() const;
};