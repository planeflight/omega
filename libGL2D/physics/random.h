#ifndef _LIBGL2D_PHYSICS_RANDOM_H_
#define _LIBGL2D_PHYSICS_RANDOM_H_

#include <vector>

namespace libgl {
namespace randlib {
/**
 * @param min inclusive min value
 * @param max exclusive max value
 * @return randint int in [min, max)
 */
int RandInt(int min, int max);

float RandFloat(float min, float max);

void SeedTime();

template <typename T>
T &RandChoice(T *arr, int size) {
	return arr[RandInt(0, size)];
}

template <typename T>
T &RandChoice(const std::vector<T> &vec) {
	return vec[RandInt(0, vec.size())];
}
}  // namespace randlib
}  // namespace libgl

#endif  // _LIBGL2D_PHYSICS_RANDOM_H_
