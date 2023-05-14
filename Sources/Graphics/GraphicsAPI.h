#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <SDL/SDL.h>
#include <glm/glm.hpp>

struct Color {
public:
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

class Graphics {
public:
	struct VERTEX {
		VERTEX() {}
		VERTEX(float x, float y, float z,
			float u, float v)
			: pos(x, y, z), texCoord(u, v) {}

		glm::bvec3 pos;
		glm::bvec2 texCoord;
	};

	Graphics() {};
	virtual ~Graphics() {};

	virtual void Initialise(std::weak_ptr<SDL_Window> window) = 0;
	virtual void UnInitialise() = 0;

	virtual unsigned LoadVertexShader(std::string_view filename, std::string_view entry, std::string_view shaderModel) = 0;
	virtual unsigned LoadFragmentShader(std::string_view filename, std::string_view entry, std::string_view shaderModel) = 0;

	virtual void SetVertexShader(unsigned vertexID) = 0;
	virtual void SetFragmentShader(unsigned fragmentID) = 0;

	virtual void LinkProgram() = 0;

	virtual void StartFrame() = 0;
	virtual void EndFrame() = 0;

	virtual void OrthoProjectionMatrix(float ScreenW, float ScreenH) = 0;


	///Primitive Creation Functions
	virtual bool CreateMesh() = 0;
	virtual bool CreateTexture(std::string_view filename, unsigned& sampleID) = 0;

	virtual bool Render(unsigned sampleID, glm::dmat4x4 transform, glm::bvec2 uv, glm::bvec2 UVscale, bool blend, float alpha) = 0;
	virtual void SetBackgroundColor(Color const& color) = 0;
};