#include <iostream>
#include <fstream>
#include <opencv/highgui.h>
#include <opencv/cv.h>

#define COLOR_BUFFER_SIZE 307200 //640*480 
#define DEPTH_BUFFER_SIZE 614400 //2*640*480

IplImage * bayer_image;
IplImage * rgb_image;

void
encode_rgb (const std::string & filename)
{
  std::stringstream ss;
  ss << "captures/" << filename;
  std::ifstream file (ss.str().c_str(), std::ios_base::binary);
  uint8_t buffer [COLOR_BUFFER_SIZE];
  file.read ((char*)buffer, COLOR_BUFFER_SIZE);
  file.close();
  memcpy (bayer_image->imageData, buffer, COLOR_BUFFER_SIZE);
  cvCvtColor (bayer_image, rgb_image, CV_BayerGB2BGR);
  std::stringstream ss_new;
  ss_new << "converted/" << filename.substr(0, filename.find('.') + 1) << "jpg";
  cvSaveImage (ss_new.str().c_str(), rgb_image);
}

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
  ss_new << "converted/" << filename.substr(0, filename.find('.') + 1) << "txt";
  std::ofstream output (ss_new.str().c_str());
  for (int row = 0; row < 480; ++row)
  {
    for (int col = 0; col < 640; ++col)
    {
      output << buffer [row * 640 + col] << " ";
    }
    output << std::endl;
  }
  output.close();
}

int
main (int argc, char ** argv)
{
  rgb_image = cvCreateImage (cvSize (640, 480), IPL_DEPTH_8U, 3);
  bayer_image = cvCreateImage (cvSize (640, 480), IPL_DEPTH_8U, 1);

  std::ifstream input ("files.txt");
  std::string filename;
  while (input >> filename)
  {
    std::string type = filename.substr (filename.find('.') + 1);
    if (!type.compare("bayer"))
    {
      encode_rgb (filename);
    }
    else
    {
      encode_depth (filename);
    }
    std::cout << filename << " conversion complete" << std::endl;
  }

  cvReleaseImage (&rgb_image);
  return 0;
}
