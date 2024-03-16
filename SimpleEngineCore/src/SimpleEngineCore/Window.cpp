#include "SimpleEngineCore/Window.hpp"
#include "SimpleEngineCore/Log.hpp"
#include "SimpleEngineCore/Rendering/OpenGL/ShaderProgram.hpp"
#include "SimpleEngineCore/Rendering/OpenGL/VertexBuffer.hpp"
#include "SimpleEngineCore/Rendering/OpenGL/VertexArray.hpp"
#include "SimpleEngineCore/Rendering/OpenGL/IndexBuffer.hpp"
#include "SimpleEngineCore/Camera.hpp"
#include "SimpleEngineCore/Application.hpp"
#include "SimpleEngineCore/Figures.hpp"
#include <SimpleEngineCore/Interface.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>

#include <glm/mat3x3.hpp>
#include <glm/trigonometric.hpp>


#include <iostream>

enum STATUS { created = 1, moving, colided, broken, };
enum STATUS2 {whole = 1, blowned};

namespace SimpleEngine {
    using std::vector;
    using std::cout;
    using std::cin;
    using std::endl;
    //using std::data;
    static bool s_GLFW_initialized = false;
    vector<GLfloat> positions_colors = {
           -0.5f,  0.5f, 0.0f,   0.7f, 0.0f, 0.0f,
            0.5f,  0.5f, 0.0f,   0.7f, 0.0f, 0.0f,
            0.5f,  -0.5f, 0.0f,   0.7f, 0.0f, 0.0f,
           -0.5f,  -0.5f, 0.0f,   0.5f, 0.0f, 0.0f,
           -0.5f,  0.5f, 0.6f,   1.0f, 0.0f, 0.0f,
            0.5f,  0.5f, 0.6f,   0.7f, 0.0f, 0.0f,
            0.5f,  -0.5f, 0.6f,   0.7f, 0.0f, 0.0f,
           -0.5f,  -0.5f, 0.6f,   0.7f, 0.0f, 0.0f
    };

    vector<GLfloat> positions_colors2 = {
       -0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 0.7f,
        0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 0.7f,
        0.5f,  -0.5f, 0.0f,   0.0f, 0.0f, 0.7f,
       -0.5f,  -0.5f, 0.0f,   0.0f, 0.0f, 0.5f,
       -0.5f,  0.5f, 0.6f,   0.0f, 0.0f, 1.0f,
        0.5f,  0.5f, 0.6f,   0.0f, 0.0f, 0.7f,
        0.5f,  -0.5f, 0.6f,   0.0f, 0.0f, 0.7f,
       -0.5f,  -0.5f, 0.6f,   0.0f, 0.0f, 0.7f
    };

    vector<GLuint> indices = { 
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

    vector<vector<GLfloat>> figures_pos_colors;
    vector<vector<GLuint>> figures_indices;
    const char* vertex_shader =
        R"(#version 100
		   #extension GL_ARB_explicit_attrib_location : enable
		   #extension GL_NV_explicit_attrib_location : enable
           layout(location = 0) in vec3 vertex_position;
           layout(location = 1) in vec3 vertex_color;
           uniform mat4 model_matrix;
           uniform mat4 view_projection_matrix;
           varying out vec3 color;
           void main() {
              color = vertex_color;
              gl_Position = view_projection_matrix * model_matrix * vec4(vertex_position, 1.0);
           }
        )";

    const char* fragment_shader =
        R"(#version 100
		   #extension GL_ARB_explicit_attrib_location : enable
		   #extension GL_NV_explicit_attrib_location : enable
		   precision mediump float;
           in vec3 color;
           varying out vec4 frag_color;
           void main() {
              frag_color = vec4(color, 1.0);
           }
        )";
    
    vector<std::shared_ptr<ShaderProgram>> p_shader_program;
    vector<std::shared_ptr<VertexBuffer>> p_positions_colors_vbo;
    vector<std::shared_ptr<IndexBuffer>> p_index_buffer;
    vector<std::shared_ptr<VertexArray>> p_vao;
    vector<GLfloat> experienceData;
    vector<int> moveCoords1;
    vector<int> moveCoords2;
    float scale[3] = { 1.f, 1.f, 1.f };
    float rotate = 0.f;
    float translate[3] = { 0.f, 0.f, 0.f };

    float camera_position[3] = { 0.f, 0.f, 4.f };
    float camera_rotation[3] = { 0.f, 0.f, 0.f };
    bool perspective_camera = true;
    bool end_experiment = false;
    int experimentStatus = created;
    int experimentStatus2 = whole;
    int size = 0;
    int backSpeed[2];

    GLfloat rr;
    GLfloat hh;
    GLfloat ff;

    int nn = 0;
    Camera camera;

    Window::Window(std::string title, const unsigned int width, const unsigned int height)
        : m_data({ std::move(title), width, height })
    {
        int resultCode = init();
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui_ImplOpenGL3_Init();
        ImGui_ImplGlfw_InitForOpenGL(m_pWindow, true);
        //CreatFunc();
        //Enables();
        //glNormal3f();
    }

    Window::~Window()
    {
        shutdown();
    }

    int Window::init()
    {
        //LOG_INFO("Creating window '{0}' with size {1}x{2}", m_data.title, m_data.width, m_data.height);
        if (!s_GLFW_initialized)
        {
            if (!glfwInit())
            {
                LOG_CRITICAL("Can't initialize GLFW!");
                return -1;
            }
            s_GLFW_initialized = true;
        }

        m_pWindow = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), nullptr, nullptr);
        if (!m_pWindow)
        {
            LOG_CRITICAL("Can't create window {0} with size {1}x{2}", m_data.title, m_data.width, m_data.height);
            glfwTerminate();
            return -2;
        }

        glfwMakeContextCurrent(m_pWindow);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            LOG_CRITICAL("Failed to initialize GLAD");
            return -3;
        }

        glfwSetWindowUserPointer(m_pWindow, &m_data);

        glfwSetWindowSizeCallback(m_pWindow, 
            [](GLFWwindow* pWindow, int width, int height)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));
                data.width = width;
                data.height = height;

                EventWindowResize event(width, height);
                data.eventCallbackFn(event);
            }
        );

        glfwSetCursorPosCallback(m_pWindow,
            [](GLFWwindow* pWindow, double x, double y)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));

                EventMouseMoved event(x, y);
                data.eventCallbackFn(event);
            }
        );

        glfwSetWindowCloseCallback(m_pWindow,
            [](GLFWwindow* pWindow)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));

                EventWindowClose event;
                data.eventCallbackFn(event);
            }
        );

        glfwSetFramebufferSizeCallback(m_pWindow,
            [](GLFWwindow* pWindow, int width, int height)
            {
                glViewport(0, 0, width, height);
            }
        );

        BufferLayout buffer_layout_1vec3
        {
            ShaderDataType::Float3
        };


        BufferLayout buffer_layout_2vec3
        {
            ShaderDataType::Float3,
            ShaderDataType::Float3
        };

        cout << "Вас приветствует программа для моделирования разрушения трёхмерных объектов" << endl
            << "Данная программа создаёт физическую симуляцию некоторых физических экспериментов, " << endl
            << "вызывающих разрушение. Опыты представлены в коснольном меню." << endl;
        experienceData = Interface();
        if (experienceData[0] != 0) {
            rr = -experienceData[3] * 0.01f;
            hh = experienceData[4] * 0.01f;
            ff = experienceData[3] * 0.01f;
        }

    }

    void Window::shutdown()
    {
        glfwDestroyWindow(m_pWindow);
        glfwTerminate();
    }

    int Window::on_update()
    {
        //return 0;
        glClearColor(m_background_color[0], m_background_color[1], m_background_color[2], m_background_color[3]);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize.x = static_cast<float>(get_width());
        io.DisplaySize.y = static_cast<float>(get_height());

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //ImGui::ShowDemoWindow();


        ImGui::Begin("Background Color Window");
        ImGui::ColorEdit4("Background Color", m_background_color);
        ImGui::SliderFloat3("scale", scale, 0.f, 2.f);
        ImGui::SliderFloat("rotate", &rotate, 0.f, 360.f);
        ImGui::SliderFloat3("translate", translate, -1.f, 1.f);

        ImGui::SliderFloat3("camera position", camera_position, -10.f, 10.f);
        ImGui::SliderFloat3("camera rotation", camera_rotation, 0, 360.f);
        ImGui::Checkbox("Perspective camera", &perspective_camera);
        ImGui::Checkbox("End experiment", &end_experiment);

        for (int i = 0; i < p_vao.size(); i++) {
        p_shader_program[i]->bind();
        glm::mat4 scale_matrix(scale[0], 0,        0,        0,
                               0,        scale[1], 0,        0,
                               0,        0,        scale[2], 0,
                               0,        0,        0,        1);

        float rotate_in_radians = glm::radians(rotate);
        glm::mat4 rotate_matrix( cos(rotate_in_radians), sin(rotate_in_radians), 0, 0,
                                -sin(rotate_in_radians), cos(rotate_in_radians), 0, 0,
                                 0,                      0,                      1, 0,
                                 0,                      0,                      0, 1);

        glm::mat4 translate_matrix(1,            0,            0,            0,
                                   0,            1,            0,            0,
                                   0,            0,            1,            0,
                                   translate[0], translate[1], translate[2], 1);

        glm::mat4 model_matrix = translate_matrix * rotate_matrix * scale_matrix;

        p_shader_program[i]->setMatrix4("model_matrix", model_matrix);


        camera.set_position_rotation(glm::vec3(camera_position[0], camera_position[1], camera_position[2]),
                                     glm::vec3(camera_rotation[0], camera_rotation[1], camera_rotation[2]));
        camera.set_projection_mode(perspective_camera ? Camera::ProjectionMode::Perspective : Camera::ProjectionMode::Orthographic);
        p_shader_program[i]->setMatrix4("view_projection_matrix", camera.get_projection_matrix() * camera.get_view_matrix());
        
        p_vao[i]->bind();
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(p_vao[i]->get_indices_count()), GL_UNSIGNED_INT, nullptr);
        }

        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        switch (static_cast<int>(experienceData[0]))
        {
        case 1:
            if (experienceData[1] > 100 || experienceData[2] > 100) {
                cout << "Слишком большие данные. Тексовое описание опыта:" << endl;
                cout << "Количество разрушенных частей первой фигуры: " << static_cast<int>(experienceData[1]) << endl;
                cout << "Количество разрушенных частей второй фигуры: " << static_cast<int>(experienceData[2]) << endl;
                end_experiment = true;
                break;
            }
            if (experienceData[1] < 0 || experienceData[2] < 0) {
                cout << "Слишком большие данные. Невозможно провести эксперимент" << endl;
                end_experiment = true;
                break;
            }
            if (experimentStatus == created) {
                SimpleEngine::CreateFigure(positions_colors, indices, figures_pos_colors, figures_indices, p_shader_program, p_positions_colors_vbo, p_index_buffer, p_vao, vertex_shader, fragment_shader);
                SimpleEngine::CreateFigure(positions_colors2, indices, figures_pos_colors, figures_indices, p_shader_program, p_positions_colors_vbo, p_index_buffer, p_vao, vertex_shader, fragment_shader);
                SimpleEngine::MoveFigure(0, -1, experienceData[5] / 2, 0, figures_pos_colors, figures_indices, p_shader_program, p_positions_colors_vbo, p_index_buffer, p_vao, vertex_shader, fragment_shader);
                SimpleEngine::MoveFigure(0, -1, -(experienceData[5] / 2), 1, figures_pos_colors, figures_indices, p_shader_program, p_positions_colors_vbo, p_index_buffer, p_vao, vertex_shader, fragment_shader);
                experimentStatus = moving;
            }

            if (experimentStatus == moving) {
                //SimpleEngine::MoveFigure(0, -1, -experienceData[3] * 0.01f, 0, figures_pos_colors, figures_indices, p_shader_program, p_positions_colors_vbo, p_index_buffer, p_vao, vertex_shader, fragment_shader);
                //SimpleEngine::MoveFigure(0, -1, experienceData[4] * 0.01f, 1, figures_pos_colors, figures_indices, p_shader_program, p_positions_colors_vbo, p_index_buffer, p_vao, vertex_shader, fragment_shader);
                SimpleEngine::MoveFigure(0, -1, rr, 0, figures_pos_colors, figures_indices, p_shader_program, p_positions_colors_vbo, p_index_buffer, p_vao, vertex_shader, fragment_shader);
                SimpleEngine::MoveFigure(0, -1, hh, 1, figures_pos_colors, figures_indices, p_shader_program, p_positions_colors_vbo, p_index_buffer, p_vao, vertex_shader, fragment_shader);
            }
            if ((experimentStatus == moving) && (figures_pos_colors[0][18] < figures_pos_colors[1][30]) && (figures_pos_colors[0][19] < figures_pos_colors[1][31]) && (figures_pos_colors[0][20] < figures_pos_colors[1][32])) {
                experimentStatus = colided;
            }
            if (experimentStatus == colided) {
                for (int j = 0; j < experienceData[1] - 1; j++) {
                    if (j != 1)
                        SimpleEngine::DestroyFigure(rand() % 3, j, figures_pos_colors, figures_indices, p_shader_program, p_positions_colors_vbo, p_index_buffer, p_vao, vertex_shader, fragment_shader);
                    else
                        experienceData[1] += 1;
                }
                if (experienceData[1] >= 1)
                    experienceData[1] -= 1;
                size = figures_pos_colors.size();
                backSpeed[0] = size;
                for (int j = 1; j < size - 1; j++) {
                    SimpleEngine::DestroyFigure(rand() % 3, j, figures_pos_colors, figures_indices, p_shader_program, p_positions_colors_vbo, p_index_buffer, p_vao, vertex_shader, fragment_shader);
                    if (experienceData[1] == 0)
                        SimpleEngine::CreateFigure(positions_colors, indices, figures_pos_colors, figures_indices, p_shader_program, p_positions_colors_vbo, p_index_buffer, p_vao, vertex_shader, fragment_shader);
                    if (j == 1) {
                        j = figures_pos_colors.size() - 3;
                        size = j + experienceData[2];
                    }
                }
                backSpeed[1] = size;
                experimentStatus = broken;
            }
            size = figures_pos_colors.size();
            if (experimentStatus == broken) {
                size = figures_pos_colors.size();
                if (nn == 0) {
                    for (int j = 0; j < size; j++) {
                        moveCoords1.push_back(rand() % 3);
                        moveCoords2.push_back(rand() % 3);
                    }
                    nn = 1;
                }
                for (int j = 0; j < backSpeed[0]; j++) {
                    SimpleEngine::MoveFigure(moveCoords1[j], moveCoords2[j], (experienceData[3]) * 0.01f, j, figures_pos_colors, figures_indices, p_shader_program, p_positions_colors_vbo, p_index_buffer, p_vao, vertex_shader, fragment_shader);
                    experienceData[3] -= 0.01f;
                    if (experienceData[3] < 0)
                        experienceData[3] = 0;
                }
                for (int j = backSpeed[0]; j < size; j++) {
                    SimpleEngine::MoveFigure(moveCoords1[j], moveCoords2[j], (experienceData[4]) * 0.01f, j, figures_pos_colors, figures_indices, p_shader_program, p_positions_colors_vbo, p_index_buffer, p_vao, vertex_shader, fragment_shader);
                    experienceData[4] -= 0.01f;
                    if (experienceData[4] < 0)
                        experienceData[4] = 0;
                }
                //for (int j = 0; j < backSpeed[0]; j++) {
                //    SimpleEngine::MoveFigure(moveCoords1[j], moveCoords2[j], ff, j, figures_pos_colors, figures_indices, p_shader_program, p_positions_colors_vbo, p_index_buffer, p_vao, vertex_shader, fragment_shader);
                //    ff -= 0.001f;
                //    if (ff < 0)
                //        ff = 0;

                //}
                //for (int j = backSpeed[0]; j < size; j++) {
                //    SimpleEngine::MoveFigure(moveCoords1[j], moveCoords2[j], hh, j, figures_pos_colors, figures_indices, p_shader_program, p_positions_colors_vbo, p_index_buffer, p_vao, vertex_shader, fragment_shader);
                //    hh -= 0.001f;
                //    if (hh < 0)
                //        hh = 0;
                //}
            }
            break;
        case 2:
            if (experienceData[1] > 100) {
                cout << "Слишком большие данные. Тексовое описание опыта:" << endl;
                cout << "Количество разрушенных первой фигуры: " << static_cast<int>(experienceData[1]) << endl;
                end_experiment = true;
                break;
            }
            if (experienceData[1] < 0) {
                cout << "Слишком большие данные. Невозможно провести эксперимент" << endl;
                end_experiment = true;
                break;
            }
            if (experimentStatus2 == whole) {
                SimpleEngine::CreateFigure(positions_colors, indices, figures_pos_colors, figures_indices, p_shader_program, p_positions_colors_vbo, p_index_buffer, p_vao, vertex_shader, fragment_shader);
                for (int j = 0; j < experienceData[1]; j++) {
                    //cout << j;
                    SimpleEngine::DestroyFigure(rand() % 3, j, figures_pos_colors, figures_indices, p_shader_program, p_positions_colors_vbo, p_index_buffer, p_vao, vertex_shader, fragment_shader);
                }
                experimentStatus2 = blowned;
            }
            if (experimentStatus2 == blowned) {
                size = figures_pos_colors.size();
                for (int j = 0; j < size; j++) {
                    moveCoords1.push_back(rand() % 3);
                    moveCoords2.push_back(rand() % 3);
                }
                experimentStatus2 = broken;
            }
            if (experimentStatus2 == broken) {
                for (int j = 0; j < size; j++) {
                    SimpleEngine::MoveFigure(moveCoords1[j], moveCoords2[j], 0.01f, j, figures_pos_colors, figures_indices, p_shader_program, p_positions_colors_vbo, p_index_buffer, p_vao, vertex_shader, fragment_shader);
                }
            }
            break;
        case 0:
            return -2;
            break;
        default:
            break;
        }
        glfwSwapBuffers(m_pWindow);
        glfwPollEvents();
        if (end_experiment) {
            if (!figures_pos_colors.empty())
            figures_pos_colors.clear();
            if (!figures_indices.empty())
            figures_indices.clear();
            if (!p_shader_program.empty())
            p_shader_program.clear();
            if (!p_positions_colors_vbo.empty())
            p_positions_colors_vbo.clear();
            if (!p_index_buffer.empty())
            p_index_buffer.clear();
            if (!p_vao.empty())
            p_vao.clear();
            if (!experienceData.empty())
            experienceData.clear();
            if (!moveCoords1.empty())
            moveCoords1.clear();
            if (!moveCoords2.empty())
            moveCoords2.clear();
			nn = 0;
            experimentStatus = created;
            experimentStatus2 = whole;
            size = 0;
            end_experiment = false;
            experienceData = Interface();
            //Interface(); 
        }
        return 0;
    }
}