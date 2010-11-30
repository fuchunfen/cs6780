#include <iostream>
#include <libusb.h>
#include "libfreenect.h"
#include <capture.h>
#include <fstream>
#include <sstream>
#include <opencv/highgui.h>
#include <opencv/cv.h>

#define COLOR_BUFFER_SIZE 307200 //640*480
#define DEPTH_BUFFER_SIZE 614400 //2*640*480

const int frame_period_ms = 50;
bool capture = false;
struct timeval tic;
bool toggled = false;

IplImage * rgb_image;

void
toggle_capture()
{
  toggled = !toggled;
}

void
save_depth (freenect_device * device, freenect_depth * depth, uint32_t timestamp)
{
  if (!toggled)
  {
    return;
  }
  if (!capture)
  {
    return;
  }
  toggled = false;
  capture = false;
  std::stringstream ss;
  ss << "captures/" << timestamp << ".depth";
  std::ofstream output (ss.str().c_str(), std::ios_base::binary);
  output.write ((const char *)depth, DEPTH_BUFFER_SIZE);
  output.close();
}

void
save_rgb (freenect_device * device, freenect_pixel * rgb, uint32_t timestamp)
{
  if (!toggled)
  {
    return;
  }
  struct timeval toc;
  gettimeofday (&toc, 0);
  long long diff = 1000*toc.tv_sec + toc.tv_usec/1000 - 1000*tic.tv_sec - tic.tv_usec/1000;
  if (diff < frame_period_ms)
  {
    std::cout << diff << std::endl;;
    return;
  }

  tic = toc;
  capture = true;
  std::stringstream ss;
  ss << "captures/" << timestamp << ".bayer";
  std::ofstream output (ss.str().c_str(), std::ios_base::binary);
  output.write ((const char *)rgb, COLOR_BUFFER_SIZE);
  output.close();
}

void
capture_init()
{
  gettimeofday (&tic, 0);
}

int
old_main (int argc, char ** argv)
{
  capture_init();
  freenect_context * context;
  freenect_device * device;

  if (freenect_init(&context, 0) < 0)
  {
    std::cerr << "Failed to initialize Kinect" << std::endl;
    return -1;
  }

  if (freenect_open_device (context, &device, 0) < 0)
  {
    std::cerr << "Failed to open device" << std::endl;
    return -1;
  }

  rgb_image = cvCreateImage (cvSize( 640, 480), IPL_DEPTH_8U, 1);

  freenect_set_depth_callback (device, save_depth);
  freenect_set_rgb_callback (device, save_rgb);
  freenect_set_rgb_format (device, FREENECT_FORMAT_BAYER);

  freenect_start_depth (device);
  freenect_start_rgb (device);

  while (freenect_process_events (context) >= 0);

  freenect_stop_depth (device);
  freenect_stop_rgb (device);

  freenect_close_device (device);

  freenect_shutdown (context);

  cvReleaseImage (&rgb_image);
  return 0;
}
