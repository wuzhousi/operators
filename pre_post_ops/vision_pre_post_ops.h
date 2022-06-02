#ifndef OPERATORS_PRE_POST_OPS_VISION_PRE_POST_OPS
#define OPERATORS_PRE_POST_OPS_VISION_PRE_POST_OPS

#include<cstring>
#include<memory>
#include<iostream>
#include <algorithm>

#include<opencv2/opencv.hpp>

#include "my_array.h"

enum FlipType {
  Horizontal = 0, 
  Vertical = 1,
};

// void mflip(cv::InputArray _src, cv::OutputArray _dst, int flip_mode );

void flipVert( const uchar* src0, size_t sstep, uchar* dst0, size_t dstep, cv::Size size, size_t esz);

void flipHoriz( const uchar* src, size_t sstep, uchar* dst, size_t dstep, cv::Size size, size_t esz);

void Flip(const std::unique_ptr<MyArray> & ptr, const std::unique_ptr<MyArray> & out_ptr, FlipType flip_type);

void Crop(const std::unique_ptr<MyArray> & ptr, const std::unique_ptr<MyArray> & out_ptr, int x, int y, int height, int width);

void Pad(const std::unique_ptr<MyArray> & ptr, const std::unique_ptr<MyArray> & out_ptr, int top_pad, int bottom_pad, int left_pad, int right_pad);

void Erase(const std::unique_ptr<MyArray> & ptr, const std::unique_ptr<MyArray> & out_ptr, int x, int y, int height, int width, char value);

void ConvertBGRToGray(const std::unique_ptr<MyArray> & ptr, const std::unique_ptr<MyArray> & out_ptr);

#endif