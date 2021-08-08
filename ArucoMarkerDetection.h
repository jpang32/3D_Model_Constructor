#ifndef ARUCO_MARKER_DETECTION_H
#define ARUCO_MARKER_DETECTION_H

#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include <vector>
#include <string>

using namespace cv;

class ArucoMarkerDetection {

    private:
        Mat img1_;
        Mat img2_;
        Mat camera_matrix_;

        std::vector<int> markerIds1_;
        std::vector<std::vector<Point2f> > markerCorners1_, rejectedCandidates1_;
        Ptr<aruco::DetectorParameters> parameters1_;

        std::vector<int> markerIds2_;
        std::vector<std::vector<Point2f> > markerCorners2_, rejectedCandidates2_;
        Ptr<aruco::DetectorParameters> parameters2_;

        Ptr<aruco::Dictionary> dictionary_;

    public:
        //ArucoMarkerDetection(aruco::PREDEFINED_DICTIONARY_NAME dictionary);
        ArucoMarkerDetection(aruco::PREDEFINED_DICTIONARY_NAME dictionary, Mat img1, Mat img2);

        Mat img1();
        Mat img2();
        Mat camera_matrix();

        void detectMarkers();
        Mat showDetectedMarkers();


};

#endif