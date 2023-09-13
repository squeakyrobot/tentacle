#include "util.h"

int normalizeRange(int value, int min, int max, int inMin, int inMax)
{
  return (value - inMin) * (max - min) / (inMax - inMin) + min;
}