// This follows the "Pose Estimation" section of this guide from OpenCV:
// https://docs.opencv.org/4.x/d5/dae/tutorial_aruco_detection.html

#include "PoseEstimator.h"

// OpenCV 5 moved contourArea/approxPolyDP/getPerspectiveTransform/solvePnP into
// the geometry module, which <opencv2/opencv.hpp> no longer includes.
#if CV_VERSION_MAJOR >= 5
#include <opencv2/geometry.hpp>
#endif
#include <cmath>

PoseResult PoseEstimator::estimatePose(const std::vector<cv::Point2f>& corners, const cv::Size& frameSize) const {
    PoseResult pose;
    cv::solvePnP(objectPoints, corners, cameraMatrix(frameSize), distCoeffs, pose.rvec, pose.tvec, false, cv::SOLVEPNP_IPPE_SQUARE);

    cv::Matx33d rotation;
    cv::Rodrigues(pose.rvec, rotation);
    pose.angle = std::atan2(rotation(1, 0), rotation(0, 0)) * 180.0 / CV_PI;
    return pose;
}

void PoseEstimator::drawAxes(cv::Mat& frame, const PoseResult& pose) const {
    cv::drawFrameAxes(frame, cameraMatrix(frame.size()), distCoeffs, pose.rvec, pose.tvec, markerLength * 1.5f, 2);
}

// This is used instead of calibrating camera
cv::Mat PoseEstimator::cameraMatrix(const cv::Size& frameSize) const {
    double f = frameSize.width;
    return (cv::Mat_<double>(3, 3) <<
        f, 0, frameSize.width / 2.0,
        0, f, frameSize.height / 2.0,
        0, 0, 1);
}
