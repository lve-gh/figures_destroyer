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
#include "SimpleEngineCore/Window.hpp"


namespace SimpleEngine {
	void CreateFigure(std::vector<GLfloat>& m_pos_colors, std::vector<GLuint>& m_indices, std::vector<std::vector<GLfloat>>& figures_pos_colors, std::vector<std::vector<GLuint>>& figures_indices, std::vector<std::shared_ptr<ShaderProgram>>& p_shader_program, std::vector<std::shared_ptr<VertexBuffer>>& p_positions_colors_vbo, std::vector<std::shared_ptr<IndexBuffer>>& p_index_buffer, std::vector<std::shared_ptr<VertexArray>>& p_vao, const char*& vertex_shader, const char*& fragment_shader);
	void MoveFigure(int coord1, int coord2, GLfloat speed, int ind, std::vector<std::vector<GLfloat>>& figures_pos_colors, std::vector<std::vector<GLuint>>& figures_indices, std::vector<std::shared_ptr<ShaderProgram>>& p_shader_program, std::vector<std::shared_ptr<VertexBuffer>>& p_positions_colors_vbo, std::vector<std::shared_ptr<IndexBuffer>>& p_index_buffer, std::vector<std::shared_ptr<VertexArray>>& p_vao, const char*& vertex_shader, const char*& fragment_shader);
	void DestroyFigure(int coordNumber, int fgn, std::vector<std::vector<GLfloat>>& figures_pos_colors, std::vector<std::vector<GLuint>>& figures_indices, std::vector<std::shared_ptr<ShaderProgram>>& p_shader_program, std::vector<std::shared_ptr<VertexBuffer>>& p_positions_colors_vbo, std::vector<std::shared_ptr<IndexBuffer>>& p_index_buffer, std::vector<std::shared_ptr<VertexArray>>& p_vao, const char*& vertex_shader, const char*& fragment_shader);
}

