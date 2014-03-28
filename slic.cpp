#include "slic.h"


//DONE
void Slic::init_data(cv::Mat image, int step, int nc)
{
    clear_data();

    this->step=step;
    this->nc=nc;
    width = image.cols;
    height = image.rows;
    center_counts.clear();
    clusters = cv::Mat(image.rows, image.cols, CV_32FC1, cv::Scalar(-1)).clone();
    distances = cv::Mat(image.rows, image.cols, CV_32FC1, cv::Scalar(FLT_MAX)).clone();
    centers.create(image.rows,image.cols, CV_32FC(5));
    centers = cv::Scalar(0);




    for(int i=step; i<width - step/2; i+= step)
        for(int j=step; j<height - step/2; j+=step)
        {
            std::vector <double> center;
            cv::Point nc = find_local_minimum(image, cv::Point(i,j));
            cv::Vec3f colour = image.at<cv::Vec3f>(nc);

            centers.at<cv::Vec3f>(j,i)[0] = colour[0];
            centers.at<cv::Vec3f>(j,i)[1] = colour[1];
            centers.at<cv::Vec3f>(j,i)[2] = colour[2];
            centers.at<cv::Vec3f>(j,i)[3] = nc.x;
            centers.at<cv::Vec3f>(j,i)[4] = nc.y;


        }

}


cv::Point Slic::find_local_minimum(cv::Mat image, cv::Point center)
{
    double min_grad = FLT_MAX;
    cv::Point local_minima = center;

    for(int i =center.x-1; i<center.x+2;i++)
        for(int j=center.y-1; j<center.y+2;j++)
        {
            cv::Vec3f c1 = image.at<uchar>(j+1,i);
            cv::Vec3f c2 = image.at<uchar>(j,i);
            cv::Vec3f c3 = image.at<uchar>(j,i+1);

            for(int k=0;k<image.channels();k++)
            {


                if (sqrt(pow(c1[k] - c3[k], 2)) + sqrt(pow(c2[k] - c3[k],2)) < min_grad)
                {
                    min_grad = fabs(c1[k]- c3[k]) + fabs(c2[k] - c3[k]);
                    local_minima.x = i;
                    local_minima.y = j;
                }

            }
        }

    return  local_minima;
}

void Slic::generate_superpixels(cv::Mat image, int step, int nc)
{
    init_data(image, step, nc);



    for (int i = 0; i < NR_ITERATIONS; i++)
    {
        //Reset not required as init_data takes care of it
        //Maybe required!!!!!! Dry run it

        for (int m = 0; m < (int) centers.cols; m++)
            for (int n = 0; n < (int) centers.rows; n++)
            {
                /* Only compare to pixels in a 2 x step by 2 x step region. */
                for (int k = centers.at<float>(n,m)[3] - step; k < centers.at<float>(n,m)[3] + step; k++)
                {
                    for (int l = centers.at<float>(n,m)[4] - step; l < centers.at<float>(n,m)[4] + step; l++)
                    {

                        //LEFT CODING HERE

                        if (k >= 0 && k < image->width && l >= 0 && l < image->height)
                        {
                            CvScalar colour = cvGet2D(image, l, k);
                            double d = compute_dist(j, cvPoint(k,l), colour);

                            /* Update cluster allocation if the cluster minimizes the
                               distance. */
                            if (d < distances[k][l])
                            {
                                distances[k][l] = d;
                                clusters[k][l] = j;
                            }

                        }
                    }
                }
            }

    }

}






Slic::~Slic()
{

}

Slic::Slic()
{
}


