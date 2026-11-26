#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include "glad.h"

class ParticleSystem
{
    private:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    Shader shader;
    unsigned int ssboPos;
    unsigned int ssboScale;
    unsigned int ssboVel;

    unsigned int computeShader;
    unsigned int computeShaderProgram;

    public:
    Vector3 position;
    float speed = 2.0f;

    void Init();
    void Update();
    void Render();
    void Delete();
};

#endif
