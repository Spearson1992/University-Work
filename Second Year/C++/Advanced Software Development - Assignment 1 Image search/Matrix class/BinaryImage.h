#ifndef binaryImage_h
#define binaryImage_h
#include "matrix.h"
class binaryImage : public Matrix<unsigned char>
{
public:
    binaryImage(int M, int N, double *input_data, unsigned char thresh);
    binaryImage(const  Matrix<unsigned char> & input);
    binaryImage(const binaryImage &);
    binaryImage(const int M, const int N, unsigned char thresh);
    binaryImage();
    void set(int i, int j, unsigned char input);
    void setNoCheck(int i, int j, unsigned char input);
    void setThresh(unsigned char thresh);

    binaryImage operator+(const binaryImage&);
    binaryImage operator-(const binaryImage&);
    binaryImage operator*(const binaryImage&);

private:
    unsigned char _thresh;
};
#endif