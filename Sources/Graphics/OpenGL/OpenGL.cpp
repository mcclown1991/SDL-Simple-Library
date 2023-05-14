#include <iostream>
#include <fstream>
#include "OpenGL.h"
#include "SDLCore.h"
#include <glm/gtc/matrix_transform.hpp>

OpenGL::OpenGL() : Graphics() {

}

OpenGL::~OpenGL() {
	
}

void OpenGL::Initialise(std::weak_ptr<SDL_Window> window) {
	std::shared_ptr<SDL_Window> p_Window = window.lock();
	if (!p_Window)
		return;
	
	// Initialize rendering context
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(
		SDL_GL_CONTEXT_PROFILE_MASK,
		SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	m_Context = SDL_GL_CreateContext(p_Window.get());
	if (m_Context == NULL) {
		fprintf(stderr, "Failed to create GL context\n");
		SDLCore::GetSDLCore()->SystemExit();
		return;
	}

	SDL_GL_SetSwapInterval(1); // Use VSYNC

	// Initialize GL Extension Wrangler (GLEW)
	GLenum err;
	glewExperimental = GL_TRUE; // Please expose OpenGL 3.x+ interfaces
	err = glewInit();
	if (err != GLEW_OK) {
		fprintf(stderr, "Failed to init GLEW\n");
		SDL_GL_DeleteContext(m_Context);
		SDLCore::GetSDLCore()->SystemExit();
	}
}

void OpenGL::UnInitialise() {

}

unsigned OpenGL::LoadVertexShader(std::string_view filename, std::string_view entry, std::string_view shaderModel) {
	//UNREFERENCED_PARAMETER(entry);
	//UNREFERENCED_PARAMETER(shaderModel);

	std::string file = filename.data();
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	file += "_gl.vs";
	std::ifstream VertexShaderStream(file, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::string Line = "";
		while (std::getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
	else {
		std::cout << "Impossible to open " << file << ". Are you in the right directory ? Don't forget to read the FAQ !" << std::endl;
		//printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", filename);
		getchar();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	std::cout << "Compiling shader : " << file << std::endl;
	//printf("Compiling shader : %s\n", filename);
	char const* VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	return VertexShaderID;
}

unsigned OpenGL::LoadFragmentShader(std::string_view filename, std::string_view entry, std::string_view shaderModel) {
	//UNREFERENCED_PARAMETER(entry);
	//UNREFERENCED_PARAMETER(shaderModel);

	std::string file = filename.data();
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	file += "_gl.frag";
	std::ifstream FragmentShaderStream(file, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Fragment Shader
	std::cout << "Compiling shader : " << file << std::endl;
	//printf("Compiling shader : %s\n", filename);
	char const* FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	return FragmentShaderID;
}

void OpenGL::SetVertexShader(unsigned vertexID) {
	m_VertexID = vertexID;
}

void OpenGL::SetFragmentShader(unsigned fragmentID) {
	m_FragmentID = fragmentID;
}

void OpenGL::LinkProgram() {
	// Link the program
	printf("Linking program\n");
	m_ProgramID = glCreateProgram();
	glAttachShader(m_ProgramID, m_VertexID);
	glAttachShader(m_ProgramID, m_FragmentID);
	glBindFragDataLocation(m_ProgramID, 0, "out_Color");
	glLinkProgram(m_ProgramID);

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Check the program
	glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(m_ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}
}

void OpenGL::StartFrame() {
	glUseProgram(m_ProgramID);

}

void OpenGL::EndFrame() {

}

void OpenGL::OrthoProjectionMatrix(float ScreenW, float ScreenH) {
	m_Projection = glm::ortho(0.f, ScreenW, ScreenH, 0.f, -5.f, 5.f);
}

bool OpenGL::CreateMesh() {
	VERTEX vertices[] =
	{
		VERTEX(-1.0f, -1.0f, 1.0f, 0.0f, 1.0f),
		VERTEX(-1.0f, 1.0f, 1.0f, 0.0f, 0.0f),
		VERTEX(1.0f, 1.0f, 1.0f, 1.0f, 0.0f),
		VERTEX(1.0f, -1.0f, 1.0f, 1.0f, 1.0f)
	};

	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VERTEX) * 4, vertices, GL_STATIC_DRAW);
	return true;
}

bool OpenGL::CreateTexture(std::string_view filename, unsigned& sampleID) {
	//GLuint texture = Load
	return true;
}

bool OpenGL::Render(unsigned sampleID, glm::dmat4x4 transform, glm::bvec2 uv, glm::bvec2 UVscale, bool blend, float alpha) {

	return true;
}