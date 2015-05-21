#include "BinaryImage.h"

binaryImage::binaryImage(int M, int N, double *inputData, unsigned char thresh)
    :Matrix(M,N), _thresh(thresh)
{
    for(int i = 0; i< size; i++)
	{
        inputData[i] > thresh ? data[i] = 1: data[i] = 0;
	}
}
binaryImage::binaryImage(const Matrix<unsigned char> &input)
    :Matrix(input), _thresh(0){}

binaryImage::binaryImage(const binaryImage &input)
    :Matrix(input.M,input.N,input.data), _thresh(input._thresh){}

binaryImage::binaryImage(const int M, const int N, unsigned char thresh)
    :Matrix(M,N), _thresh(thresh){}

binaryImage::binaryImage()
    :Matrix(), _thresh(180){}

void binaryImage::set(int i, int j, unsigned char input)
{
    input > _thresh ? data[i * N + j] = 1 : data[i * N + j] = 0;
}

void binaryImage::setNoCheck(int i, int j, unsigned char input)
{
    data[i*N + j] = input;
}

void binaryImage::setThresh(unsigned char thresh)
{
    _thresh = thresh;
}


binaryImage binaryImage::operator+(const binaryImage &input)
{
    unsigned char val = 0;
    binaryImage temp(input.M,input.N, 180);
    for(int i = 0; i < M; i++)
        for(int j = 0; j < N; j++)
            temp.setNoCheck(i,j,(data[i*N+j] | input.get(i,j)));

     return temp;
}

binaryImage binaryImage::operator-(const binaryImage &input)
{
    binaryImage temp(input.M,input.N, 180);
    for(int i = 0; i < M; i++)
        for(int j = 0; j < M; j++)
            temp.setNoCheck(i,j,(data[i*N+j] ^ input.get(i,j)));
    return temp;
}

binaryImage binaryImage::operator*(const binaryImage &input)
{
    unsigned char val = 0;
    binaryImage temp(input.M, input.N, 180);
    for(int i = 0; i < M; i++)
        for(int j = 0; j < N; j++)
            temp.setNoCheck(i,j,(data[i*N+j] & input.get(i,j)));

    return temp;
}