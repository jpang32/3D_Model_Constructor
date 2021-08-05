#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include <vector>
#include <string>

using namespace cv;

int main(int argc, char** argv) {

    if (argc != 3) {
        std::cout << "# arguments required" << std::endl;
    }

    Mat img1 = imread(argv[1]);
    Mat img2 = imread(argv[2]);

    std::vector<int> markerIds;
    std::vector<std::vector<Point2f> > markerCorners, rejectedCandidates;
    Ptr<aruco::DetectorParameters> parameters = aruco::DetectorParameters::create();
    Ptr<aruco::Dictionary> dictionary = aruco::getPredefinedDictionary(aruco::DICT_7X7_50);
    aruco::detectMarkers(img1, dictionary, markerCorners, markerIds, parameters, rejectedCandidates);

    Mat outputImg = img1.clone();
    aruco::drawDetectedMarkers(outputImg, markerCorners, markerIds);

    imshow("Marker Detection", outputImg);
    int k = waitKey(0);

}