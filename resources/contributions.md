## Individual assignments

| Individual assignment | Student | Component or task | Files | PR/commit | How tested |
|---|---|---|---|---|---|
| Assignment 1 | Kevin Taverner | CameraInput implementation and validation | CameraInput.h/.cpp | PR #2 | Camera, frame validation test and debug output |
| Assignment 1 | Love Skön | RegionAnalyzer implementation | RegionAnalyzer.h/.cpp | PR #3 | Region and invalid-input unit tests |
| Assignment 1 | Joel Seger | Contour detection, Line Estimation and Valid Quadliteral | ContourDetection.h/.cpp, LineEstimation.h/.cpp, IsValidQuad.h/.cpp | PR #4 | Camera, debug console messages |
| Assignment 1 | Thor Anderberg Nilsson | MarkerRecognizer | MarkerRecognizer.h/.cpp | PR #5 | Camera |
| Assignment 2 | Kevin Taverner | Contour and Corner bug fix | main.cpp, LineEstimation.cpp, ContourDetection.cpp, IsValidQuad.cpp, contributions.md | PR #9 | Debug checkpoints and camera image test |
| Assignment 2 | Thor Anderberg Nilsson | IsValidQuad | IsValidQuad.cpp | PR #10 | Camera and debug code-snippet |
| Assignment 2 | Joel Seger | Noise check and pose angle | PoseEstimator.cpp, MarkerRecognizer.cpp | PR #11 | Camera, debug console messages, tests |
| Assignment 2 | Love Skön | InteractionMapping 360 degree dimming | InteractionMapping.h/.cpp | PR #12 | Angle sweep and wrap unit tests |
| Assignment 2 | Love Skön | CameraInput dropped-frame handling | CameraInput.h/.cpp | PR #14 | End-of-stream and dropped-frame unit tests |



## Kevin Taverner
Component: Camera Input and Validation, Usable Marker Values and Virtual Lamp
Files: CameraInput.h, CameraInput.cpp, main.cpp, InteractionMapping.h 
InteractionMapping.cpp, LampRenderer.h, LampRenderer.cpp
Responsible for camera/video source opening, frame capture and validation.
Converting marker angle into usable brightness value between 0-100%. Renders a 
virtual lamp that is controlled by this value and also turns on and off by the 
marker detectiong existence.

Investigated and improved Countour extraction and corner estimation components,
with Joel's previous agreement

## Love Skön
Component: Binarization and Connected-region Labeling
Files: RegionAnalyzer.cpp, RegionAnalyzer.h, test_region_analyzer.cpp
Responsible for turning frames into binary images and extracting filtered candidate regions for marker detection.

For individual assignment 2, I investigated the boundary between PoseEstimator and
InteractionMapping (Kevin's component), with Kevin's agreement. PoseEstimator emits an
angle in -180..180 but InteractionMapping only mapped -90..90 and clamped the rest, so
half the rotation range was dead and the lamp jumped from 100% to 0% at the 180 degree
wrap. Added tests/test_interaction_mapping.cpp to show this and reworked the mapping.

## Joel Seger
Component: Contour Detection, Line Estimation, Quadliteral Validation
Files: CountorDetection.cpp, CountorDetection.h, LineEstimation.cpp, LineEstimation.h, IsValidQuad.cpp, IsValidQuad.h
Responsible for finding countors from the binarized picture, then finding four corners in each countor and drawing lines between them. With the lines in mind we do some math and determine if the object is a valid quadliteral.

## Thor Anderberg Nilsson
Component: Marker Normalisation and Recognition, Pose Estimation
Files: MarkerRecognizer.h, MarkerRecognizer.cpp, PoseEstimator.h, PoseEstimator.cpp
Responsible for taking the quads passed to me by Joel's component and warping them into flat images. Once there's a flat image of the quad, my component translates it into a bit-matrix in order to determine whether our specific marker is found in the quad, and if so, which way it is rotated. Screenshot: https://i.imgur.com/qkNIWOj.png. Pose Estimation then uses the marker's corners and its real size (measured on the printed paper) to find where the marker is in 3D relative to the camera and draws its axes. It outputs the marker's rotation angle on screen which in turn will be used to control a lightbulb on the screen. For individual assignment 2, I investigated and improved Quadrilateral validation (IsValidQuad.cpp).
The side-length check only compared 2 of the 4 sides, so uneven-sided quads were accepted. It now checks all 4 sides.