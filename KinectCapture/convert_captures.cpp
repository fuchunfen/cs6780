#include <iostream>
#include <fstream>
#include <opencv/highgui.h>
#include <opencv/cv.h>

IplImage * rgb_image;
uint16_t t_gamma [2048];

void
encode_rgb (const std::string & filename)
{
  std::stringstream ss;
  ss << "captures/" << filename;
  std::ifstream file (ss.str().c_str(), std::ios_base::binary);
  uint8_t buffer [921600];
  file.read ((char*)buffer, 921600);
  file.close();
  memcpy (rgb_image->imageData, buffer, 921600);
  cvCvtColor (rgb_image, rgb_image, CV_RGB2BGR);
  std::stringstream ss_new;
  ss_new << "converted/" << filename.substr(0, filename.find('.')) << ".jpg";
  cvSaveImage (ss_new.str().c_str(), rgb_image);
}

void
encode_depth (const std::string & filename)
{
  std::stringstream ss;
  ss << "captures/" << filename;
  std::ifstream file (ss.str().c_str(), std::ios_base::binary);
  uint16_t buffer[307200];
  file.read ((char*)buffer, 307200*2);
  file.close();
  std::stringstream ss_new;
  ss_new << "converted/" << filename.substr(0, filename.find('.'));
  std::ofstream output (ss_new.str().c_str());
  for (int row = 0; row < 480; ++row)
  {
    for (int col = 0; col < 640; ++col)
    {
      output << t_gamma[buffer [row * 640 + col]] << " ";
    }
    output << std::endl;
  }
  output.close();
}

int
main (int argc, char ** argv)
{
  for (int i = 0; i < 2048; ++i)
  {
    float v = i / 2048.0;
    v = powf(v, 3) * 6;
    t_gamma[i] = v*6*256;
  }

  rgb_image = cvCreateImage (cvSize (640, 480), IPL_DEPTH_8U, 3);

  std::ifstream input ("files.txt");
  std::string filename;
  while (input >> filename)
  {
    std::string type = filename.substr (filename.find('.') + 1);
    if (!type.compare("bgr"))
    {
      encode_rgb (filename);
    }
    else
    {
      encode_depth (filename);
    }
  }

  cvReleaseImage (&rgb_image);
  return 0;
}
