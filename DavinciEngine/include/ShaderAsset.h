#pragma once
#include "Asset.h"
#include <string>

namespace DavinciEngine {

class ShaderAsset : public Asset
{
public:
    ShaderAsset();
    ~ShaderAsset();

    bool Load(const std::string& vertexPath, const std::string& fragmentPath);
    void Reload() override;
    void Unload() override;

    void Bind() const;
    unsigned int GetProgram() const { return m_program; }

private:
    unsigned int m_program;

    std::string LoadFile(const std::string& path);
    unsigned int CompileShader(unsigned int type, const char* source);
};

}