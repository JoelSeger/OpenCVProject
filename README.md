# OpenCVProject: Edison

A webcam looks for a printed ArUco marker. When the marker is visible, a virtual lamp on screen turns on. Rotating the marker changes the lamp's brightness. Hiding the marker turns the lamp off.

Pipeline (one class per stage, all in src/):

1. CameraInput: opens a camera or video file, reads frames, survives dropped frames.
2. RegionAnalyzer: binarises the frame and labels connected regions.
3. ContourDetection, LineEstimation, IsValidQuad: extracts contours, fits four lines, keeps valid quadrilaterals.
4. MarkerRecognizer: warps each quad to 60x60 px, reads the 4x4 bit grid, matches ArUco DICT_4X4_1000 id 0 in any rotation.
5. PoseEstimator: solvePnP on the marker corners, gives rotation angle (-180..180 degrees) and distance.
6. InteractionMapping: folds the angle into -90..90 and maps it to brightness 0..100 %.
7. LampRenderer: draws the lamp.

## Supported platforms

- Linux. Linux with GCC 16.2, CMake 4.4, Ninja 1.13.
- Windows. Windows with Visual Studio and vcpkg.
- Compiler: any C++17 compiler.

## Required libraries

- OpenCV 4.1 or newer, or OpenCV 5.x. Tested with OpenCV 5.0.0. Modules used: core, imgproc, imgcodecs, videoio, highgui, calib3d (geometry on OpenCV 5).
- CMake 3.16 or newer.
- No other libraries.

On OpenCV 5 the sources include <opencv2/geometry.hpp>, guarded by CV_VERSION_MAJOR, because contourArea, approxPolyDP, getPerspectiveTransform and solvePnP moved there.

## Configure, build, run

    cmake -S . -B build
    cmake --build build
    ./build/camera_grab                                 # webcam 0
    ./build/camera_grab 1                               # another camera index
    ./build/camera_grab resources/test_video_bt709.mp4  # a video file instead of a camera

Keys while running: Esc quits, d prints one frame of debug output to the terminal

Windows note: create CMakeUserPresets.json in the project root with the content below, then use the "default" preset in your IDE or run cmake --preset default.

    {
      "version": 3,
      "configurePresets": [
        {
          "name": "default",
          "binaryDir": "${sourceDir}/build",
          "toolchainFile": "$env{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
        }
      ]
    }

## Camera, marker and resources

- Camera: any webcam OpenCV can open. 640x480 at 30 fps is enough. Camera index 0 is the default.
- Calibration: none needed. PoseEstimator approximates the focal length from the frame width and assumes no lens distortion, so the distance readout is approximate.
- Marker: print resources/4x4_1000-0.svg (ArUco DICT_4X4_1000, id 0) so the black border is 100 mm on a side. PoseEstimator uses 100 mm; a different print size only scales the distance readout.
- Videos: resources/test_video.mp4 and resources/test_video_bt709.mp4 (same clip, 1920x1080, 27 s, a board of eight 4x4 markers). Use the bt709 copy; the other one makes FFmpeg print a colour-space warning per frame.

## Tests

    cd build && ctest --output-on-failure

Four test programs, each also runnable on its own from build/: test_region_analyzer, test_camera_input, test_interaction_mapping, test_marker_recognizer. They generate their own synthetic images and videos; no camera is needed.

## Reproducing the demonstration

1. Build as above and start ./build/camera_grab with the webcam connected.
2. Seven windows open: the raw frame, the binarised frame, connected regions, detected contours, the warped marker candidates, the detected quadrilaterals with pose axes and angle text, and the lamp.
3. Hold the printed marker flat towards the camera, about 30 to 60 cm away, in even light. The quad is outlined in yellow, "MARKER top left" is drawn at its top-left corner, and the lamp turns on.
4. Rotate the marker about the camera axis. Upright is 50 % brightness; a quarter turn one way reaches 100 %, the other way 0 %. Turning past a quarter turn dims again, with no jump at the half turn.
5. Hide the marker. The lamp turns off.
6. Without a camera, run on resources/test_video_bt709.mp4. The clip exercises stages 1 to 6: all eight markers on the board are found as valid quadrilaterals (docs/evidence/test_video_detected_quads.png). The board markers are not id 0, so the lamp stays off.

## Repository layout

    README.md          this file
    SUBMISSION.md      submission cover sheet
    CONTRIBUTIONS.md   who did what, with the individual assignment table
    AI_USE.md          AI tool use per student
    CMakeLists.txt     builds camera_grab and the four test programs
    src/               application sources
    tests/             test programs
    resources/         marker, test videos, project proposal
    docs/              debug checkpoints and evaluation evidence
