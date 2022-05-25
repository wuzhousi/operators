#ifndef OPERATORS_PRE_POST_OPS_VISION_PRE_POST_OPS
#define OPERATORS_PRE_POST_OPS_VISION_PRE_POST_OPS

#include<cstring>
#include<memory>
#include<iostream>
#include <algorithm>

#include "my_array.h"

enum FlipType {
  Horizontal = 0, 
  Vertical = 1,
};

void Flip(const std::unique_ptr<MyArray> & ptr, const std::unique_ptr<MyArray> & out_ptr, FlipType flip_type);

void Crop(const std::unique_ptr<MyArray> & ptr, const std::unique_ptr<MyArray> & out_ptr, int x, int y, int height, int width);

void Pad(const std::unique_ptr<MyArray> & ptr, const std::unique_ptr<MyArray> & out_ptr, int top_pad, int bottom_pad, int left_pad, int right_pad);

void Erase(const std::unique_ptr<MyArray> & ptr, const std::unique_ptr<MyArray> & out_ptr, int x, int y, int height, int width, double value);

void ConvertBGRToGray(const std::unique_ptr<MyArray> & ptr, const std::unique_ptr<MyArray> & out_ptr);

#endif