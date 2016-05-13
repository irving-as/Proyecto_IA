#ifndef NETWORK_H
#define NETWORK_H
#include <math.h>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>
#include <QDebug>

class network
{
public:
    network();
    void train(int s, int c, int t, std::string path);
    int predict(std::string path);

private:
    CvANN_MLP_TrainParams params;
    CvANN_MLP *net;

    cv::Mat training_data;
    cv::Mat training_classifications;

    cv::Mat weights;

};

#endif // NETWORK_H
