#pragma once

#include <raylib.h>
#include <string.h>

/* Slider */

// Use 'actual' when you're using this for actual values.
typedef struct Slider {
  float value, div_value;
  Vector2 pos;
  int max, min;
  float internal, actual;

  struct Body {
    float xPos, yPos, w, h;
  } Body;
} Slider;

bool InVector2(Vector2 thing, Vector2 check, int minVal, int maxVal);
void UpdateSlider(Slider* s, Vector2 mousePos);
void DrawSlider(Slider s);

/* Buttons */

typedef struct Button {
  Vector2 xy;
  Vector2 dim;
  char text[30];
  Color clicked_color;
  Color neutral_color;
} Button;

void render_button(Button b, Vector2 m);
bool DidClickButton(Button b, Vector2 m);
bool DidHoldButton(Button b, Vector2 m);

/* Input */
#define INP_MAX 20
typedef struct Input {
  char input_data[INP_MAX];
  Vector2 input_area;
  Vector2 end_area;
  int counter;
  int max;
} Input;

bool MouseOverInputArea(Vector2 i, Vector2 e);
void UpdateInputBox(Input* i);
void DrawInput(Input i);


/* Checkboxes */
typedef struct Checkbox {
  Vector2 location;
  bool isSelected;
  bool mousein;
  
  // Optional. This won't be displayed if label is null.
  struct {
    char label[30];
    int fontSize;
  } label;
} Checkbox;


extern Checkbox checkboxes[3];

void drawCheckbox(Checkbox c);
void updateCheckbox(Checkbox* c, Vector2 m);
void checkboxCheckOthers();
