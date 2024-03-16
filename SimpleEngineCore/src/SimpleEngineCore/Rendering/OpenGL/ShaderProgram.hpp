#pragma once

#include <glm/mat4x4.hpp>

namespace SimpleEngine {

    class ShaderProgram
    {
    public:
        ShaderProgram(const char* vertex_shader_src, const char* fragment_shader_src);
        ShaderProgram(ShaderProgram&&);
        ShaderProgram& operator=(ShaderProgram&&);
        ~ShaderProgram();

        //ShaderProgram() = delete;
        //ShaderProgram(const ShaderProgram&) = delete;
        //ShaderProgram& operator=(const ShaderProgram&) = delete;

        void bind() const;
        static void unbind();
        bool isCompiled() const { return m_is_compiled; }
        void setMatrix4(const char* name, const glm::mat4& matrix) const;

    private:
        unsigned int m_id = 0;
        bool m_is_compiled = false;
    };
    char* GetVertexShader();
    char* GetFragmentShader();
}
