#include "../headers/Renderer.h"
#include "../headers/VertexArray.h"

VertexArray::VertexArray() {
	GLCall(glGenVertexArrays(1, &m_vertexarrayid));
	GLCall(glBindVertexArray(m_vertexarrayid));
}

VertexArray::~VertexArray() {
	GLCall(glDeleteVertexArrays(1, &m_vertexarrayid));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
	vb.Bind();

	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (int i = 0; i < elements.size(); ++i) {
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		// index,count,type,normalized,stride,offset
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
		offset += element.count * VertexBufferElements::GetType(element.type);
	}
}

void VertexArray::Bind() const {
	GLCall(glBindVertexArray(m_vertexarrayid));
}

void VertexArray::Unbind() const {
	GLCall(glBindVertexArray(0));
}