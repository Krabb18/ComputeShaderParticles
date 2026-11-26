#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include <iostream>

#include "ParticleSystem.h"

using namespace std;

int main()
{
    InitWindow(1200, 800, "ParticleSystem");

    Camera camera = {0};
    camera.position = {0.0f, 10.0f, 10.0f};
    camera.fovy = 45.0f;
    camera.target = {0.0f,0.0f,0.0f};
    camera.up = {0.0f,1.0f,0.0f};
    camera.projection = CAMERA_PERSPECTIVE;

    ParticleSystem particleSystem;
    particleSystem.Init();

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        particleSystem.Update();
        particleSystem.Render();

        DrawGrid(10, 1.0f);
        EndMode3D();

        EndDrawing();
    }
    

    particleSystem.Delete();
    CloseWindow();
}