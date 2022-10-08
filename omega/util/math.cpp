#include "math.h"

namespace glm {

bool circle_vs_circle(const glm::vec2 &center1, f32 radius1, const glm::vec2 &center2, f32 radius2) {
    auto square = [](f32 v) -> f32 { return v * v; };
    f32 dist_sq = square(center1.x - center2.x) + square(center1.y - center2.y);
    return dist_sq < square(radius1 + radius2);
}

f32 distance_sq(const glm::vec2 &p1, const glm::vec2 &p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

f32 distance_sq(const glm::vec3 &p1, const glm::vec3 &p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y) + (p1.z - p2.z) * (p1.z - p2.z);
}

} // namespace glm