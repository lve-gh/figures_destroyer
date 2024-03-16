#pragma once

#include <iostream>
#include <glad/glad.h>
#pragma once

#include <glad/glad.h>
#include <vector>
#include <memory>
#include <map>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <random>

#include "SimpleEngineCore/Rendering/OpenGL/ShaderProgram.hpp"
#include "SimpleEngineCore/Rendering/OpenGL/VertexBuffer.hpp"
#include "SimpleEngineCore/Rendering/OpenGL/VertexArray.hpp"
#include "SimpleEngineCore/Rendering/OpenGL/IndexBuffer.hpp"
#include "SimpleEngineCore/Figures.hpp"
#include "SimpleEngineCore/Window.hpp"

enum MENU {experience1 = 1, experience2, quit};

namespace SimpleEngine {
	std::vector<GLfloat> Interface();

	int Materials(int number);

	void ShowMaterials();

	int GetInt();
}