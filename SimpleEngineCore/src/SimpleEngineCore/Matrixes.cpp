#include "SimpleEngineCore/Matrixes.hpp"

glm::mat4 GetScaleMatrix() {
    glm::mat4 scale_matrix(1.f, 0, 0, 0,
        0, 1.f, 0, 0,
        0, 0, 1.f, 0,
        0, 0, 0, 1);
    return scale_matrix;
}
glm::mat4 GetRotateMatrix() {
    float rotate_in_radians = glm::radians(0.f);
    glm::mat4 rotate_matrix(cos(rotate_in_radians), sin(rotate_in_radians), 0, 0,
        -sin(rotate_in_radians), cos(rotate_in_radians), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1);
    return rotate_matrix;
}
glm::mat4 GetTranslateMatrix() {
    glm::mat4 translate_matrix(1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0.f, 0.f, 0.f, 1);
    return translate_matrix;
}

glm::mat4 GetModelMatrix() {
    return GetTranslateMatrix() * GetRotateMatrix() * GetScaleMatrix();
}