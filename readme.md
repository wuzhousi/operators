# readme

[toc]

## 项目结构

```bash
.
├── CMakeLists.txt
├── main.cc
└── pre_post_ops // 前后处理算子
    ├── CMakeLists.txt
    ├── convert_data_structure.cc 
    ├── convert_data_structure.h // 第三方数据结构与MyArray互转
    ├── my_array.cc
    ├── my_array.h // MyArray数据结构，储存向量。
    ├── vision_pre_post_ops.cc
    └── vision_pre_post_ops.h // 视觉的前后处理算子
```



## ToDoList

### 前后处理算子

#### 功能初步实现

- [ ] 视觉前后处理算子
	- [x] crop：在指定位置裁剪给定大小图像。
	- [x] flip：翻转给定的图像。（水平、垂直）
	- [x] pad：用给定的“pad”大小，扩展给定图像边缘。
	- [x] erase: 在指定位置擦除给定大小图像。
	- [ ] normalize: 用均值和标准差对图像进行归一化。
	- [ ] rotate: 按角度旋转图像。
	- [ ] perspective：透视变换。
	- [ ] affine：仿射变换。
	- [x] rgb_to_gray：将图像转换为灰度。
	- [ ] invert: 反转图像的颜色。
	- [ ] posterize:通过减少每个颜色通道的位数来对图像进行后处理。
	- [ ] solarize:通过反转高于阈值的所有像素值来曝光。
	- [ ] adjust_sharpness:调整图像的清晰度。
	- [ ] adjust_contrast:调整图像的对比度。
	- [ ] adjust_gamma:对图像执行伽马校正。
	- [ ] adjust_hue:调整图像的色调。
	- [ ] adjust_saturation:调整图像的色彩饱和度。
	- [ ] equalize:
	- [ ] hsv_to_rgb
	- [ ] rgb_to_hsv
	- [ ] gaussian_blur: 高斯模糊来模糊图像。
	- [ ] resize: 将输入图像调整为给定大小。
- [ ] 文本前后处理算子
	- [ ] todo 

#### 性能优化

- [ ] 视觉前后处理算子优化
	- [ ] crop：在指定位置裁剪给定大小图像。
	- [ ] flip：翻转给定的图像。（水平、垂直）
	- [ ] pad：用给定的“pad”大小，扩展给定图像边缘。
	- [ ] erase: 在指定位置擦除给定大小图像。
	- [ ] normalize: 用均值和标准差对图像进行归一化。
	- [ ] rotate: 按角度旋转图像。
	- [ ] perspective：透视变换。
	- [ ] affine：仿射变换。
	- [ ] rgb_to_gray：将图像转换为灰度。
	- [ ] invert: 反转图像的颜色。
	- [ ] posterize:通过减少每个颜色通道的位数来对图像进行后处理。
	- [ ] solarize:通过反转高于阈值的所有像素值来曝光。
	- [ ] adjust_sharpness:调整图像的清晰度。
	- [ ] adjust_contrast:调整图像的对比度。
	- [ ] adjust_gamma:对图像执行伽马校正。
	- [ ] adjust_hue:调整图像的色调。
	- [ ] adjust_saturation:调整图像的色彩饱和度。
	- [ ] equalize:
	- [ ] hsv_to_rgb
	- [ ] rgb_to_hsv
	- [ ] gaussian_blur: 高斯模糊来模糊图像。
	- [ ] resize: 将输入图像调整为给定大小。
- [ ] 文本前后处理算子优化
	- [ ] todo 


### 深度学习算子

#### 功能初步实现
- [ ] 视觉深度学习算子
	- [ ] todo
- [ ] 文本深度学习算子
	- [ ] todo   

#### 性能优化
- [ ] 视觉深度学习算子优化
	- [ ] todo
- [ ] 文本深度学习算子优化
	- [ ] todo   

## BENCHMARK
```bash
Run on (112 X 1558.83 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x56)
  L1 Instruction 32 KiB (x56)
  L2 Unified 1024 KiB (x56)
  L3 Unified 19712 KiB (x4)
Load Average: 32.33, 28.65, 27.90
-----------------------------------------------------------
Benchmark                 Time             CPU   Iterations
-----------------------------------------------------------
BenchMyFlipH        7542946 ns      7543941 ns           90
BenchCVFlipH       20188839 ns     20188464 ns           34
BenchMyFlipV      106082238 ns    106071807 ns            7
BenchCVFlipV        1700027 ns      1701790 ns          425
BenchMyCrop          281078 ns       281186 ns         2447
BenchCVCrop            1175 ns         1180 ns       607625
BenchMyPad        124285855 ns    124262915 ns            5
BenchCVPad          5892936 ns      5894408 ns          121
BenchMyBGRToGray   97193044 ns     97185023 ns            7
BenchCVBGRToGray    2718064 ns       286480 ns         1000
```

