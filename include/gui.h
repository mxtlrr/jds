#pragma once

#include <raylib.h>

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

/* Input */