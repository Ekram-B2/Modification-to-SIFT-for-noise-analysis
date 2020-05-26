#ifndef _PROJECT_H_
#define _PROJECT_H_

/* Includes */
#include <iostream> 
#include <opencv/highgui.hpp> 
#include <opencv/imgproc.hpp>
#include <stdint.h>
#include <typeinfo>
#include <stdbool.h>

using namespace cv;
using namespace std;

/* Compute image mean given a cv image  */
uint32_t mean(cv::Mat image);
/* Splitting an image into sub images - tunable*/
std::vector <cv::Mat> split(cv::Mat image,int n);
/* Filter */ 
cv::Mat filter(cv::Mat img);
/* Merge */
cv::Mat merge(std::vector<cv::Mat> vec,cv::Mat image);
Mat myEntropy(Mat seq, int histSize);
float entropy(Mat seq, Size size, int index);
#endif
