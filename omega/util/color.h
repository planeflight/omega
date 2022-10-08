#ifndef OMEGA_UTIL_COLOR_H
#define OMEGA_UTIL_COLOR_H

#include <glm/glm.hpp>

namespace omega::util {
namespace color {

inline glm::vec4 to_vec4(glm::u32 a) {
    unsigned char *vals = (unsigned char *)&a;
    return glm::vec4(vals[0] / 0xff, vals[1] / 0xff, vals[2] / 0xff, vals[3] / 0xff);
}

/**
 * Color constants for easier use
 */
const glm::vec4 white(1.0f, 1.0f, 1.0f, 1.0f);
const glm::vec4 black(0.0f, 0.0f, 0.0f, 1.0f);
const glm::vec4 red(1.0f, 0.0f, 0.0f, 1.0f);
const glm::vec4 green(0.0f, 1.0f, 0.0f, 1.0f);
const glm::vec4 blue(0.0f, 0.0f, 1.0f, 1.0f);
const glm::vec4 yellow(1.0f, 1.0f, 0.0f, 1.0f);

} // namespace color
} // namespace omega::util

#endif // OMEGA_UTIL_COLOR_H