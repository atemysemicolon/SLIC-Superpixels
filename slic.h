#ifndef SLIC_H
#define SLIC_H

#include <opencv2/opencv.hpp>

class Slic
{

public:
    /*To Move to private*/
    cv::Mat clusters;
    cv::Mat distances;
    cv::Mat centers;

    std::vector<int> center_counts;

    int step, nc, ns, width, height;


    void init_data(cv::Mat image, int step, int nc);
    void clear_data();
    cv::Point find_local_minimum(cv::Mat image, cv::Point center);
    Slic();
    ~Slic();

};

#endif // SLIC_H
