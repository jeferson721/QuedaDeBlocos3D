#include <stdio.h>
#include "raylib.h"

static void Bloco(Vector3 pos) {	
    DrawCube(pos, 1.0f, 1.0f, 1.0f, BLUE);
}

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "QuedaDeBlocos3D");
    Camera camera = { 0 };
    camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    DisableCursor(); 
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        UpdateCamera(&camera, CAMERA_FREE);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(camera);
        Bloco((Vector3) { -4.0f, 0.0f, 2.0f });
        DrawGrid(10, 1.0f);
        EndMode3D();
        DrawFPS(10, 10);
        EndDrawing();
        if (IsKeyDown(KEY_ESCAPE))break;
    }
    CloseWindow();
    return 0;
}