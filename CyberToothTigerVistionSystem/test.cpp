#include "opencv2/opencv.hpp"
#include "opencv2/video.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/opencv_modules.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"


using namespace std;
using namespace cv;

int vision() {

    cv::namedWindow("Frame", WINDOW_NORMAL);
    cv::setWindowProperty("Frame", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);


    // Create a VideoCapture object and open the input file
    // If the input is the web camera, pass 0 instead of the video file name
    VideoCapture cap_left(1);
    cap_left.set(CAP_PROP_FRAME_WIDTH, 1280);
    cap_left.set(CAP_PROP_FRAME_HEIGHT, 720);
    VideoCapture cap_right(3);
    cap_right.set(CAP_PROP_FRAME_WIDTH, 1280);
    cap_right.set(CAP_PROP_FRAME_HEIGHT, 720);


    //3d offset
    Point dddoffset;
    dddoffset.x = -50;
    dddoffset.y = 50;

    // text handles
    Point testTextorg;
    testTextorg.x = 600;
    testTextorg.y = 350;


    cv::Mat output;

    // Check if camera opened successfully
    if (!cap_left.isOpened()) {
        //cout << "Error opening left video stream or file" << endl;
        return -1;
    }
    if (!cap_right.isOpened()) {
        //cout << "Error opening right video stream or file" << endl;
        return -1;
    }


    while (1) {
        cv::Mat left;
        cv::Mat right;
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

        putText(output, "test text", testTextorg , 1, 1.6, (255, 255, 255), 1, 8, false);
        Point testTextrightorg = testTextorg;
        testTextrightorg.x += 1280 + dddoffset.x;
        putText(output, "test text", testTextrightorg , 1, 1.6, (255, 255, 255), 1, 8, false);

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
