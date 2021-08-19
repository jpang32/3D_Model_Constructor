#include "ArucoMarkerDetection.h"

using std::cout;
using std::endl;

using namespace cv;

ArucoMarkerDetection::ArucoMarkerDetection(aruco::PREDEFINED_DICTIONARY_NAME dictionary, Mat img1, Mat img2) {
    this->dictionary_ = aruco::getPredefinedDictionary(dictionary);
    this->parameters1_ = aruco::DetectorParameters::create();
    this->parameters2_ = aruco::DetectorParameters::create();
    this->img1_ = img1;
    this->img2_ = img2;
}

Mat ArucoMarkerDetection::img1() {
    return this->img1_;
}

Mat ArucoMarkerDetection::img2() {
    return this->img2_;
}

std::vector<int> ArucoMarkerDetection::markerIds1() {
    return this->markerIds1_;
}

std::vector<int> ArucoMarkerDetection::markerIds2() {
    return this->markerIds2_;
}

std::vector<std::vector<Point2f> > ArucoMarkerDetection::markerCorners1() {
    return this->markerCorners1_;
}

std::vector<std::vector<Point2f> > ArucoMarkerDetection::markerCorners2() {
    return this->markerCorners2_;
}

Mat ArucoMarkerDetection::camera_matrix() {
    return this->camera_matrix_;
}

void ArucoMarkerDetection::organizeMarkerCorners() {
    int index;
    std::vector<std::vector<Point2f> > v(this->markerCorners1_.size());
    for (auto i: this->markerIds1_) {
        std::vector<int>::iterator it = std::find(this->markerIds2_.begin(), this->markerIds2_.end(), i);
        index = std::distance(this->markerIds2_.begin(), it);
        std::copy(this->markerCorners2_[index].begin(), this->markerCorners2_[index].end(), back_inserter(v[i - 1]));
    }
    std::copy(v.begin(), v.end(), this->markerCorners2_.begin());
    std::copy(this->markerIds1_.begin(), this->markerIds1_.end(), this->markerIds2_.begin());
}

void ArucoMarkerDetection::detectMarkers() {
    aruco::detectMarkers(this->img1_, this->dictionary_, this->markerCorners1_, this->markerIds1_, this->parameters1_, this->rejectedCandidates1_);
    aruco::detectMarkers(this->img2_, this->dictionary_, this->markerCorners2_, this->markerIds2_, this->parameters2_, this->rejectedCandidates2_);

    this->organizeMarkerCorners();
}

void ArucoMarkerDetection::drawDetectedMarkers(Mat& img) {
    Mat outputImg;
    Mat outputImg1 = this->img1_.clone();
    Mat outputImg2 = this->img2_.clone();

    try {
        aruco::drawDetectedMarkers(outputImg1, this->markerCorners1_, this->markerIds1_);
        aruco::drawDetectedMarkers(outputImg2, this->markerCorners2_, this->markerIds2_);
    } catch (Exception& e) {
        cout << "Exception while drawing markers: " << e.what() << " (most likely member variables are "
        "not yet defined - did you call detectMarkers()? )" << endl;
    }

    hconcat(outputImg1, outputImg2, outputImg);

    outputImg.copyTo(img);
    
}