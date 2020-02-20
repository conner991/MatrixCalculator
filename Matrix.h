/*----------------------------------------------------------------------------------------------------
FILE NAME:		   Matrix.h

DESCRIPTION:	           Specification file for matrix_math.cpp

USAGE:			   Used in conjunction with the Matrix.cpp implementation file for the driver file (matrix_math.cpp).

COMPILER:		   GNU g++ compiler on Linux

NOTES:              
 
MODIFICATION HISTORY:

Author				 Date			    Version
---------------               ----------		 -------------
Conner Fissell		      2019-11-24         1.0 - Adapted material from Lab7.
Conner Fissell                2019-12-02         1.1 - Added second inherited Matrix_ops class.
Conner Fissell                2019-12-05         1.2 - Added another overloaded * operator prototype for scalar
                                                       multiplication. Added the scalar division prototype.
Conner Fissell                2019-12-06         1.3 - Added the overloaded == operator and #include <vector>
                                                       and #include <algorithm>.
 
----------------------------------------------------------------------------------------------------*/
#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

template <class T>
class Matrix
{
    protected:
        int rows;
        int cols;
        T **array;

    public:
        Matrix();                                       // Default Constructor
        Matrix(int rows, int cols); 	                // Overloaded constructor
        Matrix(const Matrix<T> &);                      // Copy Constructor 
        ~Matrix();				                        // Destructor
        Matrix<T>& operator = (const Matrix<T> &);      // Overloaded assignment
	
	template <class T1>
	friend ostream& operator << (ostream &, const Matrix<T1> &);
	template <class T1>
	friend istream& operator >> (istream &, Matrix<T1> &); 

};

template <class T>
class Matrix_ops : public Matrix<T>
{
    private:
        using Matrix<T>::rows;
        using Matrix<T>::cols;
        using Matrix<T>::array;

    public:
        // C++11 Methods
        using Matrix<T> :: Matrix;
        using Matrix<T> :: operator =;

    Matrix_ops<T> operator + (const Matrix_ops<T> &);       // Overloaded + operator function
    Matrix_ops<T> operator - (const Matrix_ops<T> &);       // Overloaded - operator function
    Matrix_ops<T> operator * (const Matrix_ops<T> &);       // Overloaded * operator function for matrices
    Matrix_ops<T> operator * (int);                         // Overloaded * operator function for scalar multiplication
    Matrix_ops<T> operator / (double);                      // Overloaded / operator function for scalar division
    bool operator == (const Matrix_ops<T> &);               // Overloaded == operator function for equality testing 

};

#endif
