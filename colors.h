#include "raylib.h"
#include <assert.h>
#include <ostream>
#include <iostream> //for cout debugging
//see-through
#define TRANSPARENT CLITERAL(Color){0,0,0,0}

//Color
bool operator==(const Color& lhs, const Color& rhs);
bool operator!=(const Color& lhs, const Color& rhs);
Color operator+(const Color& lhs, const Color& rhs);
Color operator-(const Color& lhs, const Color& rhs);
Color HuePicker(Rectangle bounds, const Color& c);
bool ColorsAreSimilar(Color& c1, Color& c2, float tolerancePC=0.6);
float ColorDistance(Color& c1, Color& c2);
float ColorBrightness(Color& c);
std::ostream& operator<<(std::ostream& os, const Color& t);
