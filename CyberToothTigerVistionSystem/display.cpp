#include "/usr/local/include/opencv4/opencv2/opencv.hpp"
#include "/usr/local/include/opencv4/opencv2/video.hpp"
#include "/usr/local/include/opencv4/opencv2/videoio.hpp"
#include "/usr/local/include/opencv4/opencv2/opencv_modules.hpp"
#include "/usr/local/include/opencv4/opencv2/core.hpp"
#include "/usr/local/include/opencv4/opencv2/imgproc.hpp"
#include "/usr/local/include/opencv4/opencv2/highgui.hpp"
#include <iostream>
#include <thread>

using namespace std;
using namespace cv;
class display {
    int CameraLeftDevice, CameraRightDevice, CameraWidth, CameraHight;
    public: void setup(int myCameraLeftDevice, int myCameraRightDevice, int myCameraWidth, int myCameraHight) {
        CameraLeftDevice = myCameraLeftDevice;
        CameraRightDevice = myCameraRightDevice;
        CameraWidth = myCameraWidth;
        CameraHight = myCameraHight;

        std::thread visionThread(show, CameraLeftDevice, CameraRightDevice, CameraWidth, CameraHight);
        visionThread.detach();
    }
    


    int static show(int CameraLeftDeviceinput, int CameraRightDeviceinput, int CameraWidthinput, int CameraHightinput) {

        namedWindow("Frame", WINDOW_NORMAL);
        setWindowProperty("Frame", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);


        // Create a VideoCapture object and open the input file
        // If the input is the web camera, pass 0 instead of the video file name
        VideoCapture cap_left(CameraLeftDeviceinput);
        cap_left.set(CAP_PROP_FRAME_WIDTH, CameraWidthinput);
        cap_left.set(CAP_PROP_FRAME_HEIGHT, CameraHightinput);
        VideoCapture cap_right(CameraRightDeviceinput);
        cap_right.set(CAP_PROP_FRAME_WIDTH, CameraWidthinput);
        cap_right.set(CAP_PROP_FRAME_HEIGHT, CameraHightinput);

        //3d offset

        Point dddoffset;
        dddoffset.x = -50;
        dddoffset.y = 50;

        // text handles
        Point testTextorg;
        testTextorg.x = 600;
        testTextorg.y = 350;


        Mat output;

        // Check if camera opened successfully
        if (!cap_left.isOpened()) {
            cout << "Error opening left video stream or file" << endl;
            return -1;
        }
        if (!cap_right.isOpened()) {
            cout << "Error opening right video stream or file" << endl;
            return -1;
        }


        while (1) {
            Mat left;
            Mat right;
            // Capture frame-by-frame
            cap_left.read(left);
            cap_right.read(right);
            // If the frame is empty, break immediately
            if (left.empty())
                break;
            if (right.empty())
                break;
            //join both camera images
            hconcat(left, right, output);

            putText(output, "test text", testTextorg, 1, 1.6, (255, 255, 255), 1, 8, false);
            Point testTextrightorg = testTextorg;
            testTextrightorg.x += 1280 + dddoffset.x;
            putText(output, "test text", testTextrightorg, 1, 1.6, (255, 255, 255), 1, 8, false);

            // Display the resulting frame
            imshow("Frame", output);

            // Press  ESC on keyboard to exit
            char c = (char)waitKey(25);
            if (c == 27)
                break;
        }
        // When everything done, release the video capture object
        cap_left.release();
        cap_right.release();

        // Closes all the frames
        destroyAllWindows();
        return 0;
    }
};