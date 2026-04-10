#pragma once

//이미지 크기 정의
#define HEIGHT 8
#define WIDTH 8

//2차원 이미지에서 최대 밝기를 찾아 반환하는 함수 선언
int	get_max_brightness(int img[HEIGHT][WIDTH]);