/*
 * test_slic.cpp.
 *
 * Written by: Pascal Mettes.
 *
 * This file creates an over-segmentation of a provided image based on the SLIC
 * superpixel algorithm, as implemented in slic.h and slic.cpp.
 */
 

#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <float.h>
#include "slic_v1.h"
#include "SLIC-Superpixels/slic.h"
using namespace std;




int main(int argc, char *argv[]) {
    /* Load the image and convert to Lab colour space. */
    IplImage *image = cvLoadImage("/home/prassanna/Development/testData/Lenna.png", 1);
    IplImage *lab_image = cvCloneImage(image);
    cvCvtColor(image, lab_image, CV_BGR2Lab);

    cv::Mat image_new = cv::imread("/home/prassanna/Development/testData/Lenna.png");
    /* Yield the number of superpixels and weight-factors from the user. */
    int w = image->width, h = image->height;
    int nr_superpixels = 200;
    int nc = 40;

    double step = sqrt((w * h) / (double) nr_superpixels);
    
    /* Perform the SLIC superpixel algorithm. */
    Slic s;
    s.init_data(image_new, step, nc);
    std::cout<<s.centers;



    Slic_v1 slic;



}
