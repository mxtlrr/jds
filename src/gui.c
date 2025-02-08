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
    if(i->counter > i->max) {
      memset(i->input_data, 0, INP_MAX);
      i->counter = 0;
    }
  }
}

void DrawInput(Input i){
  DrawRectangle(i.input_area.x, i.input_area.y, i.end_area.x-i.input_area.x, i.end_area.y-i.input_area.y, GRAY);
  DrawText(i.input_data, i.input_area.x+10, i.input_area.y+((i.end_area.y-i.input_area.y)/3), 20, BLACK);
}

/* Buttons */
bool internal_ismousein(Vector2 xy, int w, int h, Vector2 mouse){
  if(mouse.x >= xy.x && mouse.x <= xy.x + w){
    if(mouse.y >= xy.y && mouse.y <= xy.y + h){
      return true;
    }
  }
  return false;
}

void render_button(Button b, Vector2 m){
  if(internal_ismousein(b.xy, b.dim.x, b.dim.y, m)){
    DrawRectangle(b.xy.x, b.xy.y, b.dim.x, b.dim.y, b.clicked_color);
    DrawText(b.text, b.xy.x+8, b.xy.y+(b.dim.y/4)-2, 20, WHITE);
  } else {
    DrawRectangle(b.xy.x, b.xy.y, b.dim.x, b.dim.y, b.neutral_color);
    DrawText(b.text, b.xy.x+8, b.xy.y+(b.dim.y/4)-2, 20, WHITE);
  }
}

bool DidClickButton(Button b, Vector2 m){
  return (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) && internal_ismousein(b.xy, b.dim.x, b.dim.y, m);
}


bool DidHoldButton(Button b, Vector2 m){
  return (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) &&
      internal_ismousein(b.xy, b.dim.x, b.dim.y, m);
}


/* Checkbox */
void drawCheckbox(Checkbox c){
  DrawRectangle(c.location.x, c.location.y, 40, 40, GRAY);
  DrawRectangleLines(c.location.x, c.location.y, 40, 40, BLACK);
  if(c.label.label[0] != 0x00){
    DrawText(c.label.label, c.location.x+50, c.location.y+10,
             c.label.fontSize, BLACK);
  }
  // Active indicator
  if(c.isSelected) DrawText("X", c.location.x+7, c.location.y, 40, BLACK);
}

