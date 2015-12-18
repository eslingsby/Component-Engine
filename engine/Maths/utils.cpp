#include "utils.hpp"

#define _USE_MATH_DEFINES
#include <cmath>

#include <Static\DebugOutput.hpp>

#include <glm\gtc\quaternion.hpp>
#include "quat.hpp"

void mathsTesting(){
	glm::quat a0(glm::vec3(glm::radians(0.f), glm::radians(-21.f), glm::radians(324.f)));
	quat b0(vec3(glm::radians(0.f), glm::radians(-21.f), glm::radians(324.f)));

	//glm::quat a0(glm::vec3(glm::radians(10.f), glm::radians(24.f), glm::radians(32.f)));
	//quat b0(vec3(glm::radians(10.f), glm::radians(24.f), glm::radians(32.f)));

	//a0 = glm::normalize(a0);
	//b0 = normalize(b0);
		
	a0 *= a0;
	b0 *= b0;

	glm::vec3 a1 = glm::eulerAngles(glm::normalize(a0));
	vec3 b1 = eulerAngles(normalize(b0));

	a0 = glm::conjugate(a0);
	b0 = conjugate(b0);

	a1 = a0 * a1;
	b1 = b0 * b1;

	a0 = glm::inverse(a0);

	b0 = inverse(b0);
}

float radians(float a){
	return (M_PI / 180.f) * a;
}

float degrees(float a){
	return (180.f / M_PI) * a;
}

float changeRange(float oldMin, float oldMax, float newMin, float newMax, float oldValue){
	return (((oldValue - oldMin) * (newMax - newMin)) / (oldMax - oldMin)) + newMin;
}

float randomRange(int range, int spread){
	return (float)((rand() % range * spread) - (range / 2) * spread);
}

float clamp(float min, float max, float value){
	if (min > value)
		return min;

	if (value > max)
		return max;

	return value;
}