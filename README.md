# BezierCurves

Hello! Welcome to the Bezier Curve Library!

This project is activly in development, so files you see other then "BezierCurve.h" are not going to be included in the final release!

Classes:
 - Curve:
    - Constructor Arguments:
       - ((float)Root 1 X (R1x), (float)Root 1 Y (R2y), (float)Root 2 X (R2x), (float)Root 2 X (R2y), (float)Handle 1 X (P1x), (float)Handle 1 Y (P1y), (float)Handle 2 X (P2x), (float)Handle 2 Y (P2y))
     - Functions:
         - FindPoint:
                Function Arguments:
                    ((float) t value (t))
                Return Values:
                    pair<float, float> - This is the final position of the requested point
                Description
                    This function takes in a t value between 0 and 1. This represents a percentage of the line length. It outputs the X and Y position of a point at that percentage across the line.
    Spline:
        Constructor Arguments:
            ((Curve) Starting Curve (first))
        Functions:
            Add:
                Function Arguments:
                    ((float) Root 2 X (Rx), (float) Root 2 Y (Ry), (float) Handle 2 X (Px), (float) Handle 2 Y (Py))
                Return Values:
                        None
                Description:
                    This adds another Bezier Curve to the spline, and makes the first and second derivitave of the full spline continuous by setting the first root of the new Bezier curve to the second root of the last Bezier curve, and mirroring the second handle of the last Bezier Curve across the second root of the last Bezier Curve to form the first handle of the new Bezier Curve.
            MakeContinuous:
                Function Arguments:
                    None
                Return values:
                    None
                Description
                    Uses the same process described in the add function on all of the Bezier Curves in the spline to make sure that the first and second derivitave of both are continuous


--Extra Files--
- olcPixelGameEngine.h
  - This is not made by me, but by Javidx9. I use it to visualize to Bezier Cuves.
- Source.cpp
 - This is just a test file for me to run olcPixelGameEngine.h on, and test the Bezier Cuves