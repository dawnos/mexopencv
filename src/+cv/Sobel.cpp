/**
 * @file Sobel.cpp
 * @brief mex interface for cv::Sobel
 * @ingroup imgproc
 * @author Kota Yamaguchi
 * @date 2011
 */
#include "mexopencv.hpp"
#include "opencv2/imgproc.hpp"
using namespace std;
using namespace cv;

// namespace {
/// KSize map for option processing
// const ConstMap<string,int> KSizeMap = ConstMap<string,int>
//     ("Scharr", CV_SCHARR);
// }

/**
 * Main entry called from Matlab
 * @param nlhs number of left-hand-side arguments
 * @param plhs pointers to mxArrays in the left-hand-side
 * @param nrhs number of right-hand-side arguments
 * @param prhs pointers to mxArrays in the right-hand-side
 */
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    // Check the number of arguments
    nargchk(nrhs>=1 && (nrhs%2)==1 && nlhs<=1);

    // Argument vector
    vector<MxArray> rhs(prhs, prhs+nrhs);

    // Option processing
    int ddepth = -1;
    int dx = 1;
    int dy = 1;
    int ksize = 3;
    double scale = 1;
    double delta = 0;
    int borderType = cv::BORDER_DEFAULT;
    for (int i=1; i<nrhs; i+=2) {
        string key(rhs[i].toString());
        if (key == "DDepth")
            ddepth = (rhs[i+1].isChar()) ?
                ClassNameMap[rhs[i+1].toString()] : rhs[i+1].toInt();
        else if (key == "XOrder")
            dx = rhs[i+1].toInt();
        else if (key == "YOrder")
            dy = rhs[i+1].toInt();
        else if (key == "KSize")
            // ksize = (rhs[i+1].isChar()) ?
                // KSizeMap[rhs[i+1].toString()] : rhs[i+1].toInt();
            ksize = rhs[i+1].toInt();
        else if (key == "Scale")
            scale = rhs[i+1].toDouble();
        else if (key == "Delta")
            delta = rhs[i+1].toDouble();
        else if (key == "BorderType")
            borderType = BorderType[rhs[i+1].toString()];
        else
            mexErrMsgIdAndTxt("mexopencv:error",
                "Unrecognized option %s", key.c_str());
    }

    // Process
    Mat src(rhs[0].toMat()), dst;
    Sobel(src, dst, ddepth, dx, dy, ksize, scale, delta, borderType);
    plhs[0] = MxArray(dst);
}
