#include "Enables.hpp"

void Enables() {
	glEnable(GL_DEPTH_TEST);
	glEnable(0x0B50); // GL_LIGHTING
	glEnable(0x4000); // GL_LIGHT0
	glEnable(0x0B57); // GL_COLOR_MATERIAL
	//GL_LIGHTING
}	