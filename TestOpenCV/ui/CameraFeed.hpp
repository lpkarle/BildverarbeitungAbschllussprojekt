//
//  CameraFeed.hpp
//  TestOpenCV
//
//  Created by Lukas Karle on 07.01.22.
//

#ifndef CameraFeed_hpp
#define CameraFeed_hpp

#include <stdio.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class CameraFeed
{
private:
    VideoCapture cameraCapture;
    
public:
    CameraFeed(void);
    ~CameraFeed(void);
};


#endif /* CameraFeed_hpp */
