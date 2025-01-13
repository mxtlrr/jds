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

/* Input */
bool MouseOverInputArea(Vector2 i, Vector2 e){
  Vector2 mousepos = GetMousePosition();
  if(mousepos.x > i.x && mousepos.x < e.x){
    if(mousepos.y < e.y && mousepos.y > i.y){
      return true;
    }
  }
  return false;
}

void UpdateInputBox(Input* i){
  if(MouseOverInputArea(i->input_area, i->end_area)){
    int key = GetCharPressed();
    if (key != 0) {
      i->input_data[i->counter++] = (char)key;
    }
    if(i->counter > INP_MAX-1) {
      memset(i->input_data, 0, INP_MAX);
      i->counter = 0;
    }
  }
}

void DrawInput(Input i){
  DrawRectangle(i.input_area.x, i.input_area.y, i.end_area.x-i.input_area.x, i.end_area.y-i.input_area.y, GRAY);
  DrawText(i.input_data, i.input_area.x+10, i.input_area.y+((i.end_area.y-i.input_area.y)/3), 20, BLACK);
}
