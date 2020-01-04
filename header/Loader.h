#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>


bool loadOBJ(const char* path, std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals, std::vector<glm::vec2>& uvTextures);
