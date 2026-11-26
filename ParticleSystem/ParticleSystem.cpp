#include "ParticleSystem.h"


void ParticleSystem::Init()
{
    shader = LoadShader("vert.vs", "frag.fs");
    int camMatrixLoc = GetShaderLocation(shader, "camMat");

    ssboPos = rlLoadShaderBuffer(3000*sizeof(Vector4), NULL, RL_DYNAMIC_COPY);
    ssboScale = rlLoadShaderBuffer(3000*sizeof(Vector4), NULL, RL_DYNAMIC_COPY);
    ssboVel = rlLoadShaderBuffer(3000*sizeof(Vector4), NULL, RL_DYNAMIC_COPY);

    char* computeShaderSource = LoadFileText("compute.comp");
    computeShader = rlLoadShader(computeShaderSource, RL_COMPUTE_SHADER);
    computeShaderProgram = rlLoadShaderProgramCompute(computeShader);
    UnloadFileText(computeShaderSource);

    //Create buffer for vertices
    float vertices[] = {

    -0.5f, -0.5f,  0.5f, 
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f, 
    -0.5f,  0.5f,  0.5f, 

    -0.5f, -0.5f, -0.5f, 
     0.5f, -0.5f, -0.5f, 
     0.5f,  0.5f, -0.5f, 
    -0.5f,  0.5f, -0.5f  
};

unsigned int indices[] = {
    
    0, 1, 2,
    2, 3, 0,
   
    1, 5, 6,
    6, 2, 1,
    
    7, 6, 5,
    5, 4, 7,
    
    4, 0, 3,
    3, 7, 4,
    
    4, 5, 1,
    1, 0, 4,
    
    3, 2, 6,
    6, 7, 3
};

position = {0.0f, 0.0f, 0.0f};

glGenVertexArrays(1, &VAO);
glGenBuffers(1, &VBO);
glGenBuffers(1, &EBO);

glBindVertexArray(VAO);

glBindBuffer(GL_ARRAY_BUFFER,VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(float)*24, vertices, GL_STATIC_DRAW);

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*36, indices, GL_STATIC_DRAW);

glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

}

void ParticleSystem::Update()
{
    rlEnableShader(computeShaderProgram);
    float dt = GetFrameTime();

    rlSetUniform(rlGetLocationUniform(computeShaderProgram,"dt"), &dt, SHADER_UNIFORM_FLOAT,1);
    rlSetUniform(rlGetLocationUniform(computeShaderProgram, "speed"), &speed, SHADER_UNIFORM_FLOAT, 1);
    rlSetUniform(rlGetLocationUniform(computeShaderProgram, "initPos"), &position, SHADER_UNIFORM_VEC3, 1);

    rlBindShaderBuffer(ssboPos, 0);
    rlBindShaderBuffer(ssboScale, 1);
    rlBindShaderBuffer(ssboVel, 2);
    rlComputeShaderDispatch(3000/4, 1, 1);
    glMemoryBarrier(GL_ALL_BARRIER_BITS);
    rlDisableShader();
}

void ParticleSystem::Render()
{
    BeginShaderMode(shader);
    rlBindShaderBuffer(ssboPos, 0);
    rlBindShaderBuffer(ssboScale, 1);
    rlBindShaderBuffer(ssboVel, 2);

    //Bind camera matrix and draw stuff
    
    Matrix modelview = rlGetMatrixModelview();
    Matrix projection = rlGetMatrixProjection();
    Matrix mvp = MatrixMultiply(modelview, projection);

    int camMatrixLoc = GetShaderLocation(shader, "camMat");
    SetShaderValueMatrix(shader, camMatrixLoc, mvp);

    glBindVertexArray(VAO);
    glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, 3000);
    
    EndShaderMode();
}

void ParticleSystem::Delete()
{
    rlUnloadShaderBuffer(ssboPos);
    rlUnloadShaderBuffer(ssboScale);
    rlUnloadShaderBuffer(ssboVel);
    UnloadShader(shader);

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);
}