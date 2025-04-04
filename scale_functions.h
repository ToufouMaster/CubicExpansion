#pragma once
#include <iostream>

const int RARITY_POWER = 20;
const int MAX_RARITY = 4;

static double GetScaleValue(double level) {
    return pow(level, 1.3);
}

// 5.0f mean there is 5 level beetween each rarity legendary being 20 levels more powerful than a common item
double GetItemScalingValue(float level, int32_t rarity) {
    double scaling_value = GetScaleValue(level + ((float)RARITY_POWER * rarity));
    return scaling_value;
}