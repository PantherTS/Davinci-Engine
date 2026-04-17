#include "ShaderAsset.h"
#include <glad/gl.h>
#include <fstream>
#include <sstream>
#include <SDL3/SDL.h>

using namespace DavinciEngine;

ShaderAsset::ShaderAsset() : Asset(ASSET_SHADER), m_program(0) {}
ShaderAsset::~ShaderAsset() {}

std::string ShaderAsset::LoadFile(const std::string& path)
{
	std::ifstream file(path);

	if (!file.is_open())
	{
		Error("FAILED TO OPEN FILE: %s\n", path.c_str());
		return "";
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

unsigned int ShaderAsset::CompileShader(unsigned int type, const char* source)
{
	if (source == nullptr || strlen(source) == 0)
	{
		printf("ERROR: Shader source is empty!\n");
		return 0;
	}

	if (!SDL_GL_GetCurrentContext())
	{
		Log("NO OPENGL CONTEXT ON THIS THREAD");
	}

	unsigned int id = glCreateShader(type);
	glShaderSource(id, 1, &source, nullptr);
	glCompileShader(id);

	int success;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(id, 512, nullptr, infoLog);
		Error("Shader compile error: %s\n", infoLog);

		glDeleteShader(id);
		return 0;
	}

	return id;
}

void DavinciEngine::ShaderAsset::Reload()
{}

void DavinciEngine::ShaderAsset::Unload()
{}

bool ShaderAsset::Load(const std::string& vertexPath, const std::string& fragmentPath)
{
	std::string vCode = LoadFile(vertexPath);
	std::string fCode = LoadFile(fragmentPath);

	if (vCode.empty() || fCode.empty())
	{
		Error("Shader source is empty!");
		return false;
	}

	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vCode.c_str());
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fCode.c_str());

	if (vs == 0 || fs == 0)
	{
		printf("Shader compile failed. Aborting program link.\n");
		return false;
	}

	m_program = glCreateProgram();
	glAttachShader(m_program, vs);
	glAttachShader(m_program, fs);
	glLinkProgram(m_program);

	int success;
	glGetProgramiv(m_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(m_program, 512, nullptr, infoLog);
		printf("Shader link error: %s\n", infoLog);
		return false;
	}

	glDeleteShader(vs);
	glDeleteShader(fs);

	return true;
}

void ShaderAsset::Bind() const
{
	if (m_program == 0)
	{
		printf("ERROR: Trying to bind invalid shader program!\n");
		return;
	}

	glUseProgram(m_program);
}