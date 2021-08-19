#include "VisionUtilities.h"

using namespace cv;

VisionUtilities::VisionUtilities(Mat cameraIntrinsic) {
    this->cameraIntrinsic_ = cameraIntrinsic;
}

Mat VisionUtilites::cameraIntrinsic() {
    return this->cameraIntrinsic_;
}

Mat bundleAdjustment() {
    
}

Mat VisionUtilities::denseMatch() {
    return;
}