#include<iostream>
#include <cstring>

#include<opencv2/opencv.hpp>
#include <benchmark/benchmark.h>

#include "mini_mat.h"
#include "convert_data_structure.h"
#include "vision_pre_post_ops.h"

static void BenchCVFlipVert(benchmark::State& state){
  std::string file_name = "lena_" + std::to_string(state.range(0)) + "_"+ std::to_string(state.range(1)) +".jpg";
  std::string img_path = "../img/" + file_name;
  std::string save_path = "../result/cv_flip_vert_" + file_name;
  cv::Mat img = cv::imread(img_path, cv::IMREAD_COLOR);
  for (auto _ : state){
    state.PauseTiming();
    cv::Mat img_flipv;
    state.ResumeTiming();
    cv::flip(img, img_flipv, 0);
  }
  cv::Mat img_flipv;
  cv::flip(img, img_flipv, 0);
  cv::imwrite(save_path, img_flipv);
}

static void BenchCVFlipHoriz(benchmark::State& state){
  std::string file_name = "lena_" + std::to_string(state.range(0)) + "_"+ std::to_string(state.range(1)) +".jpg";
  std::string img_path = "../img/" + file_name;
  std::string save_path = "../result/cv_flip_horiz_" + file_name;
  cv::Mat img = cv::imread(img_path, cv::IMREAD_COLOR);
  for (auto _ : state){
    state.PauseTiming();
    cv::Mat img_fliph;
    state.ResumeTiming();
    cv::flip(img, img_fliph, 1);
  }
  cv::Mat img_fliph;
  cv::flip(img, img_fliph, 1);
  cv::imwrite(save_path, img_fliph);
}

static void BenchCVCrop(benchmark::State& state){
  int x = state.range(0);
  int y = state.range(1);
  int w = state.range(2);
  int h = state.range(3);
  std::string img_path = "../img/lena_2048_2048.jpg";
  std::string save_path = "../result/cv_crop_lena_" + std::to_string(x) + "_"+ std::to_string(y) + "_"+ std::to_string(w) + "_"+ std::to_string(h) + ".jpg";
  cv::Mat img = cv::imread(img_path, cv::IMREAD_COLOR);
  cv::Rect roi(x, y, w, h);
  for (auto _ : state){
    cv::Mat crop;
    crop = img(roi);
  }
  cv::Mat crop;
  crop = img(roi);
  cv::imwrite(save_path,crop);
}

static void BenchCVPad(benchmark::State& state){
  int pad_top = state.range(0);
  int pad_bottom = state.range(1);
  int pad_left = state.range(2);
  int pad_right = state.range(3);
  int w = state.range(4);
  int h = state.range(5);
  std::string img_path = "../img/lena_" + std::to_string(w) + "_" + std::to_string(h) + ".jpg";
  std::string save_path = "../result/pad_leftena_" + std::to_string(pad_top) + "_"+ std::to_string(pad_bottom) + "_"+  std::to_string(pad_left) + "_"+ std::to_string(pad_right) + "_"+ std::to_string(w) + "_"+ std::to_string(h) + ".jpg";
  cv::Mat img = cv::imread(img_path, cv::IMREAD_COLOR);
  for (auto _ : state){
    cv::Mat pad;
    cv::copyMakeBorder(img, pad, pad_top, pad_bottom, pad_left, pad_right, cv::BORDER_CONSTANT, cv::Scalar(0));
  }
  cv::Mat pad;
  cv::copyMakeBorder(img, pad, pad_top, pad_bottom, pad_left, pad_right, cv::BORDER_CONSTANT, cv::Scalar(0));
  cv::imwrite(save_path, pad);
}

static void BenchFlipVert(benchmark::State& state){
  std::string file_name = "lena_" + std::to_string(state.range(0)) + "_"+ std::to_string(state.range(1)) +".jpg";
  std::string img_path = "../img/" + file_name;
  std::string save_path = "../result/flip_vert_" + file_name;
  cv::Mat img = cv::imread(img_path, cv::IMREAD_COLOR);
  MiniMat m1(img.cols, img.rows, 3, 1, BGR);
  MiniMat m2(img.cols, img.rows, 3, 1, BGR);
  unsigned char data_type;
  FromCVRGBOrBGR(img.data, m1, data_type);
  for (auto _ : state){
    FlipVert(m1.data, m1.w, m1.h, m1.c, m1.elemsize, m1.cstep, m2.data);
  }
  ToCVRGBOrBGR(img.data, m2, data_type);
  cv::imwrite(save_path, img);
}

static void BenchFlipHoriz(benchmark::State& state){
  std::string file_name = "lena_" + std::to_string(state.range(0)) + "_"+ std::to_string(state.range(1)) +".jpg";
  std::string img_path = "../img/" + file_name;
  std::string save_path = "../result/flip_horiz_" + file_name;
  cv::Mat img = cv::imread(img_path, cv::IMREAD_COLOR);
  MiniMat m1(img.cols, img.rows, 3, 1, BGR);
  MiniMat m2(img.cols, img.rows, 3, 1, BGR);
  unsigned char data_type;
  FromCVRGBOrBGR(img.data, m1, data_type);
  for (auto _ : state){
    FlipHoriz(m1.data, m1.w, m1.h, m1.c, m1.elemsize, m1.cstep, m2.data);
  }
  ToCVRGBOrBGR(img.data, m2, data_type);
  cv::imwrite(save_path, img);
}

static void BenchCrop(benchmark::State& state){
  int x = state.range(0);
  int y = state.range(1);
  int w = state.range(2);
  int h = state.range(3);
  std::string img_path = "../img/lena_2048_2048.jpg";
  std::string save_path = "../result/crop_lena_" + std::to_string(x) + "_"+ std::to_string(y) + "_"+ std::to_string(w) + "_"+ std::to_string(h) + ".jpg";
  cv::Mat img = cv::imread(img_path, cv::IMREAD_COLOR);
  MiniMat m1(img.cols, img.rows, 3, 1, BGR);
  MiniMat m2(w, h, 3, 1, BGR);
  unsigned char data_type;
  FromCVRGBOrBGR(img.data, m1, data_type);
  for (auto _ : state){
    Crop(m1.data, m1.w, m1.h, m1.c, m1.elemsize, m1.cstep, m2.data, x, y, m2.w, m2.h, m2.cstep);
  }
  cv::Mat img2(h, w, CV_8UC3);
  ToCVRGBOrBGR(img2.data, m2, data_type);
  cv::imwrite(save_path, img2);
}

static void BenchPad(benchmark::State& state){
  int pad_top = state.range(0);
  int pad_bottom = state.range(1);
  int pad_left = state.range(2);
  int pad_right = state.range(3);
  int w = state.range(4);
  int h = state.range(5);
  std::string img_path = "../img/lena_" + std::to_string(w) + "_" + std::to_string(h) + ".jpg";
  std::string save_path = "../result/pad_leftena_" + std::to_string(pad_top) + "_"+ std::to_string(pad_bottom) + "_"+  std::to_string(pad_left) + "_"+ std::to_string(pad_right) + "_"+ std::to_string(w) + "_"+ std::to_string(h) + ".jpg";
  cv::Mat img = cv::imread(img_path, cv::IMREAD_COLOR);
  MiniMat m1(img.cols, img.rows, 3, 1, BGR);
  MiniMat m2(img.cols+pad_left+pad_right, img.rows+pad_top+pad_bottom, 3, 1, BGR);
  unsigned char data_type;
  FromCVRGBOrBGR(img.data, m1, data_type);
  for (auto _ : state){
    Pad(m1.data, m1.w, m1.h, m1.c, m1.elemsize, m1.cstep, m2.data, pad_top, pad_bottom, pad_left, pad_right, m2.w, m2.h, m2.cstep);
  }
  cv::Mat img2(h+pad_top+pad_bottom, w+pad_left+pad_right, CV_8UC3);
  ToCVRGBOrBGR(img2.data, m2, data_type);
  cv::imwrite(save_path, img2);
}

BENCHMARK(BenchFlipVert)->Args({360, 640})->Args({640, 360})->Args({720, 1280})->Args({1280, 720})->Args({1080, 1920})->Args({1920, 1080});
BENCHMARK(BenchCVFlipVert)->Args({360, 640})->Args({640, 360})->Args({720, 1280})->Args({1280, 720})->Args({1080, 1920})->Args({1920, 1080});
BENCHMARK(BenchFlipHoriz)->Args({360, 640})->Args({640, 360})->Args({720, 1280})->Args({1280, 720})->Args({1080, 1920})->Args({1920, 1080});
BENCHMARK(BenchCVFlipHoriz)->Args({360, 640})->Args({640, 360})->Args({720, 1280})->Args({1280, 720})->Args({1080, 1920})->Args({1920, 1080});
BENCHMARK(BenchCrop)->Args({50, 50, 360, 640})->Args({100, 100, 640, 360})->Args({150, 150, 720, 1280})->Args({200, 200, 1280, 720})->Args({50, 50, 1080, 1920})->Args({50, 50, 1920, 1080});
BENCHMARK(BenchCVCrop)->Args({50, 50, 360, 640})->Args({100, 100, 640, 360})->Args({150, 150, 720, 1280})->Args({200, 200, 1280, 720})->Args({50, 50, 1080, 1920})->Args({50, 50, 1920, 1080});
BENCHMARK(BenchPad)->Args({50, 50, 50, 50, 360, 640})->Args({100, 100, 100, 100, 640, 360})->Args({150, 150, 150, 150, 720, 1280})->Args({200, 200, 200, 200, 1280, 720})->Args({50, 50, 50, 50, 1080, 1920})->Args({50, 50, 50, 50, 1920, 1080});
BENCHMARK(BenchCVPad)->Args({50, 50, 50, 50, 360, 640})->Args({100, 100, 100, 100, 640, 360})->Args({150, 150, 150, 150, 720, 1280})->Args({200, 200, 200, 200, 1280, 720})->Args({50, 50, 50, 50, 1080, 1920})->Args({50, 50, 50, 50, 1920, 1080});


BENCHMARK_MAIN();
