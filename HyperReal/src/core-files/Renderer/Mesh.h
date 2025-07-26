#pragma once
#include "hrpch.h"
#include "VertexArray.h"
#include "Buffer.h"
#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp>

namespace HyperR {

	

	class Mesh {
	public:
		Ref<Mesh> Create(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);
		~Mesh() = default;

		virtual void Bind() const=0;
		virtual void Unbind() const=0;

	private:
		void SetupMesh();

	
	};

}
