/*
 * File:   cpp_ImageScience.cpp
 * Author: rupton
 *
 * Created on March 12, 2013, 2:50 PM
 */

#include <cstdlib>
#include <Eigen/Dense>
#include <iostream>
#include <math.h>
#include "cpp_ImageScience.h"
#include <mgl2/mgl.h>

using namespace std;
using namespace Eigen;

// Define methods
Test::Test(int nsampp, float padFacp)   // constructor
{
    nsamp  = nsampp;
    padFac = padFacp;
}

int Test::cart2polMat(ArrayXXd & X, ArrayXXd & Y, ArrayXXd & R, ArrayXXd & TH)
{
   
    for (int kk = 0; kk < nsamp; ++kk)
    {
        for (int ll = 0; ll < nsamp; ++ll)
        {
            X(kk,ll) = (kk-(nsamp-1)/2+1e-016)*2/(nsamp-1);
            Y(kk,ll) = (ll-(nsamp-1)/2+1e-016)*2/(nsamp-1);
        }
    }
    
    ArrayXXd RR2  = X*X+Y*Y;
    R   = RR2.sqrt();
    ArrayXXd TAN  = (Y/X);
    
    // calculation of theta
    for (int ii = 0; ii < nsamp; ++ii)
    {
        for (int jj = 0; jj < nsamp; ++jj)
        {
            TH(ii,jj) = atan(TAN(ii,jj));
        }
    }
    return 0;
}

ArrayXXd Test::maskForm(float padFac, ArrayXXd RR)
{
    ArrayXXd mask(RR.rows(),RR.cols());
    
    mask = RR;
    
    for (int ii = 0; ii < mask.rows(); ++ii)
    {
        for (int jj = 0; jj < mask.cols(); ++jj)
        {
            if (mask(ii,jj) <= 1.0/padFac)
            {
                mask(ii,jj) = 1/padFac;
            }
            if (mask(ii,jj) > 1/padFac)
            {
                mask(ii,jj) = 0;
            }
        }
    }
    mask = mask*padFac;
    
    return mask;
}

// printArray
int Test::printArray(ArrayXXd MAT, string format)
{
    char colStr[20];
    string totColStr;
    long ncols = MAT.cols();
    long nrows = MAT.rows();
    
    for (int ii = 0; ii < nrows; ++ii)
    {
        totColStr = " ";
        for (int jj = 0; jj < ncols; ++jj)
        {
            sprintf(colStr,"%.3f  ",MAT(ii,jj));
            totColStr += colStr;
        }
        cout << totColStr << endl;
    }
    return 0;
}


// main function
int main(int argc, char** argv) {
    
    // declare variables
    int nsamp  = 21;
    float padFac = 1;
    int retVal;
    ArrayXXd X(nsamp,nsamp), Y(nsamp,nsamp);
    ArrayXXd R(nsamp,nsamp), TH(nsamp,nsamp);
    string format = "4.2f ";
    
    
    // instantiate the Test class
    Test obj(nsamp,padFac);
    
    // calculate theta
    retVal = obj.cart2polMat(X, Y, R, TH);
    ArrayXXd mask = obj.maskForm(padFac, R);
    
    // print results
    retVal = obj.printArray(abs(TH), format);
    
    // plot results
    
    
    mglData data(21,21);
    
    /*
    mglGraph gr;
    gr.Rotate(50,60);
    gr.Light(true);
    gr.Surf(data);
     */
    
        
    return 0;
}
