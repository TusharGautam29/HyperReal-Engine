#pragma once
#include "hrpch.h"
#include "VertexArray.h"
#include "Buffer.h"
#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Vertex.h"

namespace HyperR {

	
	class Mesh {
	public:
		static Ref<Mesh> Create(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const Ref<Shader>& shader);
		virtual ~Mesh() = default;
		virtual const Ref<Shader>& GetShader() const = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void Draw() const = 0;

	};


}
