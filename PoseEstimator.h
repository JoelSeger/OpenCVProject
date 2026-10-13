#pragma once
#include <vector>
#include <opencv2/opencv.hpp>

struct PoseResult {
    cv::Vec3d rvec; // axis + angle (rad)
    cv::Vec3d tvec; // marker's center position relative to camera (X,Y,Z)
    double angle = 0; // -180 to 180
};

class PoseEstimator {
public:
    PoseResult estimatePose(const std::vector<cv::Point2f>& corners, const cv::Size& frameSize) const;
    void drawAxes(cv::Mat& frame, const PoseResult& pose) const;

private:
    cv::Mat cameraMatrix(const cv::Size& frameSize) const;

    static constexpr float markerLength = 100.0f; // printed marker side in mm (outer edge of black border)

    const std::vector<cv::Point3f> objectPoints = {
        {-markerLength / 2,  markerLength / 2, 0},
        { markerLength / 2,  markerLength / 2, 0},
        { markerLength / 2, -markerLength / 2, 0},
        {-markerLength / 2, -markerLength / 2, 0}
    };

    const cv::Mat distCoeffs = cv::Mat::zeros(4, 1, CV_64F);
};
