#include <cmath>
#include "raylib/include/raylib.h"
#include "raylib/include/raymath.h"

//Screen Size
const int   screenWidth   {800};
const int   screenHeight  {600};

//Sector Circle min-max angle
const float maxSectorAngle = 180.0f;
const float minSectorAngle = 5.0f;

//Movement Speed 
const float movementSpeed {200.0f};

//Input Movement Function declaration
void InputMovement(Vector2& ballPos, float& deltaTime)
{
    if(IsKeyDown(KEY_W)) ballPos.y -= movementSpeed * deltaTime;
    if(IsKeyDown(KEY_S)) ballPos.y += movementSpeed * deltaTime;
    if(IsKeyDown(KEY_D)) ballPos.x += movementSpeed * deltaTime;
    if(IsKeyDown(KEY_A)) ballPos.x -= movementSpeed * deltaTime;
}

int main()
{
    //Current Time initialization
    double currentElapsedTime = 0.0f;

    //Sector Circle Variables
    float outerRadius    = 40.f;
    float minOuterRadius = 50.f;
    float startAngle     = 0.f;
    float endAngle       = 100.f;
    int   segments       = 100;

    float mouseAngle;

    Vector2 ballPos = { (float)screenWidth/2, (float)screenHeight/2 };

    InitWindow(screenWidth, screenHeight, "Audio Actor Test");
    InitAudioDevice();

    Sound radarSFX = LoadSound("audiofiles/radar_click.wav");

    while (!WindowShouldClose())
    {
        //Current time modified in game loop with GetFrameTime function
        currentElapsedTime += GetFrameTime();
        float deltaTime     = GetFrameTime();

        //Mouse Position and Mouse-Ball distance vectors 
        Vector2 mousePos = GetMousePosition();
        float   distance = Vector2Distance(mousePos, ballPos);

        //Radian and Degree calculation of mouse position using ball as an origin
        float centerLineRadian = std::atan2(mousePos.y - ballPos.y, mousePos.x - ballPos.x);
        float centerLineAngle  = centerLineRadian * (180 / PI);

        //If angle goes below 0 modify it to 360
        if(centerLineAngle < 0) centerLineAngle += 360;

        //Sector Circle Radius modifier
        outerRadius = minOuterRadius + distance;

        //Sector Circle Width modifier
        float sectorWidth = maxSectorAngle - Clamp(distance, minSectorAngle, maxSectorAngle - minSectorAngle);
        startAngle        = centerLineAngle - sectorWidth;
        endAngle          = centerLineAngle + sectorWidth;
        
        //Input Movement call
        InputMovement(ballPos, deltaTime);
        if(IsKeyPressed(KEY_F)) PlaySound(radarSFX);

        BeginDrawing();
            ClearBackground(BLACK);
            //Current time panel
            DrawText(TextFormat("%f", currentElapsedTime), 20, 20, 20, RAYWHITE);
            //Current angle panel
            DrawText(TextFormat("%f", centerLineAngle), 20, 40, 20, RAYWHITE);
            //Draw Sector Circle
            DrawCircleSector(ballPos, outerRadius, startAngle, endAngle, segments, Fade(PINK, 0.3));
            //Draw Main Circle
            DrawCircleV(ballPos, 12, RAYWHITE);
        EndDrawing();
    }

    UnloadSound(radarSFX);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}