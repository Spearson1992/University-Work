#include <iostream>
#ifndef Matrix_h
#define Matrix_h
template<class T>
class Matrix
{
protected:
	T* data;
	int M, N, size;

public:
	Matrix(int sizeR, int sizeC, const T* input_data);
	Matrix(int sizeR, int sizeC, const T input_data);
	Matrix(int sizeR, int sizeC);
	Matrix(const Matrix &);
    Matrix();
	~Matrix();
	inline T get(int i, int j) const;
    inline T get(int i) const {return data[i];};
    inline T* getData() const {return data;}
    inline int getSize() const {return size;}
    void set(int i, int j, T value);
    inline void set(int i, T value) {data[i] = value;}
	inline int getRows() const {return M;} 
	inline int getColumns() const {return N;}
    double sum() const;
	Matrix getBlock(int startRow, int endRow, int startColumn, int endColumn) const;
    void setBlock(int startRow, int endRow, int startColumn, int endColumn, const T *data);
    void setBlock(int startRow, int endRow, int startColumn, int endColumn, const T data);
    void print() {for (int i = 0; i < size; i++) cout<<data[i];}

	Matrix operator + (const Matrix&) const;
	Matrix operator - (const Matrix&) const;
	Matrix operator * (const Matrix&) const;
	Matrix operator / (const Matrix&) const;
	Matrix& operator = (const Matrix&);

	Matrix& operator+=(const Matrix&);
	Matrix operator++(int);
	Matrix& operator++();
   
	T operator()(int i, int j);
};


using namespace std;
template<class T>
Matrix<T>::Matrix(int sizeR, int sizeC, const T* input_data)
	:M(sizeR), N(sizeC), size(sizeR*sizeC)
{
	data = new T[size];
	for (int i =0; i < size; i++)
		*(data+i) = *(input_data+i); 
}

template<class T>
Matrix<T>::Matrix(const Matrix &existingMatrix)
	:M(existingMatrix.M), N(existingMatrix.N), size(existingMatrix.size)
{
	data = new T[size];
	for(int i = 0; i < size; i++)
	{
		data[i] = existingMatrix.data[i];
	}
}

template<class T>
Matrix<T>::Matrix(int sizeR, int sizeC, const T input_data)
	:M(sizeR), N(sizeC), size(M*N)
{
    data = new T[size];
	for(int i = 0; i < size; i++)
	{
		data[i] = input_data;
	}
}

template<class T>
Matrix<T>::Matrix(int sizeR,int sizeC)
	:M(sizeR),N(sizeC),size(sizeR*sizeC)
{
	data = new T[size];
	for(int i = 0; i < size; i++)
	{
		data[i] = 0;
	}
}

template<class T>
Matrix<T>::Matrix()
    :M(0),N(0),size(0),data(nullptr){}

template<class T>
Matrix<T>::~Matrix()
{
	delete []data;
}

template<class T>
inline T Matrix<T>::get(int i,int j) const {return data[i*N + j];}

template<class T>
inline void Matrix<T>::set(int i, int j, T value) {data[i*N+j] = value;}

template<class T>
double Matrix<T>::sum() const
{
    double temp = 0;
    for(int i = 0; i < this->size; i++)
        temp += data[i];
    return temp;
}

template<class T>
Matrix<T> Matrix<T>::getBlock(int startRow, int endRow, int startColumn, int endColumn) const
{
	T *newData;
	const int noOfRows = (endRow-startRow);
	const int noOfColumns = (endColumn - startColumn);
	newData= new T[noOfRows*noOfColumns];

	for(int i = 0; i < noOfRows; i++)
 		for(int j =0; j < noOfColumns; j++)
			newData[i*noOfColumns + j] = this->get(startRow + i, startColumn + j);

	Matrix temp(noOfRows, noOfColumns, newData);
	delete[] newData;
	return temp;
}

template<class T>
void Matrix<T>::setBlock(int startRow, int endRow, int startColumn, int endColumn, const T *data)
{
    
	const int noOfRows = (endRow-startRow);
	const int noOfColumns = (endColumn - startColumn);
    for(int i = 0; i < noOfRows; i++)
 		for(int j =0; j < noOfColumns; j++)
            set(startRow + i,startColumn + j,data[i*noOfColumns + j]);
}

template<class T>
void Matrix<T>::setBlock(int startRow, int endRow, int startColumn, int endColumn, const T data)
{
    const int noOfRows = (endRow-startRow);
	const int noOfColumns = (endColumn - startColumn);
    for(int i = 0; i < noOfRows; i++)
 		for(int j =0; j < noOfColumns; j++)
            set(startRow + i,startColumn + j,data);
}

template<class T>
Matrix<T> Matrix<T>::operator+(const Matrix& mat) const
{
	T val = 0;
	Matrix temp(mat.M,mat.N,val);
	for(int i = 0; i < M; i++)
		for(int j = 0; j < N; j++)
		{
			val = data[i*N+j] + mat.get(i,j);
			temp.set(i,j,val);
		}
		return temp;
}

template<class T>
Matrix<T> Matrix<T>::operator-(const Matrix& mat) const
{
	T val = 0;
	Matrix temp(mat.M,mat.N,val);
	for(int i = 0; i < M; i++)
		for(int j = 0; j < N; j++)
		{
			val = data[i*N+j] - mat.get(i,j);
			temp.set(i,j,val);
		}
		return temp;
}

template<class T>
Matrix<T> Matrix<T>::operator*(const Matrix& mat) const
{
	T val = 0;
	Matrix temp(mat.M,mat.N,val);
	for(int i = 0; i < M; i++)
		for(int j = 0; j < N; j++)
		{
			val = data[i*N+j] * mat.get(i,j);
			temp.set(i,j,val);
		}
		return temp;
}

template<class T>
Matrix<T> Matrix<T>::operator/(const Matrix& mat) const
{
	Y val = 0;
	Matrix temp(mat.M,mat.N,val);
	for(int i = 0; i < M; i++)
		for(int j = 0; j < N; j++)
		{
			val = data[i*N+j] / mat.get(i,j);
			temp.set(i,j,val);
		}
		return temp;
}

template<class T>
Matrix<T>& Matrix<T>::operator=(const Matrix& input)
{
	if(this == &input)
		return *this;
	else
	{
		delete []data;
		M = input.getRows();
		N = input.getColumns();
        size = M*N;
		data = new T[M*N];
		for(int i = 0; i< M; i++)
			for(int j = 0; j < N; j++)
				set(i,j,input.get(i,j));
	}
	return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator+=(const Matrix& input)
{
	for(int i =0; i< size; i++)
		data[i] += input.data
}
template<class T>
T Matrix<T>::operator()(int i, int j)
{
    return data[i*N + j];
}

#endif