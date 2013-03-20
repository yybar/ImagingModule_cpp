/*
 File      :   cpp_ImageScience.h
 Project   :   cythonTest
 Created by:   Robert Upton (Sigma Space Corporation)
 Date      :   3/12/13
 Summary   :   This is the header code containing the declaration of the classes
 and methods that will be defined in the cpp_ImageScience.cpp code.
 The classes, methods and attributes will be compiled with Cython
 to introduce the classes into Python as modules.  This will eventually
 become a module in Python
 */

#ifndef __cythonTest__cpp_ImageScience__
#define __cythonTest__cpp_ImageScience__

#include "cpp_ArrayXXdpy.h"

class Test
{
private:
    int nsamp;
    float padFac;
    
public:
    Test(int nsampp, float padFacp);
    ArrayXXd getArrayXd(int d1, int d2);
    ArrayXXd maskForm(float padFac, ArrayXXd RR);
    int cart2polMat(ArrayXXd & X, ArrayXXd & Y, ArrayXXd & R, ArrayXXd & TH);
    int printArray(ArrayXXd MAT, std::string format);
    
};

#endif /* defined(__cythonTest__cpp_ImageScience__) */

