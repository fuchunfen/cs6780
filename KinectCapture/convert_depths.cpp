#include <iostream>
#include <fstream>
#include <opencv/highgui.h>
#include <opencv/cv.h>

#define DEPTH_BUFFER_SIZE 614400 //2*640*480

IplImage * depth_image;

void
encode_depth (const std::string & filename)
{
  std::stringstream ss;
  ss << "captures/" << filename;
  std::ifstream file (ss.str().c_str(), std::ios_base::binary);
  uint16_t buffer[307200];
  file.read ((char*)buffer, DEPTH_BUFFER_SIZE);
  file.close();
  std::stringstream ss_new;
  ss_new << "converted_depth/" << filename.substr(0, filename.find('.') + 1) << "bmp";
  for (int row = 0; row < 480; ++row)
  {
    for (int col = 0; col < 640; ++col)
    {
      CV_IMAGE_ELEM(depth_image, uchar, row, 3*col) = buffer [row * 640 + col] & 0xff;
      CV_IMAGE_ELEM(depth_image, uchar, row, 3*col + 1) = buffer [row * 640 + col]>>8;
    }
  }
  cvSaveImage (ss_new.str().c_str(), depth_image);
}

int
main (int argc, char ** argv)
{
  depth_image = cvCreateImage (cvSize (640, 480), IPL_DEPTH_8U, 3);
  memset (depth_image->imageData, 0, depth_image->imageSize);

  std::ifstream input ("files.txt");
  std::string filename;
  while (input >> filename)
  {
    std::string type = filename.substr (filename.find('.') + 1);
    if (!type.compare("depth"))
    {
      encode_depth (filename);
    }
    std::cout << filename << " conversion complete" << std::endl;
  }

  cvReleaseImage (&depth_image);
  return 0;
}
