#include "gui.h"

/* Slider */
bool InVector2(Vector2 thing, Vector2 check, int minVal, int maxVal){
  if(check.x >= minVal && check.x <= maxVal && thing.y+(15) >= check.y && thing.y-15 <= check.y) return true;
  return false;
}

void UpdateSlider(Slider* s, Vector2 mousePos){
  if(InVector2(s->pos, mousePos, s->Body.xPos, s->Body.w+s->pos.x)){
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) s->internal = mousePos.x-(s->pos.x);
  }
  if(s->value > s->max) s->value = s->max;
  if(s->value < s->min) s->value = s->min;

  s->actual = s->internal/(s->div_value);
  if(s->actual < 0) s->actual = 0;
}

void DrawSlider(Slider s){
  DrawRectangle(s.Body.xPos, s.Body.yPos, s.Body.w, s.Body.h, GRAY);
  if(s.pos.x+s.internal < s.pos.x){
    DrawCircle(s.pos.x, s.pos.y, 20, BLUE);
  } else DrawCircle(s.pos.x+s.internal, s.pos.y, 20, BLUE);
}
