# Debug checkpoints

camera_grab shows one window per pipeline stage so a failure can be located by looking at the first window that is wrong.

| Window | Stage | What a good frame looks like |
|---|---|---|
| OpenCV video test | 1 CameraInput | The raw camera or video frame. |
| Binarised | 2 RegionAnalyzer | Marker cells and border white, background black. |
| Connected regions | 3 RegionAnalyzer | A green box around each candidate region. |
| Detected Contour | 4 ContourDetection | Candidate contours drawn in green. |
| Warped | 7 MarkerRecognizer | Each valid quad warped to a 60x60 grid, enlarged 4x. Black square when there is no quad. |
| Detected Quadrilateral | 5-6, 8-9 | Quads outlined in yellow with coloured corners and a Quad N label, "MARKER top left" on the recognised marker, pose axes, and "angle N deg, distance N mm" at the top. |
| Lamp | 10-11 InteractionMapping, LampRenderer | The lamp, on when a marker is found, brightness from the angle. |

Press d to print one frame of debug output to the terminal:

    --- DEBUG FRAME ---
    Regions detected: N
    Region: [x y w h] | Contour points: N | Area: N     (one line per region)
    Quad valid: true/false
      Corner 0..3: [x, y]
      WARNING: Duplicate corners i and j               (only if two corners coincide)
    Valid quadrilaterals: N
    Marker recognized: true/false
    END DEBUG

Console messages while running:

- "Source: ..." at start: what was opened, resolution and fps.
- "Warning: camera N did not deliver a frame, retrying": a dropped camera frame, skipped.
- "Stopping: ... reached end of stream": a video file ended; the program exits.
- "Error: could not open ...": the camera index or file could not be opened; exit code 1.
