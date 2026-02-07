#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <time.h>

typedef struct Vector2 {
	float x;
	float y;
}Vector2;

class common {
public:
	// 乱数生成補助(float)
	static float RandHelperFloat(float min, float max) {
		return min + (max - min) * (rand() / (float)RAND_MAX);
	}

	// 乱数生成補助(int)
	static int RandHelperInt(int min, int max) {
		return min + rand() % (max - min + 1);
	}

	// 円同士の衝突判定
	static bool IsHitCirle(
		const Vector2& aPos, float aRadius,
		const Vector2& bPos, float bRadius
	){
		// 距離計算
		float dx = aPos.x - bPos.x;
		float dy = aPos.y - bPos.y;
		float distance = sqrtf(dx * dx + dy * dy);

		return distance <= (aRadius + bRadius);
	}
};