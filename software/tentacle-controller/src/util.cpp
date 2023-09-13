#include <stdio.h>

int normalizeRange(int value, int min, int max, int inMin = 0, int inMax = 100)
{
  return (value - inMin) * (max - min) / (inMax - inMin) + min;
}