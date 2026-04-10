#include "array.h"
int get_max_brightness(int img[HEIGHT][WIDTH])
{
	int max_brightness = 0; // 최대 밝기를 저장할 변수 초기화
	// 2차원 배열을 순회하여 최대 밝기를 찾음
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (img[i][j] > max_brightness) {
				max_brightness = img[i][j]; // 최대 밝기 업데이트
			}
		}
	}
	return max_brightness; // 최대 밝기 반환
}