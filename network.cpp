#include "network.h"
#include <iostream>

#define NUMBER_OF_TRAINING_SAMPLES 5
#define ATTRIBUTES_PER_SAMPLE 400
#define NUMBER_OF_CLASSES 3

network::network()
{
    training_data = cv::Mat(0, ATTRIBUTES_PER_SAMPLE, CV_32FC1);
    training_classifications = cv::Mat(0, NUMBER_OF_CLASSES, CV_32FC1);

    int layers_d[] = { ATTRIBUTES_PER_SAMPLE, 20,  NUMBER_OF_CLASSES};
    cv::Mat layers = cv::Mat(1,3,CV_32SC1);
    layers.at<int>(0,0) = layers_d[0];
    layers.at<int>(0,1) = layers_d[1];
    layers.at<int>(0,2) = layers_d[2];

    net = new CvANN_MLP;
    net->create(layers, CvANN_MLP::SIGMOID_SYM, 0.6, 1);

    params = CvANN_MLP_TrainParams(

    cvTermCriteria(CV_TERMCRIT_ITER+CV_TERMCRIT_EPS, 1000, 0.000001),

    CvANN_MLP_TrainParams::BACKPROP,

    0.1,
    0.1);
}

void network::train(int s, int c, int t, std::string path)
{
    //Set matrices for the classification
    cv::Mat mS = cv::Mat(1, 3, CV_32S);
    mS.at<int>(0,0) = 1;
    mS.at<int>(0,1) = 0;
    mS.at<int>(0,2) = 0;
    cv::Mat mC = cv::Mat(1, 3, CV_32S);
    mC.at<int>(0,0) = 0;
    mC.at<int>(0,1) = 1;
    mC.at<int>(0,2) = 0;
    cv::Mat mT = cv::Mat(1, 3, CV_32S);
    mT.at<int>(0,0) = 0;
    mT.at<int>(0,1) = 0;
    mT.at<int>(0,2) = 1;

    cv::Mat mCh = cv::Mat(1,1,CV_32FC1);

    //Load images from first symbol
    for(int i = 0; i < s; i++)
    {
        std::string newPath = path + "s" + std::to_string(i) + ".bmp";
        cv::Mat temp = cv::imread(newPath);
        cv::Mat temp2 = cv::Mat(20, 20, CV_32FC1);
        cv::cvtColor(temp, temp2, CV_BGR2GRAY);
        temp2 = temp2.reshape(1,1);
        training_data.push_back(temp2);
        mCh.at<float>(0) = 0;
        training_classifications.push_back(mS);
    }
    //Load images from second symbol
    for(int i = 0; i < c; i++)
    {
        std::string newPath = path + "c" + std::to_string(i) + ".bmp";
        cv::Mat temp = cv::imread(newPath);
        cv::Mat temp2 = cv::Mat(20, 20, CV_32FC1);
        cv::cvtColor(temp, temp2, CV_BGR2GRAY);
        temp2 = temp2.reshape(1,1);
        training_data.push_back(temp2);
        mCh.at<float>(0) = 1;
        training_classifications.push_back(mC);
    }
    //Load images from third symbol
    for(int i = 0; i < t; i++)
    {
        std::string newPath = path + "t" + std::to_string(i) + ".bmp";
        cv::Mat temp = cv::imread(newPath);
        cv::Mat temp2 = cv::Mat(20, 20, CV_32FC1);
        cv::cvtColor(temp, temp2, CV_BGR2GRAY);
        temp2 = temp2.reshape(1,1);
        training_data.push_back(temp2);
        mCh.at<float>(0) = 2;
        training_classifications.push_back(mT);
    }

    //We need to convert the matrix to float as a requisite for the train method
    training_data.convertTo(training_data, CV_32FC1);
    training_classifications.convertTo(training_classifications, CV_32FC1);

    //Set initial weights to 1
    weights = cv::Mat::ones(1, training_data.rows, CV_32FC1);

    //Train the network
    net->train(training_data, training_classifications, weights);//, 0, params);
    std::cout << "Network Trained" << std::endl;
}

int network::predict(std::string path)
{
    cv::Mat temp = cv::imread(path);
    cv::Mat temp2 = cv::Mat(20, 20, CV_32FC1);
    cv::cvtColor(temp, temp2, CV_BGR2GRAY);
    temp2 = temp2.reshape(1,1);
    temp2.convertTo(temp2, CV_32FC1);
    cv::Mat pred = cv::Mat(1, 3, CV_32FC1);
    net->predict(temp2, pred);
    //if(pred.at<float>(0,0) < .5 && pred.at<float>(0,1) < .5 && pred.at<float>(0,0) < .5) return -1;
    if(pred.at<float>(0,0) > pred.at<float>(0,1))
    {
        if(pred.at<float>(0,0) > pred.at<float>(0,2)) return 0;
        else return 2;
    }
    else
    {
        if(pred.at<float>(0,1) > pred.at<float>(0,2)) return 1;
        else return 2;
    }
}
