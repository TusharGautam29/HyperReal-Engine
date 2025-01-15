#pragma once
namespace HyperR {

	enum class RendererAPI {
		None = 0, OpenGL = 1
	};
	
	class Renderer {
	public:
		inline static RendererAPI GetAPI() { return s_API; }
	private:
		static RendererAPI s_API;
	};
}