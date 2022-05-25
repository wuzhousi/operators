#ifndef OPERATORS_PRE_POST_OPS_CONVERT_DATA_STRUCTURE
#define OPERATORS_PRE_POST_OPS_CONVERT_DATA_STRUCTURE

#include<memory>
#include<iostream>

#include<opencv2/opencv.hpp>

#include"my_array.h"

std::unique_ptr<MyArray> ConvertOpencvMat2MyArray(cv::Mat mat);

cv::Mat ConvertMyArray2OpencvMat(const std::unique_ptr<MyArray> & ptr);

#endif