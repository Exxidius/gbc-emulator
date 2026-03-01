#pragma once
#include <stdint.h>

const int GB_WIDTH = 160;
const int GB_HEIGHT = 144;
const int GB_CLOCK_SPPED = 4'194'304; // in Hz
const float GB_FRAMERATE = 59.73;
const int GB_CYCLES_PER_FRAME = GB_CLOCK_SPPED / GB_FRAMERATE;

const uint32_t GB_DARKEST_GREEN = 0x0F380FFF;
const uint32_t GB_DARK_GREEN = 0x306230FF;
const uint32_t GB_LIGHT_GREEN = 0x0BAC0FFF;
const uint32_t GB_LIGHTEST_GREEN = 0x9BBC0FFF;
