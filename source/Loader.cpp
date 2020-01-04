
#include <Loader.h>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>

bool loadOBJ(const char* path, std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals, std::vector<glm::vec2>& uvTextures) 
{
	std::ifstream fs;
	fs.open(path);

	if (fs.is_open() == false) return false;

	std::vector< glm::vec3 > v_arr;
	std::vector< glm::vec3 > n_arr;
	std::vector< glm::vec2 > t_arr;

	v_arr.reserve(10000);
	n_arr.reserve(10000);
	t_arr.reserve(10000);

	std::string line;
	while (std::getline(fs, line))
	{
		std::istringstream iss(line);
		
		std::string prefix;
		iss >> prefix;

		if (prefix == "#")
		{
			continue;
		}
		if (prefix == "vt")
		{
			glm::vec2 val;
			iss >> val.x >> val.y;

			t_arr.push_back(val);
		}
		else if (prefix == "vn")
		{
			glm::vec3 val;
			iss >> val.x >> val.y >> val.z;

			n_arr.push_back(val);
		}
		else if (prefix == "v")
		{
			glm::vec3 val;
			iss >> val.x >> val.y >> val.z;

			v_arr.push_back(val);
		}
		else if (prefix == "f")
		{
			char bar;
			glm::ivec3 i0;
			iss >> i0.x >> bar >> i0.y >> bar >> i0.z;

			glm::ivec3 i1;
			iss >> i1.x >> bar >> i1.y >> bar >> i1.z;

			glm::ivec3 i2;
			iss >> i2.x >> bar >> i2.y >> bar >> i2.z;

			positions.push_back(v_arr[i0.x-1]);
			positions.push_back(v_arr[i1.x-1]);
			positions.push_back(v_arr[i2.x-1]);

			uvTextures.push_back(t_arr[i0.y-1]);
			uvTextures.push_back(t_arr[i1.y-1]);
			uvTextures.push_back(t_arr[i2.y-1]);

			normals.push_back(n_arr[i0.z-1]);
			normals.push_back(n_arr[i1.z-1]);
			normals.push_back(n_arr[i2.z-1]);
		}
	}

	return true;
}
