// main.cpp

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <fstream>

#include "ArucoMarkerDetection.h"

using std::cout;
using std::endl;

using namespace cv;

int main(int argc, char** argv) {

    if (argc != 4) {
        cout << "Expecting a image file to be passed to program" << endl;
        return -1;
    }
    
    Mat img1 = imread(argv[1]);
    Mat img2 = imread(argv[2]);
    std::ifstream fileStream(argv[3]);
    
    if (img1.empty() || img2.empty()) {
        cout << "Not a valid image file" << endl;
        return -1;
    }

    double m;
    Mat camera_matrix = Mat::zeros(3, 3, CV_64FC1);
    int count = 0;
    
    while (fileStream >> m) {
        camera_matrix.at<double>(count / 3, count % 3) = m;
        count++;
    }
    
    ArucoMarkerDetection amd = ArucoMarkerDetection(aruco::DICT_7X7_50, img1, img2);

    amd.detectMarkers();
    amd.showDetectedMarkers();

    return 0;
}