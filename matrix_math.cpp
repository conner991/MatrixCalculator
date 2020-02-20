/*---------------------------------------------------------------------------------------------------------
FILE NAME:		   matrix_math.cpp

DESCRIPTION:	   Driver file for my matrix math program.

USAGE:			   ./matrix_math -h
                   ./matrix_math -inp A
                or ./matrix_math -inp A -out C
                or ./matrix_math A + B
                or ./matrix_math A - B
                or ./matrix_math A x B
                or ./matrix_math A x n
                or ./matrix_math A / n
                or ./matrix_math -eq A B

COMPILER:		   GNU g++ compiler on Linux

NOTES:              

MODIFICATION HISTORY:

Author				             Date			    Version
---------------               ----------		 -------------
Conner Fissell		          2019-11-22		 1.0 - Basic Version adapted from Lab7
Conner Fissell                2019-12-02         1.1 - Worked on prototype functions. Updated main to work better
                                                       with addition and subtraction.
Conner Fissell                2019-12-05         1.2 - Modularized the driver by adding more functions to handle the
                                                       different types of command line prompts.
Conner Fissell                2019-12-06         1.3 - Continued adding more functions. Added the scalar multipliaction
                                                       and division functions. Created DnA_test2 () function. Took the 
                                                       ifstream and ofstream operator definitions out of main () and moved 
                                                       them into all the individual functions. Added multiplication and
                                                       equality testing functions.
Conner Fissell                2019-12-07         1.4 - Added finishing comments and notes.
----------------------------------------------------------------------------------------------------------*/
//#define TEST
//#include "Matrix.h"           // Specification file 
#include "Matrix.cpp"           // Implementation file to be compiled together

typedef unsigned char byte;

//Prototypes
void help_screen();
int open_file (ifstream&, string, int);
int write_file (ofstream&, string, int);
int arg_count (int, int, int);
int one_mat_op (int&, int, char*[]);
int file_out (int&, int, char*[]);
int eq_test(int&, int, string, string, char*[]);
int mult_mat_op (int&, int, string, char*[]);
int DnA_test (int, string);
int DnA_test2 (int, string);
int add (int, string, string);
int sub (int, string, string);
int multiply (int, string, string);
int scalar_div (double, int, string);
int scalar_mult(int, int, string);
/* -----------------------------------------------------------------------------
FUNCTION:          int main(int argc, char* argv[])
DESCRIPTION:       Reads matrix from a file, creates a Matrix object, and displays
                   it to the screen.
RETURNS:           0
NOTES:             int argc         // Number  of parameters on the command line
                   char *argv[]     // An array of pointers to C-Strings
------------------------------------------------------------------------------- */
int main(int argc, char *argv[])
{
    int error = 0;
    string file1, cmd;
 
  
    if (arg_count (argc, 2, error))
    return error;
        
    
    cmd = *++argv;  // moves over one to the right, left matrix for two, -inp for one
    cout << "argc = " << argc << "  " << *argv << endl;

    if (cmd == "-h")
    {
        help_screen();
    }

    else if (cmd == "-inp")
    {
        error = one_mat_op(argc, error, argv); 
        if (error)
        return error;  
    }

    else if (argc >= 3)
    {
        error = mult_mat_op(argc, error, cmd, argv);
        if (error)
        return error;
    }

    else 
    cout << "\nUnknown command\n\n";

    
 

    #ifdef TEST
    cout << "Copy Constructor test: Matrix<T> mat4 = mat2: " << endl;
    Matrix<double> mat4 = mat2;
    cout << mat4;
    if (outfile)
    outfile << mat4;
    #endif
    

    return 0;


}

/* -----------------------------------------------------------------------------
FUNCTION:          help_screen ()
DESCRIPTION:       Displays the help screen.
RETURNS:           Nothing (void)
NOTES:            
----------------------------------------------------------------------------- */
void help_screen ()
{
    cout << "\n              ------------HELP SCREEN--------------\n\n";
    cout << "Here are the valid command line prompts that\n";
    cout << "work with this Matrix Math program.\n";
    cout << "In the following examples, A, B and C are matrices and n is a scalar.\n\n";
    cout << "./matrix_math -h               : Displays help screen\n";
    cout << "./matrix_math -inp A           : Reads in the A.mtx file and displays it to the screen.\n";
    cout << "                               : Also displays the matrix assignment operator test\n";
    cout << "./matrix_math cmds... -out C   : Writes out result to a named output file (e.g., A.mtx).\n";
    cout << "./matrix_math A + B            : Reads in 2 matrix files and adds them together.\n";
    cout << "                               : Displays result (A + B).\n";
    cout << "./matrix_math A - B            : Reads in 2 matrix files, subtracts one from\n";
    cout << "                               : the other and displays the result (A - B).\n";
    cout << "./matrix_math A x B            : Multiplies two matrix files together and\n";
    cout << "                               : displays the result (A x B).\n";
    cout << "./matrix_math A x n            : Multiplies a matrix A by a scalar value n.\n";
    cout << "                               : Displays the result (A x N).\n";
    cout << "./matrix_math A / n            : Divides a matrix file A by a scalar value n.\n";
    cout << "                               : Displays the result (A / n).\n";
    cout << "./matrix_math -eq A B          : Reads in 2 matrix files and tests for equality\n";
    cout << "                               : (A == B).\n";
}

/* -----------------------------------------------------------------------------
FUNCTION:          open_file (ifstream &infile, string filename, int error)
DESCRIPTION:       Opens input file for use with the infile operator.
RETURNS:           error (int)
NOTES:             Returns a 1 if there was a problem opening the file.
----------------------------------------------------------------------------- */
int open_file (ifstream &infile, string filename, int error)
{
    filename += ".mtx";
    infile.open(filename);

    if (!infile)
    {
        cout << "\nError opening file: " << filename << endl << endl;
        error = 1;
    }

    else 
    cout << "Opened: " << filename << endl;

    
    return error;
}

/* -----------------------------------------------------------------------------
FUNCTION:          write_file (ofstream &outfile, string filename, int error)
DESCRIPTION:       Opens output file for use with the outfile operator.
RETURNS:           error (int)
NOTES:             Returns a 1 if there was a problem opening the file for output.
----------------------------------------------------------------------------- */
int write_file (ofstream &outfile, string filename, int error)
{
    filename += ".mtx";
    outfile.open(filename);

    if (!outfile)
    {
        cout << "\nError opening file: " << filename << endl << endl;
        error = 2;
    }
    else 
    cout << "Output: " << filename << endl;


    return error;
}

/* -----------------------------------------------------------------------------
FUNCTION:          arg_count (int argc, int num, int error)
DESCRIPTION:       Checks for minimum number of arguments.
RETURNS:           error (int)
NOTES:             Returns a 1 if there were too few arguments.
----------------------------------------------------------------------------- */
int arg_count (int argc, int num, int error)
{
    if (argc < num)
    {
        cout << "Not enough Arguments ?\n\n";
        error = 1;
    }

    return error;
}

/* -----------------------------------------------------------------------------
FUNCTION:          one_mat_op (int &argc, int error, char *argv[])
DESCRIPTION:       Handles the DnA_test() function for handling a single matrix.
RETURNS:           error (int)
NOTES:            
----------------------------------------------------------------------------- */
int one_mat_op (int &argc, int error, char *argv[])
{   
    string name1;

    error = arg_count(--argc, 1, error);
    name1 = *++argv;
            
    error = DnA_test(error, name1);

    return error;
}

/* -----------------------------------------------------------------------------
FUNCTION:          file_out (int &argc, int error, char *argv[])
DESCRIPTION:       Preparation for the write_file out function.
RETURNS:           error (int)
NOTES:            
----------------------------------------------------------------------------- */
int file_out (int &argc, int error, char *argv[])
{   
    ofstream outfile;
    string name2;

    error = arg_count(--argc, 1, error);
    name2 = *++argv;
    write_file(outfile, name2, error);

    outfile.close();

    return error;
}

/* -----------------------------------------------------------------------------
FUNCTION:          mult_mat_op (int &argc, int error, string cmd, char *argv[])
DESCRIPTION:       Handles the command line math prompts.
RETURNS:           error (int)
NOTES:             If argc >= 3. Scalar multiplication only works with single digit 
                   integers unfortunately. Also did not have time to get the output
                   file function working as well. 
----------------------------------------------------------------------------- */
int mult_mat_op (int &argc, int error, string cmd, char *argv[])
{   
    string name1, name2;
    vector<string> num = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    Matrix_ops<int> mat1, mat2, mat3;
    int scalar1;
    double scalar2;
    

    name1 = *argv;                      // is left matrix (A) + B, or (-eq) A B
    cmd = *++argv;                      // + or - or (A for -eq)
    cout << "cmd = " << cmd << endl;     
    name2 = *++argv;                    // is right matrix A + (B), or -eq A (B)
                      
    while (--argc)
    {
        if (name1 == "-eq")
        {   
            error = eq_test(argc, error, cmd, name2, argv);         // Matrix equlity test
            if (error)
            return error;
        }

        else if (cmd == "+")
        {
            error = add(error, name1, name2);       // Matrix addition
        }

        else if (cmd == "-")
        {
            error = sub(error, name1, name2);       // Matrix subtraction
        }

        else if (cmd == "x")
        {   
            //(find(begin(num), end(num), name2) == end(num)) ? cout << "1\n" : cout << "2\n";        

            if (cmd == "x" && (find(num.begin(), num.end(), name2)) != num.end())  
            {   
                scalar1 = stoi(name2);
                error = scalar_mult(scalar1, error, name1);     // Scalar multiplication

            }
            
            else
            {   
                error = multiply(error, name1, name2);         // Matrix multiplication
            }
            
        }

        else if (cmd == "/")
        {   
            scalar2 = stod(name2);
            error = scalar_div(scalar2, error, name1);          // Scalar division
        }

        else if (++argc == (4 || 5))
        {
            error = file_out(argc, error, argv);
            if (error)
            return error;
        }

        else 
        cout << "Unknown Operation\n\n";
        argc -= 2;

    }

    return error;
}

/* -----------------------------------------------------------------------------
FUNCTION:          DnA_test (int error, string name1)
DESCRIPTION:       Displays a single matrix and tests the assignment operator.
RETURNS:           error (int)
NOTES:             For integer data type
----------------------------------------------------------------------------- */
int DnA_test (int error, string name1)
{   
    ifstream infile1, infile2;
    Matrix_ops<int> mat1, mat2;

    error = open_file(infile1, name1, error);
    infile1 >> mat1;

    cout << "Input test: Matrix 1" << endl;
    cout << mat1 << endl; 
    cout << "Blank Matrix 2: " << endl;
    cout << mat2;
    cout << "Assignment test: Matrix 2 = Matrix 1: " << endl;
    mat2 = mat1;
    cout << "Matrix 2 is now: " << endl; 
    cout << mat2 << endl;

    return error;
}   

/* -----------------------------------------------------------------------------
FUNCTION:          DnA_test2 (int error, string name1)
DESCRIPTION:       Displays a single matrix and tests the assignment operator.
RETURNS:           error (int)
NOTES:             For double data type
----------------------------------------------------------------------------- */
int DnA_test2 (int error, string name1)
{   
    ifstream infile1, infile2;
    Matrix_ops<double> mat4, mat5;

    error = open_file(infile1, name1, error);
    infile1 >> mat4;

    cout << "Input test: Matrix 1" << endl;
    cout << mat4 << endl;
    cout << "Blank Matrix 2: " << endl;
    cout << mat5;
    cout << "Assignment test: Matrix 2 = Matrix 1: " << endl;
    mat5 = mat4;
    cout << "Matrix 2 is now: " << endl; 
    cout << mat5 << endl;

    return error;
}

/* -----------------------------------------------------------------------------
FUNCTION:          add (int error, string name1, string name2)
DESCRIPTION:       Adds two matrices together if they are of valid dimensions.
RETURNS:           error (int)
NOTES:             
----------------------------------------------------------------------------- */
int add (int error, string name1, string name2)
{   ifstream infile1, infile2;
    ofstream outfile;
    Matrix_ops<int> mat1, mat2, mat3;

    error = open_file(infile1, name1, error);
    error = open_file(infile2, name2, error);
    infile1 >> mat1;
    infile2 >> mat2;

    cout << "Adding Matrix 1 to Matrix 2:\n\n";
    mat3 = mat1 + mat2;
    cout << mat1 << endl;
    cout << setw(15) << " + " << endl << endl;
    cout << mat2 << endl;
    cout << "----------------------------" << endl;
    cout << mat3 << endl;

    infile1.close(); 
    infile2.close();

    return error;
}

/* -----------------------------------------------------------------------------
FUNCTION:          sub (int error, string name1, string name2)
DESCRIPTION:       Subtracts one matrix from another if they are of valid dimensions.
RETURNS:           error (int)
NOTES:             
----------------------------------------------------------------------------- */
int sub (int error, string name1, string name2)
{
    ifstream infile1, infile2;
    ofstream outfile;
    Matrix_ops<int> mat1, mat2, mat3;

    error = open_file(infile1, name1, error);
    error = open_file(infile2, name2, error);
    infile1 >> mat1;
    infile2 >> mat2;

    cout << "Subtracting Matrix 2 from Matrix 1:\n\n";
    mat3 = mat1 - mat2;
    cout << mat1 << endl;
    cout << setw(15) << " - " << endl << endl;
    cout << mat2 << endl;
    cout << "----------------------------" << endl;
    cout << mat3 << endl;

    infile1.close(); 
    infile2.close();

    return error;
}

/* -----------------------------------------------------------------------------
FUNCTION:          multiply (int error, string name1, string name2)
DESCRIPTION:       Multiplies two matrices together if they are of valid dimensions.
RETURNS:           error (int)
NOTES:             
----------------------------------------------------------------------------- */
int multiply (int error, string name1, string name2)
{
    ifstream infile1, infile2;
    ofstream outfile;
    Matrix_ops<int> mat1, mat2, mat3;

    error = open_file(infile1, name1, error);
    error = open_file(infile2, name2, error);
    infile1 >> mat1;
    infile2 >> mat2;

    cout << "Multiplying Matrix 1 and Matrix 2:\n\n";
    mat3 = mat1 * mat2;
    cout << mat1 << endl;
    cout << setw(15) << " x " << endl << endl;
    cout << mat2 << endl;
    cout << "----------------------------" << endl;
    cout << mat3 << endl;

    infile1.close(); 
    infile2.close();

    return error;
}

/* -----------------------------------------------------------------------------
FUNCTION:          eq_test (int &argc, int error, string A, string B, char *argv[])
DESCRIPTION:       Tests to see if two matrices are equal.
RETURNS:           error (int)
NOTES:             
----------------------------------------------------------------------------- */
int eq_test(int &argc, int error, string A, string B, char *argv[])
{   
    ifstream infile1, infile2;
    ofstream outfile;
    Matrix_ops<int> mat1, mat2;
    bool equality; 

    error = open_file(infile1, A, error);
    error = open_file(infile2, B, error);
    infile1 >> mat1; 
    infile2 >> mat2; 

    cout << mat1 << endl;
    cout << setw(15) << " = " << endl << endl;
    cout << mat2 << endl;
    cout << setw(15) << " ? " << endl << endl;
    cout << "----------------------------" << endl;


    if (mat1 == mat2)
    {
        cout << "\nThese two matrices ARE equal.\n\n";
    }

    else
    {
        cout << "\nThese two matrices are NOT equal.\n\n";
    }
    

    infile1.close(); 
    infile2.close();

    return error;

}

/* -----------------------------------------------------------------------------
FUNCTION:          scalar_mult (int scalar, int error, string name1)
DESCRIPTION:       Multiplies a matrix by a scalar integer value.
RETURNS:           error (int)
NOTES:             
----------------------------------------------------------------------------- */
int scalar_mult (int scalar, int error, string name1)
{   
    ifstream infile1;
    Matrix_ops<int> mat1, mat2;

    error = open_file(infile1, name1, error);
    infile1 >> mat1;

    cout << "Multiplying Matrix 1 by a scalar:\n\n";
    mat2 = mat1 * scalar;
    cout << setw(14) << scalar << endl << endl;
    cout << setw(15) << " x " << endl << endl;
    cout << mat1 << endl;
    cout << "----------------------------" << endl;
    cout << mat2 << endl;


    infile1.close(); 

    return error;
    
}

/* -----------------------------------------------------------------------------
FUNCTION:          scalar_div (double scalar, int error, string name1)
DESCRIPTION:       Divides a matrix by a scalar double value.
RETURNS:           error (int)
NOTES:             
----------------------------------------------------------------------------- */
int scalar_div (double scalar, int error, string name1)
{
    ifstream infile1;
    Matrix_ops<double> mat4, mat5;

    error = open_file(infile1, name1, error);
    infile1 >> mat4;

    cout << "Matrix 1 is divided by a scalar:\n\n";
    mat5 = mat4 / scalar;
    cout << mat4 << endl;
    cout << setw(15) << " / " << endl << endl;
    cout << setw(14) << scalar << endl << endl;
    cout << "----------------------------" << endl;
    cout << setprecision(2) << fixed;
    cout << mat5 << endl;


    infile1.close(); 

    return error;
}

