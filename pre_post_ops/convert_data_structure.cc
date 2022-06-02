#include "convert_data_structure.h"

std::unique_ptr<MyArray> ConvertOpencvMat2MyArray(cv::Mat mat){
  int channels = mat.channels();
  int rows = mat.rows;
  int cols = mat.cols;
  unsigned char* array_ptr = static_cast<unsigned char*>(malloc(channels * rows * cols * sizeof(unsigned char)));
  
  std::unique_ptr<MyArray> ptr = std::make_unique<MyArray>(channels, rows, cols, array_ptr);
  
  if(channels == 3){
    for(int j=0; j<cols; j++){
      for(int i=0; i<rows; i++){
        array_ptr[0 * cols * rows + j * rows + i] = static_cast<unsigned char>(mat.at<cv::Vec3b>(i, j)[0]);
        array_ptr[1 * cols * rows + j * rows + i] = static_cast<unsigned char>(mat.at<cv::Vec3b>(i, j)[1]);
        array_ptr[2 * cols * rows + j * rows + i] = static_cast<unsigned char>(mat.at<cv::Vec3b>(i, j)[2]);
      }
    }
  }else if(channels == 1){
    for(int j=0; j<cols; j++){
      for(int i=0; i<rows; i++){
        array_ptr[0 * cols * rows + j * rows + i] = static_cast<unsigned char>(mat.at<uchar>(i, j));
      }
    }
  }

  return ptr;
}

cv::Mat ConvertMyArray2OpencvMat(const std::unique_ptr<MyArray> & ptr){
  int channels = ptr->get_channels();
  int cols = ptr->get_cols();
  int rows = ptr->get_rows();
  unsigned char* array_ptr = ptr->get_array_ptr();

  if(channels==3){
    cv::Mat mat(rows, cols, CV_8UC3);
    for(int j=0; j<cols; j++){
      for(int i=0; i<rows; i++){
        mat.at<cv::Vec3b>(i, j)[0] = static_cast<unsigned char>(array_ptr[0 * cols * rows + j * rows + i]);
        mat.at<cv::Vec3b>(i, j)[1] = static_cast<unsigned char>(array_ptr[1 * cols * rows + j * rows + i]);
        mat.at<cv::Vec3b>(i, j)[2] = static_cast<unsigned char>(array_ptr[2 * cols * rows + j * rows + i]);
      }
    }
    return mat;
  }
  else if(channels==1){
    cv::Mat mat(rows, cols, CV_8UC1);
    for(int j=0; j<cols; j++){
      for(int i=0; i<rows; i++){
        mat.at<uchar>(i, j) = static_cast<unsigned char>(array_ptr[0 * cols * rows + j * rows + i]);
      }
    }
    return mat;
  }

  cv::Mat mat(0, 0, CV_8UC1);
  return mat;
}