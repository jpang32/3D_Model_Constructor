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
    Mat testImage;
    amd.drawDetectedMarkers(testImage);

    std::vector<Point2f> corners1_flattened;
    std::vector<Point2f> corners2_flattened;

    for(const auto &v: amd.markerCorners1()) corners1_flattened.insert(corners1_flattened.end(), v.begin(), v.end());
    for(const auto &v: amd.markerCorners2()) corners2_flattened.insert(corners2_flattened.end(), v.begin(), v.end());                                                                                       

    imshow("", testImage);
    waitKey(0);

    Mat fundamental = findFundamentalMat(corners1_flattened, corners2_flattened, FM_RANSAC, 2, 0.95);

    //Next step: draw correspondences between images with fundamental matrix
    


    // Calculate essential matrix
    //findFundamentalMat(amd.)

    //fundamentalFromEssential()

    return 0;
}