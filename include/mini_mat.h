#ifndef MINI_MAT
#define MINI_MAT

#include<stdlib.h>

enum MatType{
    NormalMat = 0,
    RGB = 1,
    BGR = 2,
    GRAY = 3,
    RGBA = 4,
    BGRA = 5,
    NV21 = 6,
    NV12 = 7,
};

class MiniMat{
  public:
    // empty
    MiniMat();
    // dim 1
    MiniMat(int w, int elemsize, MatType mat_type);
    // dim 2
    MiniMat(int w, int h, int elemsize, MatType mat_type);
    // dim 3
    MiniMat(int w, int h, int c, int elemsize, MatType mat_type);
    // release
    ~MiniMat();
    // assigin
    MiniMat& operator=(const MiniMat& m);

    // create dim 1
    void Create(int w, int elemsize);
    // create dim 2
    void Create(int w, int h, int elemsize);
    // create dim 3
    void Create(int w, int h, int c, int elemsize);
 
    // data reference
    void* Channel(int c);

    int mat_type;
    // point to the data
    void* data;
    // element size int btyes
    // 4 = float32
    // 2 = float16
    // 1 = uint8
    // 0 = empty
    int elemsize;
    // dimension rank
    int dims;
    // weight
    int w;
    // height
    int h;
    // channel
    int c;
    // channel step
    int cstep;

};

inline MiniMat::MiniMat()
  :mat_type(NormalMat), data(0), elemsize(0), dims(0), w(0), h(0), c(0), cstep(0){

}

inline MiniMat::MiniMat(int _w, int _elemsize, MatType _mat_type)
  :mat_type(_mat_type), data(0), elemsize(_elemsize), dims(1), w(_w), h(1), c(1), cstep(w){
    Create(_w, _elemsize);
}

inline MiniMat::MiniMat(int _w, int _h, int _elemsize, MatType _mat_type)
  :mat_type(_mat_type), data(0), elemsize(_elemsize), dims(2), w(_w), h(_h), c(1), cstep(0){
    Create(_w, _h, _elemsize);
}

inline MiniMat::MiniMat(int _w, int _h, int _c, int _elemsize, MatType _mat_type)
  :mat_type(_mat_type), data(0), elemsize(_elemsize), dims(3), w(_w), h(_h), c(_c), cstep(0){
    Create(_w, _h, _c, _elemsize);
}

inline MiniMat::~MiniMat(){
    if(data!=0){
        free(data);
    }
}

#endif