#include <iostream>
#include <opencv2/opencv.hpp>
#include <tesseract/baseapi.h>
#include <tesseract/strngs.h>
//#include <iostream>
//kaisa kare?
g++ -I/usr/local/include/opencv -I/usr/local/include/opencv2 -L/usr/local/lib/ -g -o binaryName  cam1.cpp -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect  -lopencv_videoio -lopencv_imgcodecs -lopencv_video


 g++ -I/usr/local/include `pkg-config --cflags --libs opencv tesseract` -I/usr/local/include/opencv -I/usr/local/include/opencv2 -L/usr/local/lib/ threshold3.cpp   -lopencv_core -lopencv_imgproc -lopencv_highgui

 g++  -I/usr/local/include/opencv -I/usr/local/include/opencv2 -L/usr/local/lib/ -g  -o binaryName threshold3.cpp   -lopencv_core -lopencv_imgproc -lopencv_highgui

//works ye neche wala 100%

 g++ -I/usr/local/include `pkg-config --cflags --libs opencv tesseract` -I/usr/local/include/opencv -I/usr/local/include/opencv2 -L/usr/local/lib/ -g -o binaryName  threshold3.cpp -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect  -lopencv_videoio -lopencv_imgcodecs -lopencv_video

/*


 g++ -I/usr/local/include `pkg-config --cflags --libs opencv tesseract` threshold3.cpp -L/usr/local/lib  -lopencv_core -lopencv_imgproc -lopencv_highgui
*/


int main ()
{//
//Then create a Mat object that will store the data of the loaded image.
/*

Now we call the imread function which loads the image name specified by the first argument . The second argument specifies the format in what we want the image. This may be:

    CV_LOAD_IMAGE_UNCHANGED (<0) loads the image as is (including the alpha channel if present)
    CV_LOAD_IMAGE_GRAYSCALE ( 0) loads the image as an intensity one
    CV_LOAD_IMAGE_COLOR (>0) loads the image in the RGB format


*/
    //Our color image
    cv::Mat imageMat = cv::imread("/home/kunal/Desktop/projects/plate1.png", CV_LOAD_IMAGE_COLOR);
    //Grayscale matrix
//CV_8U is unsigned 8bit/pixel - ie a pixel can have values 0-255, this is the normal range for most image and video formats
    cv::Mat grayscaleMat (imageMat.size(), CV_8U);
    //Convert BGR to Gray
    cv::cvtColor( imageMat, grayscaleMat, CV_BGR2GRAY );
    //Binary image
    cv::Mat binaryMat(grayscaleMat.size(), grayscaleMat.type());
    //Apply thresholding
//threshold: parmetres:  (src,dst,thresh,maxvalue,type)
/*

thresh binary:
here:
converts the greyscale image to image having only 2 values one is zero and the other value is maxvalue specifed in param 255 is black
100: is thrsh value
in thresh_binary : all pixels having value >100  will have value ---> maxvalue  (here 255 i,e black)
and  the others  having value <100 will now have value-->0  (i.e  white)
*/


    cv::threshold(grayscaleMat, binaryMat, 100, 255, cv::THRESH_BINARY);
    //Show the results


    cv::namedWindow("Output", cv::WINDOW_AUTOSIZE);
    cv::imshow("Output", binaryMat);
    cv::imwrite("output.png",binaryMat);

/////////////////////////////////////////////////////////////////////////////////////////////////////

/*


Contours can be explained simply as a curve joining all the continuous points (along the boundary), having same color or intensity. The contours are a useful tool for shape analysis and object detection and recognition.

    For better accuracy, use binary images. So before finding contours, apply threshold or canny edge detection.
    findContours function modifies the source image. So if you want source image even after finding contours, already store it to some other variables.
    In OpenCV, finding contours is like finding white object from black background. So remember, object to be found should be white and background should be black.


http://www.google.co.in/url?sa=t&rct=j&q=&esrc=s&source=web&cd=4&ved=0CDQQFjADahUKEwiitKnPqcTHAhUOwY4KHUxLCBc&url=http%3A%2F%2Fdocs.opencv.org%2Fmaster%2Fd9%2Fd8b%2Ftutorial_py_contours_hierarchy.html&ei=q2vcVeKyIY6CuwTMlqG4AQ&usg=AFQjCNHQbjkhk2G437Xm9jSifU8Megl2kA&sig2=cRlJ_mupBBk_J9q46yQW_w
*/
    cv::Mat im2;
    binaryMat.convertTo(im2, CV_8U);

    std::vector<std::vector<cv::Point> > contours;
    cv::findContours(im2, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

//external : consider external shapes nly
/*
f you pass cv2.CHAIN_APPROX_NONE, all the boundary points are stored. But actually do we need all the points? For eg, you found the contour of a straight line. Do you need all the points on the line to represent that line? No, we need just two end points of that line. This is what cv2.CHAIN_APPROX_SIMPLE does. It removes all redundant points and compresses the contour, thereby saving memory.
*/

    double max_area = 0;
    int max_idx = 0;
    for (int i = 0; i < contours.size(); i++)
    {
        double area = cv::contourArea(contours[i]);
        max_idx  = area > max_area ? i : max_idx;
        max_area = area > max_area ? area : max_area;
    }

    im2.setTo(cv::Scalar(0));
    cv::drawContours(im2, contours, max_idx, cv::Scalar(255), -1);

    cv::namedWindow("Output2", cv::WINDOW_AUTOSIZE);
        cv::imshow("Output2", im2);
///////////////////////////////////////////////////////////////////////////////////////////////////
		cv::Mat im3;
		cv::cvtColor(imageMat, im3, CV_BGR2GRAY);
		im3 = ((255 - im3) & im2) > 200;
        cv::namedWindow("Output3", cv::WINDOW_AUTOSIZE);
               cv::imshow("Output3", im3);
	  cv::imwrite("output2.jpg",im3);

/*cv::Mat dst = im3.clone();
    cv::findContours(dst.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    for (int i = 0; i < contours.size(); i++)
    {
        if (cv::contourArea(contours[i]) < 100)
            cv::drawContours(dst, contours, i, cv::Scalar(0), -1);
    }
*/
	cv::namedWindow("Output3", cv::WINDOW_AUTOSIZE);
        cv::imshow("Output3", im3);
	  cv::imwrite("output2.jpg",im3);

	tesseract::TessBaseAPI tess;
    tess.Init(NULL, "eng", tesseract::OEM_DEFAULT);
// 		OcrEngineMode  	oem 
    tess.SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);
//Possible modes for page layout analysis. These must be kept in order of decreasing amount of layout analysis to be done, except for OSD_ONLY, so that the inequality test macros below work. 
    tess.SetImage((uchar*)im3.data, im3.cols, im3.rows, 1, im3.cols);

    // Get the text
    char* out = tess.GetUTF8Text();
    std::cout << out << std::endl;





    cv::waitKey(0);
    return 0;
}

