//
// Created by Morey on 16/01/2026.
//

#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../include/gls/Shader.h"
#include <unordered_map>
#include "gls/Debug.h"

namespace gls{
    struct Shader::Impl {
        GLuint program;
        std::unordered_map<std::string, GLint> uniformCache;
    };

    static std::string loadShader(const std::string& path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "Failed to open shader: " << path << std::endl;
            return {};
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) : impl(new Impl) {

        if (!gladLoadGL()) {
            std::cerr << "Failed to initialize GLAD\n";
            return;
        }


        std::string vsahder = loadShader(vertexPath);
        std::string fsahder = loadShader(fragmentPath);

        const char *vsSrc = vsahder.c_str();
        const char *fsSrc = fsahder.c_str();

        GLuint vshader =  GL_CHECK_RET(glCreateShader(GL_VERTEX_SHADER));
         GL_CHECK(glShaderSource(vshader, 1, &vsSrc, nullptr));
         GL_CHECK(glCompileShader(vshader));

        int success;
        char info[512];
        GLint programInfo;

         GL_CHECK(glGetShaderiv(vshader, GL_COMPILE_STATUS, &success));
        if (!success) {
             GL_CHECK(glGetShaderInfoLog(vshader, 512, nullptr, info));
            std::cout << info << std::endl;
        } else {
            std::cout << "Vertex Shader initialized " << std::endl;
        }
        GLuint fshader =  GL_CHECK_RET(glCreateShader(GL_FRAGMENT_SHADER));
         GL_CHECK(glShaderSource(fshader, 1, &fsSrc, nullptr));
         GL_CHECK(glCompileShader(fshader));

         GL_CHECK(glGetShaderiv(fshader, GL_COMPILE_STATUS, &success));
        if (!success) {
             GL_CHECK(glGetShaderInfoLog(fshader, 512, nullptr, info));
            std::cout << info << std::endl;
        } else {
            std::cout << "Fragment Shader initialized " << std::endl;
        }

        impl->program =  GL_CHECK_RET(glCreateProgram());
        if (!impl->program) {
            std::cerr << "Failed to initialize program GL\n"; return;
        }

         GL_CHECK(glAttachShader(impl->program, vshader));
         GL_CHECK(glAttachShader(impl->program, fshader));
         GL_CHECK(glLinkProgram(impl->program));

         GL_CHECK(glGetProgramiv(impl->program, GL_LINK_STATUS, &success));
        if (!success) {
            char infoLog[512];
             GL_CHECK(glGetProgramInfoLog(impl->program, 512, nullptr, infoLog));
            std::cerr << infoLog << std::endl;
        }

         GL_CHECK(glDeleteShader(vshader));
         GL_CHECK(glDeleteShader(fshader));
    }

    Shader::~Shader() {
        glDeleteProgram(impl->program);
        delete impl;
    }

    GLint Shader::getUniformLocation(const std::string& name) const {
        auto it = impl->uniformCache.find(name);

        if (it != impl->uniformCache.end()) {
            return it->second;
        }

        GLint location =  GL_CHECK_RET(glGetUniformLocation(impl->program, name.c_str()));
        impl->uniformCache[name] = location;

        return location;
    }


    void Shader::use() {
         GL_CHECK(glUseProgram(impl->program));
    }

    void Shader::setBool (const std::string& name, bool value) const {
         GL_CHECK(glUniform1i(getUniformLocation(name.c_str()), (int)value));
    }

    void Shader::setInt  (const std::string& name, int value) const {
         GL_CHECK(glUniform1i(glGetUniformLocation(impl->program, name.c_str()), value));
    }

    void Shader::setFloat(const std::string& name, float value) const {
         GL_CHECK(glUniform1f(glGetUniformLocation(impl->program, name.c_str()), value));
    }


    void Shader::setVec2(const std::string& name, const float* v) const{
         GL_CHECK(glUniform3fv(
           glGetUniformLocation(impl->program, name.c_str()),
           1,
           v
       ));
    }

    void Shader::setVec3(const std::string& name, const float* v) const {
         GL_CHECK(glUniform3fv(
            glGetUniformLocation(impl->program, name.c_str()),
            1,
            v
        ));
    }


    void Shader::setVec4(const std::string& name, const float* v) const {
         GL_CHECK(glUniform3fv(
           glGetUniformLocation(impl->program, name.c_str()),
           1,
           v
       ));
    }



    void Shader::setMat3(const std::string& name, const float* m) const {
         GL_CHECK(glUniformMatrix3fv(
            glGetUniformLocation(impl->program, name.c_str()),
            1,
            GL_FALSE,
            m
        ));
    }

    void Shader::setMat4(const std::string& name, const float* m) const {
         GL_CHECK(glUniformMatrix4fv(
            glGetUniformLocation(impl->program, name.c_str()),
            1,
            GL_FALSE,
            m
        ));
    }



}
