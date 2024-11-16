#include "../headers/Renderer.h";

void GLClearErrors() {
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall() {
	while (GLenum error = glGetError()) {
		cout << error << endl;
		return false;
	}
	return true;
}