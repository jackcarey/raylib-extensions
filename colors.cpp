#include "raylib_extensions.h"
#include "raygui.h"

/* Equal to operator for the Color class */
bool operator==(const Color& lhs, const Color& rhs) {
	if (lhs.a != rhs.a)return false;
	if (lhs.r != rhs.r)return false;
	if (lhs.g != rhs.g)return false;
	if (lhs.b != rhs.b)return false;
	return true;
};
bool operator!=(const Color& lhs, const Color& rhs) {
	return !(lhs == rhs);
};

/*Addition and subtraction for colours */
Color operator+(const Color& lhs, const Color& rhs) {
	return {
		(unsigned char)(lhs.r + rhs.r),
		(unsigned char)(lhs.g + rhs.g),
		(unsigned char)(lhs.b + rhs.b),
		(unsigned char)(lhs.a + rhs.a)
	};
};
Color operator-(const Color& lhs, const Color& rhs) {
	return {
		(unsigned char)(lhs.r - rhs.r),
		(unsigned char)(lhs.g - rhs.g),
		(unsigned char)(lhs.b - rhs.b),
		(unsigned char)(lhs.a - rhs.a)
	};
};

//check if two colours are similar to each other using weighted euclidean distances
bool ColorsAreSimilar(Color& c1, Color& c2, float tolerancePC) {
	assert(tolerancePC >= 0);
	assert(tolerancePC <= 1);
	if (c1 == c2) return true;
	float sRGBDistance = ColorDistance(c1, c2);
	std::cout << c1 << " | " << c2 << " | " << (int)sRGBDistance << " /" << (int)(255 * tolerancePC) << "\n";
	if (sRGBDistance <= 255 * tolerancePC) {
		if (sRGBDistance > 0) {
			//since this sRGB distance doesn't account for brightness well
			// we must also check the difference in brightness of the two colours
			//is not too great
			std::cout << std::abs(ColorBrightness(c1) - ColorBrightness(c2)) << "\n";
			return std::abs(ColorBrightness(c1) - ColorBrightness(c2)) < 20;
		}else{
			//there are some edge cases where the distance between two distinct colours is considered zero.
			// When this occurs we must compare each RGB channel individually
			float upperMultiplier = 1 + tolerancePC;
			float lowerMultiplier = 1 - tolerancePC;	
			//only when all channels are within range of each other will the colours be similar.
			//if statements written like this for legibility
			if (c1.r >= c2.r * lowerMultiplier && c1.r <= c2.r * upperMultiplier) {
				if (c1.g >= c2.g * lowerMultiplier && c1.g <= c2.g * upperMultiplier) {
					if (c1.b >= c2.b * lowerMultiplier && c1.b <= c2.b * upperMultiplier) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

float ColorDistance(Color& c1, Color& c2) {
	//see Wikipedia - Color_difference
	float redMean = (c1.r + c2.r) / 2;
	float component1 = 2 + (redMean / 256);
	float redDiff = (std::abs(c2.r - c1.r) ^ 2) + 4;
	float greenDiff = std::abs(c2.g - c1.g) + (2 + (255 - redMean) / 256);
	float blueDiff = std::abs(c2.b - c1.b) ^ 2;
	float distanceSq = component1 * redDiff * greenDiff * blueDiff;
	return std::sqrt(distanceSq);
}

float ColorBrightness(Color& c) {
	//see Wikipedia - Relative_luminance
	return (0.2126 * c.r + 0.7152 * c.g + 0.0722 * c.b);
}
