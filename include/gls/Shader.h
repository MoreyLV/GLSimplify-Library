//
// Created by Morey on 16/01/2026.
//

#ifndef GLSIMPLIFY_SHADER_H
#define GLSIMPLIFY_SHADER_H

namespace gls {
    class Shader {
    public:
        Shader(const std::string& vertexPath, const std::string& fragmentPath);
        ~Shader();

        void use();
        void setBool (const std::string& name, bool value) const;
        void setInt  (const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;

        void setVec2(const std::string& name, const float* data) const;
        void setVec3(const std::string& name, const float* data) const;
        void setVec4(const std::string& name, const float* data) const;

        void setMat3(const std::string& name, const float* data) const;
        void setMat4(const std::string& name, const float* data) const;
    private:
        struct Impl;
        Impl* impl;
        int getUniformLocation(const std::string& name) const;
    };
}



#endif //GLSIMPLIFY_SHADER_H