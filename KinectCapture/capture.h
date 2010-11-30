#ifndef CAPTURE_H
#define CAPTURE_H

#include <libusb.h>
#include "libfreenect.h"

void save_rgb(freenect_device *dev, freenect_pixel *rgb, uint32_t timestamp);
void save_depth(freenect_device *dev, freenect_depth * depth, uint32_t timestamp);
void capture_init();
void toggle_capture();

#endif
