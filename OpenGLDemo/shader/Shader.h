#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	Shader(const std::string &vertexPath, const std::string &fragmentPath);
	virtual ~Shader();

	void use();
	GLuint getID() { return m_ShaderID; }
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
private:
	void checkCompileErrors(GLuint shader, std::string type);

private:
	GLuint m_ShaderID;
};