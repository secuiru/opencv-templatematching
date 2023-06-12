// opencv-test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>


using namespace cv;


int main()
{
    

    static std::string filepath = "C:\\work\\C++\\harjoituksia\\1\\opencv_matchtemplate";
    static std::string image_path = filepath+"\\image.png";
    static std::string object_image_path = filepath+"\\target_object.png";

    Mat imageGrayscale = imread(image_path, IMREAD_GRAYSCALE);
    Mat imageOriginal = imread(image_path);
    Mat object_image = imread(object_image_path, IMREAD_GRAYSCALE);
    Mat_<float> result;
  
   
    if (imageOriginal.empty()) {

        std::cout << "image not found\n";
        return 1;
    }
    if (object_image.empty()) {

        std::cout << "object image not found\n";
        return 1;
    }
  
    try {
        matchTemplate(imageGrayscale, object_image, result, TM_CCOEFF_NORMED);
    }
    catch (cv::Exception& e) {
        std::cout << e.msg;
    }

    if (result.empty()) {
        std::cout << "result empty\n";
        return 1;
    }
    

   

    cv::Size objectSize = object_image.size();
  

    double threshold_value = 0.7;
    threshold(result, result, threshold_value, 1, THRESH_TOZERO);

   
    Point location1;
    Point location2;
    
   
   
    for (int j = 0; j < result.rows; j++)
    {
        for (int i = 0; i < result.cols; i++)
        {
            if (result(j, i) > threshold_value) {
                
               
                location1.x = i;
                location1.y = j;
                

                location2.x = (location1.x + objectSize.width);
                location2.y=(location1.y + objectSize.height);
                rectangle( imageOriginal, location1,location2,(255, 255, 0), 2);
            }
        }
    }
    
    imshow("matchtemplate", result);
    imshow("image", imageOriginal);


   imwrite(filepath+"\\outputimage.png", imageOriginal);
   waitKey(0);
    
   
    
}
