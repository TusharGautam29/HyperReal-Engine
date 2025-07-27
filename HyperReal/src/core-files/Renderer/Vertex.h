#pragma once
#include <glm/glm.hpp>

namespace HyperR {

	struct Vertex {
		glm::vec3 Position;
		//glm::vec3 Normal;
		glm::vec2 TexCoord;

		bool operator==(const Vertex& other) const {
			return Position == other.Position &&
				TexCoord == other.TexCoord;
		}
	};

}
