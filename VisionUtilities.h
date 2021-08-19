#ifndef VISION_UTILITIES_H
#define VISION_UTILITIES_H

#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>

class VisionUtilities {

    private:
        Mat cameraIntrinsic_;

    public:
        VisionUtilities(Mat);

        Mat cameraIntrinsic();
        Mat bundleAdjustment();
        Mat denseMatch();

};

#endif