#pragma once

#include <vector>
#include <GL/glew.h>

#include "GraphicsAPI.h"

class OpenGL : public Graphics {
public:
	OpenGL();
	~OpenGL();
	virtual void Initialise(std::weak_ptr<SDL_Window> window);
	virtual void UnInitialise();

	virtual unsigned LoadVertexShader(std::string_view filename, std::string_view entry, std::string_view shaderModel);
	virtual unsigned LoadFragmentShader(std::string_view filename, std::string_view entry, std::string_view shaderModel);

	virtual void SetVertexShader(unsigned vertexID);
	virtual void SetFragmentShader(unsigned fragmentID);

	virtual void LinkProgram();
	virtual void StartFrame();
	virtual void EndFrame();

	virtual void OrthoProjectionMatrix(float ScreenW, float ScreenH);


	///Primitive Creation Functions
	virtual bool CreateMesh() = 0;
	virtual bool CreateTexture(std::string_view filename, unsigned& sampleID);

	virtual bool Render(unsigned sampleID, glm::dmat4x4 transform, glm::bvec2 uv, glm::bvec2 UVscale, bool blend, float alpha);
	virtual void SetBackgroundColor(Color const& color);

private:

	struct ImageObj {
		
	};
	
	SDL_GLContext m_Context;
	unsigned m_VertexID, m_FragmentID;

	GLuint m_ProgramID;

	glm::mat4 m_Projection;
	std::vector<
};