#ifndef SHADER_H
#define SHADER_H
#include "export.h"
#include <iostream>

class ENGINE_API Shader {
private:
	unsigned int _id;
	unsigned int Compile(unsigned int type, std::string& source);
	void CreateAttribPointer(unsigned int shaderAttribIndex, int dataAmmount, int dataSize, int dataPosition);

public:
	Shader();
	~Shader();
	void Create(const char* vertexPath, const char* fragmentPath);
	void Use();
	void SetVertexAttributes(const char* name);
	void SetColorAttributes(const char* name);
	unsigned int GetMatrixAttributes(const char* name);
	unsigned int GetID();
};

#endif // !SHADER_H

