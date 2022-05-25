#include<memory>
#include<iostream>

#include<opencv2/opencv.hpp>
#include <benchmark/benchmark.h>

#include "pre_post_ops/convert_data_structure.h"
#include "pre_post_ops/vision_pre_post_ops.h"

static void BenchMyFlipH(benchmark::State& state){
  cv::Mat image = cv::imread("/root/vscode/operators/lena_sr.jpg", cv::IMREAD_COLOR);
  std::unique_ptr<MyArray> ptr = ConvertOpencvMat2MyArray(image);
  std::unique_ptr<MyArray> fliph_out_ptr = std::make_unique<MyArray>();
  for (auto _ : state){
    Flip(ptr, fliph_out_ptr, Horizontal);
    state.PauseTiming();
    fliph_out_ptr->Reset(0, 0, 0, nullptr);
    state.ResumeTiming();
  }
  Flip(ptr, fliph_out_ptr, Horizontal);
  cv::Mat image_fliph = ConvertMyArray2OpencvMat(fliph_out_ptr);
  cv::imwrite("./res_fliph.jpg", image_fliph);
}

static void BenchCVFlipH(benchmark::State& state){
  cv::Mat image = cv::imread("/root/vscode/operators/lena_sr.jpg", cv::IMREAD_COLOR);
  for (auto _ : state){
    state.PauseTiming();
    cv::Mat image_fliph;
    state.ResumeTiming();
    cv::flip(image, image_fliph, 1);
  }

  cv::Mat image_fliph;
  cv::flip(image, image_fliph, 1);
  cv::imwrite("./res_cv_fliph.jpg", image_fliph);
}

static void BenchMyFlipV(benchmark::State& state){
  cv::Mat image = cv::imread("/root/vscode/operators/lena_sr.jpg", cv::IMREAD_COLOR);
  std::unique_ptr<MyArray> ptr = ConvertOpencvMat2MyArray(image);
  std::unique_ptr<MyArray> flipv_out_ptr = std::make_unique<MyArray>();
  for (auto _ : state){
    Flip(ptr, flipv_out_ptr, Vertical);
    state.PauseTiming();
    flipv_out_ptr->Reset(0, 0, 0, nullptr);
    state.ResumeTiming();
  }
  Flip(ptr, flipv_out_ptr,  Vertical);
  cv::Mat image_flipv = ConvertMyArray2OpencvMat(flipv_out_ptr);
  cv::imwrite("./res_flipv.jpg", image_flipv);
}

static void BenchCVFlipV(benchmark::State& state){
  cv::Mat image = cv::imread("/root/vscode/operators/lena_sr.jpg", cv::IMREAD_COLOR);
  for (auto _ : state){
    state.PauseTiming();
    cv::Mat image_flipv;
    state.ResumeTiming();
    cv::flip(image, image_flipv, 0);
  }

  cv::Mat image_flipv;
  cv::flip(image, image_flipv, 0);
  cv::imwrite("./res_cv_flipv.jpg", image_flipv);
}

static void BenchMyCrop(benchmark::State& state){
  cv::Mat image = cv::imread("/root/vscode/operators/lena_sr.jpg", cv::IMREAD_COLOR);
  std::unique_ptr<MyArray> ptr = ConvertOpencvMat2MyArray(image);
  std::unique_ptr<MyArray> out_ptr = std::make_unique<MyArray>();
  for (auto _ : state){
    Crop(ptr, out_ptr, 100, 100, 100, 100);
    state.PauseTiming();
    out_ptr->Reset(0, 0, 0, nullptr);
    state.ResumeTiming();
  }
  Crop(ptr, out_ptr, 100, 100, 100, 100);
  cv::Mat image_crop = ConvertMyArray2OpencvMat(out_ptr);
  cv::imwrite("./res_crop.jpg", image_crop);
}

static void BenchCVCrop(benchmark::State& state){
  cv::Mat image = cv::imread("/root/vscode/operators/lena_sr.jpg", cv::IMREAD_COLOR);
  cv::Rect roi(100, 100, 100, 100);
  for (auto _ : state){
    state.PauseTiming();
    cv::Mat crop;
    state.ResumeTiming();
    crop = image(roi);
  }
  cv::Mat crop;
  crop = image(roi);
  cv::imwrite("./res_cv_crop.jpg", crop);
}

static void BenchMyPad(benchmark::State& state){
  cv::Mat image = cv::imread("/root/vscode/operators/lena_sr.jpg", cv::IMREAD_COLOR);
  std::unique_ptr<MyArray> ptr = ConvertOpencvMat2MyArray(image);
  std::unique_ptr<MyArray> out_ptr = std::make_unique<MyArray>();
  for (auto _ : state){
    Pad(ptr, out_ptr, 400, 400, 400, 400);
    state.PauseTiming();
    out_ptr->Reset(0, 0, 0, nullptr);
    state.ResumeTiming();
  }
  Pad(ptr, out_ptr, 400, 400, 400, 400);
  cv::Mat image_pad = ConvertMyArray2OpencvMat(out_ptr);
  cv::imwrite("./res_pad.jpg", image_pad);
}

static void BenchCVPad(benchmark::State& state){
  cv::Mat image = cv::imread("/root/vscode/operators/lena_sr.jpg", cv::IMREAD_COLOR);
  for (auto _ : state){
    state.PauseTiming();
    cv::Mat pad;
    state.ResumeTiming();
    cv::copyMakeBorder(image, pad, 400, 400, 400, 400, cv::BORDER_CONSTANT, cv::Scalar(0));
  }
  cv::Mat pad;
  cv::copyMakeBorder(image, pad, 400, 400, 400, 400, cv::BORDER_CONSTANT, cv::Scalar(0));
  cv::imwrite("./res_cv_pad.jpg", pad);
}

static void BenchMyBGRToGray(benchmark::State& state){
  cv::Mat image = cv::imread("/root/vscode/operators/lena_sr.jpg", cv::IMREAD_COLOR);
  std::unique_ptr<MyArray> ptr = ConvertOpencvMat2MyArray(image);
  std::unique_ptr<MyArray> out_ptr = std::make_unique<MyArray>();
  for (auto _ : state){
    ConvertBGRToGray(ptr, out_ptr);
    state.PauseTiming();
    out_ptr->Reset(0, 0, 0, nullptr);
    state.ResumeTiming();
  }
  ConvertBGRToGray(ptr, out_ptr);
  cv::Mat image_gray = ConvertMyArray2OpencvMat(out_ptr);
  cv::imwrite("./res_gray.jpg", image_gray);
}

static void BenchCVBGRToGray(benchmark::State& state){
  cv::Mat image = cv::imread("/root/vscode/operators/lena_sr.jpg", cv::IMREAD_COLOR);
  for (auto _ : state){
    state.PauseTiming();
    cv::Mat image_gray;
    state.ResumeTiming();
    cv::cvtColor(image, image_gray, CV_BGR2GRAY);
  }
  cv::Mat image_gray;
  cv::cvtColor(image, image_gray, CV_BGR2GRAY);
  cv::imwrite("./res_cv_gray.jpg", image_gray);
}

BENCHMARK(BenchMyFlipH);
BENCHMARK(BenchCVFlipH);
BENCHMARK(BenchMyFlipV);
BENCHMARK(BenchCVFlipV);
BENCHMARK(BenchMyCrop);
BENCHMARK(BenchCVCrop);
BENCHMARK(BenchMyPad);
BENCHMARK(BenchCVPad);
BENCHMARK(BenchMyBGRToGray);
BENCHMARK(BenchCVBGRToGray);
BENCHMARK_MAIN();

// using namespace cv;
// using namespace std;

// int main()
// {
//     Mat image = imread("/root/vscode/operators/lena_sr.jpg", IMREAD_COLOR);

//     unique_ptr<MyArray> ptr = ConvertOpencvMat2MyArray(image);

//     std::unique_ptr<MyArray> fliph_out_ptr = std::make_unique<MyArray>();
//     Flip(ptr, fliph_out_ptr, Horizontal);
//     Mat new_image_h = ConvertMyArray2OpencvMat(fliph_out_ptr);
//     imwrite("./res_hflip.jpg", new_image_h);

//     std::unique_ptr<MyArray> flipv_out_ptr = std::make_unique<MyArray>();
//     Flip(ptr, flipv_out_ptr, Vertical);
//     Mat new_image_v = ConvertMyArray2OpencvMat(flipv_out_ptr);
//     imwrite("./res_vflip.jpg", new_image_v);

//     std::unique_ptr<MyArray> crop_out_ptr = std::make_unique<MyArray>();
//     Crop(ptr, crop_out_ptr, 100, 100, 100, 100);
//     Mat new_image_c = ConvertMyArray2OpencvMat(crop_out_ptr);
//     imwrite("./res_crop.jpg", new_image_c);

//     std::unique_ptr<MyArray> pad_out_ptr = std::make_unique<MyArray>();
//     Pad(ptr, pad_out_ptr, 400, 400, 400, 400);
//     Mat new_image_p = ConvertMyArray2OpencvMat(pad_out_ptr);
//     imwrite("./res_pad.jpg", new_image_p);

//     std::unique_ptr<MyArray> erase_out_ptr = std::make_unique<MyArray>();
//     Erase(ptr, erase_out_ptr, 100, 100, 100, 100, 255);
//     Mat new_image_e = ConvertMyArray2OpencvMat(erase_out_ptr);
//     imwrite("./res_erase.jpg", new_image_e);

//     std::unique_ptr<MyArray> bgr2gray_out_ptr = std::make_unique<MyArray>();
//     ConvertBGRToGray(ptr, bgr2gray_out_ptr);
//     Mat new_image_bgr2gray = ConvertMyArray2OpencvMat(bgr2gray_out_ptr);
//     imwrite("./res_gray.jpg", new_image_bgr2gray);

//     image = ConvertMyArray2OpencvMat(ptr);
//     imwrite("./res_origin.jpg", image);

//     return 0;
// }