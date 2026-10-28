# Submission

Group number and project title: OpenCVProject: Edison

Team members: Joel Seger, Thor Anderberg Nilsson, Love Skön, Kevin Taverner

Repository URL: https://github.com/JoelSeger/OpenCVProject

Final tag: final-submission

Assessed commit hash: 

Main interaction: Show the printed ArUco marker (4x4, id 0) to the webcam to turn the virtual lamp on. Rotate the marker to change the brightness between 0 and 100 %. Hide or obstruct the marker to turn the lamp off.

Required equipment or software: a webcam, the marker from resources/4x4_1000-0.svg printed 100 mm wide, and a C++17 compiler, CMake 3.16+ and OpenCV 4.1+ or 5.x.

Known limitations:
- No camera calibration. The focal length is approximated from the frame width, so the distance readout is approximate.
- Only ArUco DICT_4X4_1000 id 0 is recognised, and only the first recognised marker in a frame controls the lamp.
- Detection relies on a dark marker on a light background with reasonably even lighting.
- When the pose axes leave the frame OpenCV prints a drawFrameAxes warning per frame; the program keeps running.
- Any tiny interruption could dirupt the lamp.
- Allowable distorsion is low, tilt the marker too much and the detection will cease.

Presentation date and time: 2026-11-06 09:00
