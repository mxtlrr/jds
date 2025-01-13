#include <stdio.h>
#include <raylib.h>

int main(void){
  InitWindow(1024, 768, TextFormat("JDS git-%s", VERSION));
  SetTargetFPS(60);

  while(!WindowShouldClose()){
    BeginDrawing();
    ClearBackground(WHITE);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}