#pragma once
#include<string>
using namespace std;
#include "../dependencies/include/glew.h"

class Texture {
private:
	unsigned int texture_id;
	string file_location;
	unsigned char* m_localBuffer;
	int m_width, m_height,m_BPP;
public:
	Texture(const string& filepath);
	~Texture();

	void Bind(unsigned int slot=0) const;
	void Unbind() const;

	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }
};