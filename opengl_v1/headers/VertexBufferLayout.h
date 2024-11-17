#pragma once
using namespace std;
#include "../dependencies/include/glew.h"
#include <vector>

struct VertexBufferElements {
	unsigned int type;
	int count;
	bool normalized;
};

class VertexBufferLayout {
private:
	vector<VertexBufferElements> m_elements;
	unsigned int m_stride;
public:
	VertexBufferLayout() :m_stride(0) {}
	
	template<typename T>
	void Push(int count) {
		static_assert(false);
	}

	template<>
	void Push<float>(int count) 
	{
		m_elements.push_back({GL_FLOAT,count,false });
		m_stride += sizeof(GLfloat);
	}

	template<>
	void Push<unsigned int>(int count) {
		m_elements.push_back({ GL_UNSIGNED_INT,count,false });
		m_stride += sizeof(GLuint);
	}

	template<>
	void Push<unsigned char>(int count) {
		m_elements.push_back({ GL_UNSIGNED_BYTE,count,false });
		m_stride += sizeof(GLbyte);
	}

	inline vector<VertexBufferElements> GetElements() const& { return m_elements; }
	inline unsigned int GetStride() const { return m_stride; }
};