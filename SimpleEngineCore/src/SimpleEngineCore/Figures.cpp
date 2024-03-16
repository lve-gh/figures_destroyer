#include "SimpleEngineCore/Figures.hpp"

namespace SimpleEngine {

    BufferLayout buffer_layout_1vec3
    {
        ShaderDataType::Float3
    };


    BufferLayout buffer_layout_2vec3
    {
        ShaderDataType::Float3,
        ShaderDataType::Float3
    };

    void CreateFigure(std::vector<GLfloat>& m_pos_colors, std::vector<GLuint>& m_indices, std::vector<std::vector<GLfloat>>& figures_pos_colors, std::vector<std::vector<GLuint>>& figures_indices, std::vector<std::shared_ptr<ShaderProgram>>& p_shader_program, std::vector<std::shared_ptr<VertexBuffer>>& p_positions_colors_vbo, std::vector<std::shared_ptr<IndexBuffer>>& p_index_buffer, std::vector<std::shared_ptr<VertexArray>>& p_vao, const char*& vertex_shader, const char*& fragment_shader) {
 
        p_shader_program.push_back(std::make_unique<ShaderProgram>(vertex_shader, fragment_shader));

        figures_pos_colors.push_back(m_pos_colors);

        figures_indices.push_back(m_indices);

        p_vao.push_back(std::make_unique<VertexArray>());

        p_positions_colors_vbo.push_back(std::make_unique<VertexBuffer>(std::data(m_pos_colors), m_pos_colors.size() * 4, buffer_layout_2vec3));

        p_index_buffer.push_back(std::make_unique<IndexBuffer>(std::data(m_indices), m_indices.size()));


        p_vao[p_vao.size() - 1]->add_vertex_buffer(*p_positions_colors_vbo[p_positions_colors_vbo.size() - 1]);
        p_vao[p_vao.size() - 1]->set_index_buffer(*p_index_buffer[p_index_buffer.size() - 1]);

    }

    void MoveFigure(int coord1, int coord2, GLfloat speed, int ind, std::vector<std::vector<GLfloat>>& figures_pos_colors, std::vector<std::vector<GLuint>>& figures_indices, std::vector<std::shared_ptr<ShaderProgram>>& p_shader_program, std::vector<std::shared_ptr<VertexBuffer>>& p_positions_colors_vbo, std::vector<std::shared_ptr<IndexBuffer>>& p_index_buffer, std::vector<std::shared_ptr<VertexArray>>& p_vao, const char*& vertex_shader, const char*& fragment_shader) {

        p_shader_program[ind] = std::make_unique<ShaderProgram>(vertex_shader, fragment_shader);

        for (int i = 0; i < figures_pos_colors[ind].size(); i += 6) {
            if (coord1 >= 0)
            figures_pos_colors[ind][coord1 + i] += speed;
            if (coord2 >= 0)
            figures_pos_colors[ind][coord2 + i] += speed;
        }

        p_vao[ind] = std::make_unique<VertexArray>();

        p_positions_colors_vbo[ind] = std::make_unique<VertexBuffer>(std::data(figures_pos_colors[ind]), figures_pos_colors[ind].size() * 4, buffer_layout_2vec3);
        p_index_buffer[ind] = std::make_unique<IndexBuffer>(std::data(figures_indices[ind]), figures_indices[ind].size());
        p_vao[ind]->add_vertex_buffer(*p_positions_colors_vbo[ind]);
        p_vao[ind]->set_index_buffer(*p_index_buffer[ind]);
    }
    void DestroyFigure(int coordNumber, int fgn, std::vector<std::vector<GLfloat>>& figures_pos_colors, std::vector<std::vector<GLuint>>& figures_indices, std::vector<std::shared_ptr<ShaderProgram>>& p_shader_program, std::vector<std::shared_ptr<VertexBuffer>>& p_positions_colors_vbo, std::vector<std::shared_ptr<IndexBuffer>>& p_index_buffer, std::vector<std::shared_ptr<VertexArray>>& p_vao, const char*& vertex_shader, const char*& fragment_shader) {
        srand(static_cast<unsigned>(time(0)));
        using std::cout;
        using std::endl;
        GLfloat min = figures_pos_colors[fgn][coordNumber];
        GLfloat max = figures_pos_colors[fgn][coordNumber];
        int size = static_cast<int>(figures_pos_colors[fgn].size());
        for (int i = coordNumber; i < size; i += 6) {

            if (figures_pos_colors[fgn][i] > max)
                max = figures_pos_colors[fgn][i];
            if (figures_pos_colors[fgn][i] < min)
                min = figures_pos_colors[fgn][i];
        }
        std::vector<GLfloat> random_coords;
        GLfloat randomCoord = 0.f;
        for (int i = 0; i < 4; i++) {
            randomCoord = min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
            random_coords.push_back(randomCoord);
        }
        
        std::vector<GLfloat> newFigure_pos_colors;
        std::vector<GLfloat> newFigure_pos_colors2;
        switch (coordNumber)
        {
        case 0:
            for (int i = 0; i < 48; i++) {
                if (i == 0)
                    newFigure_pos_colors.push_back(random_coords[0]);
                else if (i == 18)
                    newFigure_pos_colors.push_back(random_coords[1]);
                else if (i == 24)
                    newFigure_pos_colors.push_back(random_coords[2]);
                else if (i == 42)
                    newFigure_pos_colors.push_back(random_coords[3]);
                else 
                    newFigure_pos_colors.push_back(figures_pos_colors[fgn][i]);

                if (i == 6)
                    newFigure_pos_colors2.push_back(random_coords[0]);
                else if (i == 12)
                    newFigure_pos_colors2.push_back(random_coords[1]);
                else if (i == 30)
                    newFigure_pos_colors2.push_back(random_coords[2]);
                else if (i == 36)
                    newFigure_pos_colors2.push_back(random_coords[3]);
                else
                    newFigure_pos_colors2.push_back(figures_pos_colors[fgn][i]);
            }
            break;
        case 1:
            for (int i = 0; i < 48; i++) {
                if (i == 1)
                    newFigure_pos_colors.push_back(random_coords[0]);
                else if (i == 19)
                    newFigure_pos_colors.push_back(random_coords[1]);
                else if (i == 25)
                    newFigure_pos_colors.push_back(random_coords[2]);
                else if (i == 43)
                    newFigure_pos_colors.push_back(random_coords[3]);
                else
                    newFigure_pos_colors.push_back(figures_pos_colors[fgn][i]);

                if (i == 7)
                    newFigure_pos_colors2.push_back(random_coords[0]);
                else if (i == 13)
                    newFigure_pos_colors2.push_back(random_coords[1]);
                else if (i == 31)
                    newFigure_pos_colors2.push_back(random_coords[2]);
                else if (i == 37)
                    newFigure_pos_colors2.push_back(random_coords[3]);
                else
                    newFigure_pos_colors2.push_back(figures_pos_colors[fgn][i]);
            }
            break;
        case 2:
            for (int i = 0; i < 48; i++) {
                if (i == 2)
                    newFigure_pos_colors.push_back(random_coords[0]);
                else if (i == 20)
                    newFigure_pos_colors.push_back(random_coords[1]);
                else if (i == 26)
                    newFigure_pos_colors.push_back(random_coords[2]);
                else if (i == 44)
                    newFigure_pos_colors.push_back(random_coords[3]);
                else
                    newFigure_pos_colors.push_back(figures_pos_colors[fgn][i]);

                if (i == 7)
                    newFigure_pos_colors2.push_back(random_coords[0]);
                else if (i == 14)
                    newFigure_pos_colors2.push_back(random_coords[1]);
                else if (i == 32)
                    newFigure_pos_colors2.push_back(random_coords[2]);
                else if (i == 38)
                    newFigure_pos_colors2.push_back(random_coords[3]);
                else
                    newFigure_pos_colors2.push_back(figures_pos_colors[fgn][i]);
            }
            break;
        default:
            break;
        }
        std::vector<GLuint> indicesFunc = {
            0, 1, 2,
            0, 2, 3,
            2, 1, 5,
            2, 5, 6,
            3, 2, 6,
            3, 6, 7,
            0, 3, 7,
            0, 7, 4,
            1, 0, 4,
            1, 4, 5,
            6, 5, 4,
            6, 4, 7
        };
        figures_pos_colors[fgn].clear();
        figures_indices[fgn].clear();
        SimpleEngine::CreateFigure(newFigure_pos_colors, indicesFunc, figures_pos_colors, figures_indices, p_shader_program, p_positions_colors_vbo, p_index_buffer, p_vao, vertex_shader, fragment_shader);
        SimpleEngine::CreateFigure(newFigure_pos_colors2, indicesFunc, figures_pos_colors, figures_indices, p_shader_program, p_positions_colors_vbo, p_index_buffer, p_vao, vertex_shader, fragment_shader);
        newFigure_pos_colors.clear();
        newFigure_pos_colors2.clear();
    }
}