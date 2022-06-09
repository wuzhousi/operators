# readme

[toc]

## 项目结构

```bash
.
├── CMakeLists.txt
├── img
│   ├── lena_1080_1920.jpg
│   ├── lena_1280_720.jpg
│   ├── lena_1920_1080.jpg
│   ├── lena_2048_2048.jpg
│   ├── lena_360_640.jpg
│   ├── lena_640_360.jpg
│   └── lena_720_1280.jpg
├── include
│   ├── allocator.h
│   ├── convert_data_structure.h
│   ├── mini_mat.h
│   └── vision_pre_post_ops.h 
├── readme.md
└── src
    ├── allocator.cc // 内存分配
    ├── convert_data_structure.cc // cv::mat 与 mini_mat 相互转换
    ├── main.cc // benckmark
    ├── mini_mat.cc // 向量存储数据结构
    └── vision_pre_post_ops.cc // 视觉预处理和后处理算子
```



## ToDoList

### 前后处理算子

#### 功能初步实现

- [ ] 视觉前后处理算子
	- [x] crop：在指定位置裁剪给定大小图像。
	- [x] flip：翻转给定的图像。（水平、垂直）
	- [x] pad：用给定的“pad”大小，扩展给定图像边缘。
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
- [ ] 文本前后处理算子
	- [ ] todo 

#### 性能优化

- [ ] 视觉前后处理算子优化
	- [x] crop：在指定位置裁剪给定大小图像。（正在进行）
	- [x] flip：翻转给定的图像。（水平、垂直）（正在进行）
	- [x] pad：用给定的“pad”大小，扩展给定图像边缘。（正在进行）
	- [ ] normalize: 用均值和标准差对图像进行归一化。
	- [ ] rotate: 按角度旋转图像。
	- [ ] perspective：透视变换。
	- [ ] affine：仿射变换。
	- [ ] rgb_to_gray：将图像转换为灰度。（正在进行）
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
2022-06-09T10:23:41+08:00
Running ./test_ops
Run on (8 X 2000 MHz CPU s)
CPU Caches:
  L1 Data 48 KiB (x4)
  L1 Instruction 32 KiB (x4)
  L2 Unified 512 KiB (x4)
  L3 Unified 6144 KiB (x1)
Load Average: 2.21, 2.54, 2.54
------------------------------------------------------------------------------
Benchmark                                    Time             CPU   Iterations
------------------------------------------------------------------------------
BenchFlipVert/360/640                    33093 ns        32164 ns        20068
BenchFlipVert/640/360                    24156 ns        23709 ns        29219
BenchFlipVert/720/1280                  134830 ns       128763 ns         5998
BenchFlipVert/1280/720                  104030 ns       101326 ns         7026
BenchFlipVert/1080/1920                 379291 ns       371580 ns         1804
BenchFlipVert/1920/1080                 348424 ns       342775 ns         2071
BenchCVFlipVert/360/640                  31609 ns        31613 ns        22244
BenchCVFlipVert/640/360                  28418 ns        28425 ns        25062
BenchCVFlipVert/720/1280                150554 ns       150525 ns         4666
BenchCVFlipVert/1280/720                148396 ns       148358 ns         4568
BenchCVFlipVert/1080/1920              1183785 ns      1183796 ns          543
BenchCVFlipVert/1920/1080              1118201 ns      1118089 ns          575
BenchFlipHoriz/360/640                  159173 ns       152720 ns         4951
BenchFlipHoriz/640/360                  138749 ns       137923 ns         4974
BenchFlipHoriz/720/1280                 592662 ns       578600 ns         1287
BenchFlipHoriz/1280/720                 558672 ns       554113 ns         1279
BenchFlipHoriz/1080/1920               1287478 ns      1274701 ns          491
BenchFlipHoriz/1920/1080               1289786 ns      1267743 ns          534
BenchCVFlipHoriz/360/640                 41069 ns        41067 ns        16364
BenchCVFlipHoriz/640/360                 32972 ns        32988 ns        20648
BenchCVFlipHoriz/720/1280               175144 ns       175190 ns         4028
BenchCVFlipHoriz/1280/720               167372 ns       167395 ns         3958
BenchCVFlipHoriz/1080/1920             1217975 ns      1217956 ns          540
BenchCVFlipHoriz/1920/1080             1147388 ns      1147605 ns          615
BenchCrop/50/50/360/640                  55082 ns        53809 ns        13558
BenchCrop/100/100/640/360                29890 ns        29693 ns        23930
BenchCrop/150/150/720/1280              219363 ns       216620 ns         3292
BenchCrop/200/200/1280/720              126932 ns       122123 ns         5992
BenchCrop/50/50/1080/1920               483855 ns       468931 ns         1544
BenchCrop/50/50/1920/1080               340905 ns       336985 ns         2091
BenchCVCrop/50/50/360/640                 29.9 ns         29.9 ns     21452782
BenchCVCrop/100/100/640/360               30.2 ns         30.2 ns     23523402
BenchCVCrop/150/150/720/1280              29.4 ns         29.4 ns     23261687
BenchCVCrop/200/200/1280/720              32.0 ns         31.9 ns     23315380
BenchCVCrop/50/50/1080/1920               30.1 ns         30.1 ns     23173053
BenchCVCrop/50/50/1920/1080               29.7 ns         29.7 ns     23064098
BenchPad/50/50/50/50/360/640             46662 ns        43096 ns        17573
BenchPad/100/100/100/100/640/360         27907 ns        27514 ns        23880
BenchPad/150/150/150/150/720/1280       145148 ns       140996 ns         5358
BenchPad/200/200/200/200/1280/720       104006 ns       101248 ns         7102
BenchPad/50/50/50/50/1080/1920          368357 ns       363008 ns         1941
BenchPad/50/50/50/50/1920/1080          342880 ns       337792 ns         2070
BenchCVPad/50/50/50/50/360/640          117214 ns       116893 ns         5856
BenchCVPad/100/100/100/100/640/360       48098 ns        48087 ns        13254
BenchCVPad/150/150/150/150/720/1280     949824 ns       949524 ns          738
BenchCVPad/200/200/200/200/1280/720     993732 ns       993395 ns          658
BenchCVPad/50/50/50/50/1080/1920       1606351 ns      1605190 ns          379
BenchCVPad/50/50/50/50/1920/1080       1536538 ns      1535861 ns          452
```

