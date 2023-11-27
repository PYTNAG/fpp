#pragma once

// major must be in range 0-1023
// minor must be in range 0-1023
// patch must be in range 0-4095
#define MAKE_VERSION(major, minor, patch) ((((uint32_t)(major)) << 22U) | (((uint32_t)(minor)) << 12U) | ((uint32_t)(patch)))