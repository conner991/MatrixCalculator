/*---------------------------------------------------------------------------------------------------------
FILE NAME:		   Matrix.cpp

DESCRIPTION:	           Implementation file for matrix_math.cpp. Contains member function for both 
                           the Matrix and Matrix_ops classes.

USAGE:			   Used in conjunction with the Matrix.h specification file for the driver class (matrix_math.cpp).

COMPILER:		   GNU g++ compiler on Linux

NOTES:             

MODIFICATION HISTORY:

Author	 		    Date	           Version
---------------          ----------		 -------------
Conner Fissell		 2019-11-25	 1.0 - Adapted material from Lab7. 
Conner Fissell           2019-12-02      1.1 - Assignment operator. Fixed overloaded input >> operator.
Conner Fissell           2019-12-03      1.2 - Added more to the Assignment operator function. Wrote the 
                                               basic outlines for the overloaded + and - operator functions.
Conner Fissell           2019-12-04      1.3 - Added initializer to 0 for loop inside of the overloaded 
                                               Constructor for multiplication. Fixed the addition function.
Conner Fissell           2019-12-05      1.4 - Started working on the logic for the matrix multiplication function.
                                               Added a second multiplication function for scalars. Added the scalar 
                                               division function.
Conner Fissell           2019-12-06      1.5 - Fleshed out the multiplication and equality functions.
Conner Fissell           2019-12-07      1.6 - Added finishing comments and notes.

------------------------------------------------------------------------------------------------------------*/
#include "Matrix.h"

/* -----------------------------------------------------------------------------
FUNCTION:          Matrix ()
DESCRIPTION:       Default Constructor
RETURNS:           Nothing
NOTES:             
------------------------------------------------------------------------------- */
template <class T>
Matrix<T>::Matrix()
{
    rows = 0;
    cols = 0;

    array = NULL;

    #ifdef TEST
    cout << "Default Constructor USED: ";
    cout << rows << " X " << cols << endl;
    #endif

}


/* -----------------------------------------------------------------------------
FUNCTION:          Matrix (int n_rows, int n_cols)
DESCRIPTION:       Overloaded Constructor
RETURNS:           Nothing
NOTES:             
------------------------------------------------------------------------------- */
template <class T>
Matrix<T>::Matrix(int n_rows, int n_cols)
{
    rows = n_rows;
    cols = n_cols;

    array = new T *[rows];

    for (int i = 0; i < rows; i++)
    {
        array[i] = new T[cols];
        for (int j = 0; j < cols; ++j)
        {
            array[i][j] = 0;
        }
    }

    #ifdef TEST
    cout << "Matrix Constructor USED: ";
    cout << rows << " X " << cols << endl;
    #endif

}

/* -----------------------------------------------------------------------------
FUNCTION:          Matrix (const Matrix<T> &mat1)
DESCRIPTION:       Copy Constructor
RETURNS:           Nothing
NOTES:             
------------------------------------------------------------------------------- */
template <class T>
Matrix<T>::Matrix (const Matrix<T> &mat1)
{
    rows = mat1.rows;
    cols = mat1.cols;

    array = new T *[rows];

    for (int i = 0; i < rows; i++)
    {
        array[i] = new T[cols];

        for(int j = 0; j < cols; j++)
        {
            array[i][j] = mat1.array[i][j];
        }
    }

    #ifdef TEST
    cout << "Copy Constructor USED: ";
    cout << rows << " X " << cols << endl;
    #endif

}

/* -----------------------------------------------------------------------------
FUNCTION:          ~Matrix ()
DESCRIPTION:       Destructor  
RETURNS:           Nothing
NOTES:             
-------------------------------------------------------------------------------*/
template <class T>
Matrix<T>::~Matrix ()
{
    for (int i = 0; i < rows; i++)
        delete [] array[i];

    delete [] array;

    #ifdef TEST
    cout << "Destructor USED\n";
    #endif

}

/* -----------------------------------------------------------------------------
FUNCTION:          operator >> (istream &strm, Matrix<T> &mat1)
DESCRIPTION:       Overloaded >> operator function.
RETURNS:           strm
NOTES:             
------------------------------------------------------------------------------- */
template <class T>
istream& operator >> (istream &strm, Matrix<T> &mat1)
{
    char x;
    int m, n;

    strm >> m >> x >> n;
    Matrix<T> mat(m, n);

    #ifdef TEST
    cout << "\nInput operator >>\n\n" >> endl;
    #endif

    for (int i = 0; i < mat.rows; i++)
    {
        for (int j = 0; j < mat.cols; j++)
        {
            strm >> mat.array[i][j];
        }
    }

    mat1 = mat;

    return strm;

}
/* -----------------------------------------------------------------------------
FUNCTION:          operator << (ostream &strm, const Matrix<T> &mat1)
DESCRIPTION:       Overloaded << operator function. 
RETURNS:           strm
NOTES:             
------------------------------------------------------------------------------- */
template <class T> 
ostream& operator << (ostream &strm, const Matrix<T> &mat1)
{   
    strm << "__________"  << mat1.rows << "  X  " << mat1.cols << "__________" << endl << endl;

    for (int i = 0; i < mat1.rows; i++)
    {
        for (int j = 0; j < mat1.cols; j++)
        {
            strm << setw(7) << mat1.array[i][j]; 
        }
    
        strm << endl;
    }

    return strm;
}

/* -----------------------------------------------------------------------------
FUNCTION:          operator = (const Matrix<T> &mat1)
DESCRIPTION:       Overloaded = operator function. Makes the matrix on the left 
                   the same as the one of the right.
RETURNS:           *this
NOTES:             
------------------------------------------------------------------------------- */
template <class T>
Matrix<T>& Matrix<T>::operator = (const Matrix<T> &mat1)
{   
    for (int n = 0; n < rows; n++)
    {
        delete [] array[n];
    }
    delete [] array;

    rows = mat1.rows;
    cols = mat1.cols;

    array = new T *[rows];      // pointer to pointer = a new int pointer allocation, creating an array of pointers 

    #ifdef TEST
    cout << "Assignment op = " << rows << " X " << cols << endl;
    #endif

    for (int i = 0; i < rows; i++)
    {   
        array[i] = new T [cols];            // Setting each of those pointers to an actual array, allocating actual
        for (int j = 0; j < cols; j++)
        {
            array[i][j] = mat1.array[i][j];      
        }
    }

    return *this;

}

/* -----------------------------------------------------------------------------
FUNCTION:          operator + (const Matrix_ops<T> &mat1)
DESCRIPTION:       Overloaded + operator function. Adds two matrices together. 
RETURNS:           mat2
NOTES:             
------------------------------------------------------------------------------- */
template <class T>
Matrix_ops<T> Matrix_ops<T>::operator + (const Matrix_ops<T> &mat1)
{
    if (rows != mat1.rows || cols != mat1.cols)
    {
        cout << "\nInvalid Dimensions\n\n";
        Matrix_ops<T> mat2;
        return mat2;
    }

    Matrix_ops<T> mat2(rows, cols);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            mat2.array[i][j] = array[i][j] + mat1.array[i][j];
        }
    }

    return mat2;

}

/* -----------------------------------------------------------------------------
FUNCTION:          operator - (const Matrix_ops<T> &mat1)
DESCRIPTION:       Overloaded - operator function. Subtracts one matrix from another.
RETURNS:           mat2
NOTES:             
------------------------------------------------------------------------------- */
template <class T>
Matrix_ops<T> Matrix_ops<T>::operator - (const Matrix_ops<T> &mat1)
{
    if (rows != mat1.rows || cols != mat1.cols)
    {
        cout << "\nInvalid Dimensions\n\n";
        Matrix_ops<T> mat2;
        return mat2;
    }

    Matrix_ops<T> mat2(rows, cols);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            mat2.array[i][j] = array[i][j] - mat1.array[i][j];
        }
    }

    return mat2;
}

/* -----------------------------------------------------------------------------
FUNCTION:          operator * (const Matrix_ops<T> &mat1)
DESCRIPTION:       Overloaded * operator function. Multiplies two matrices together
                   if they both have valid dimensions.
RETURNS:           mat2
NOTES:             
------------------------------------------------------------------------------- */
template <class T>
Matrix_ops<T> Matrix_ops<T>::operator * (const Matrix_ops<T> &mat1)
{   
    T sum = 0;

    if (cols != mat1.rows)
    {
        cout << "Invalid Multiplication Dimensions\n\n";
        Matrix_ops<T> mat2;
        return mat2;
    }

    Matrix_ops<T> mat2(rows, mat1.cols);

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < mat1.cols; ++j)
        {   
            
            for (int k = 0; k < mat1.rows; ++k)
            {
                sum += (array[i][k] * mat1.array[k][j]);
            }

            mat2.array[i][j] = sum;
            sum = 0;
        }
    }

    return mat2;
    
}

/* -----------------------------------------------------------------------------
FUNCTION:          operator * (int scalar)
DESCRIPTION:       Overloaded * operator function for scalar multiplication.
RETURNS:           mat1
NOTES:             
------------------------------------------------------------------------------- */
template <class T>
Matrix_ops<T> Matrix_ops<T>::operator * (int scalar)
{   
    Matrix_ops<T> mat1(rows, cols);
    
    for (int i = 0; i < rows; ++i)
    {   
        for (int j = 0; j < cols; ++j)
        {
            mat1.array[i][j] = array[i][j] * scalar;
        }
    }

    return mat1;
}

/* -----------------------------------------------------------------------------
FUNCTION:          operator / (double scalar)
DESCRIPTION:       Overloaded / operator function. Divides a matrix by a scalar double value. 
RETURNS:           mat1 
NOTES:             
------------------------------------------------------------------------------- */
template<class T>
Matrix_ops<T> Matrix_ops<T>::operator / (double scalar)
{
    Matrix_ops<T> mat1(rows, cols);
    
    for (int i = 0; i < rows; ++i)
    {   
        for (int j = 0; j < cols; ++j)
        {
            mat1.array[i][j] = array[i][j] * (1 / scalar);
        }
    }

    return mat1;
}
/* -----------------------------------------------------------------------------
FUNCTION:          operator == (const Matrix_ops<T> &mat)
DESCRIPTION:       Overloaded == operator function. Tests for equality of two matrices.
RETURNS:           equality (bool)
NOTES:             
------------------------------------------------------------------------------- */
template<class T>
bool Matrix_ops<T>::operator == (const Matrix_ops<T> &mat1)
{
    bool equality;

    if (rows != mat1.rows && cols != mat1.cols)
    {
        cout << "\nThese two matrices are NOT equal.\n\n";
        equality = 0;
        return equality;
    }

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            if (array[i][j] != mat1.array[i][j])
            {
                equality = 0;
                return equality;
            }

        }
    }

    equality = 1;
    return equality;
    
}
