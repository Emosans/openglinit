#include "../headers/VertexBuffer.h";
#include "../dependencies/include/glew.h";
#include "../headers/Renderer.h";

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
	GLCall(glGenBuffers(1, &m_bufferId));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_bufferId));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}
VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &m_bufferId);
}
void VertexBuffer::Bind() const{
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferId);
}
void VertexBuffer::UnBind() const{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}