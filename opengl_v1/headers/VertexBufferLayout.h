#pragma once
using namespace std;
#include "../dependencies/include/glew.h"
#include "../headers/Renderer.h"
#include <vector>

struct VertexBufferElements {
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetType(unsigned int type) {
		switch (type)
		{
			case GL_FLOAT:			return 4;
			case GL_UNSIGNED_INT:   return 4;
			case GL_UNSIGNED_BYTE:  return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout {
private:
	vector<VertexBufferElements> m_elements;
	unsigned int m_stride;
public:
	VertexBufferLayout() :m_stride(0) {}
	
	template<typename T>
	void Push(unsigned int count) {
		//static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count) 
	{
		m_elements.push_back({GL_FLOAT,count,GL_FALSE });
		m_stride += count*VertexBufferElements::GetType(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>(unsigned int count) {
		m_elements.push_back({ GL_UNSIGNED_INT,count,GL_FALSE });
		m_stride += count*VertexBufferElements::GetType(GL_UNSIGNED_INT);
	}

	template<>
	void Push<unsigned char>(unsigned int count) {
		m_elements.push_back({ GL_UNSIGNED_BYTE,count,GL_TRUE });
		m_stride += count*VertexBufferElements::GetType(GL_UNSIGNED_BYTE);
	}

	inline vector<VertexBufferElements> GetElements() const& { return m_elements; }
	inline unsigned int GetStride() const { return m_stride; }
};