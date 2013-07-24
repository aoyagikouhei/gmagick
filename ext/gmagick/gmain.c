#include "gmagick.h"

void 
Init_gmagickn(){
  VALUE mGmagick;
  VALUE cImage;
  VALUE cPixel;

  InitializeMagick(NULL);

  mGmagick = rb_define_module("Gmagick");
  cImage = rb_define_class_under(mGmagick, "Image", rb_cObject);
  rb_define_alloc_func(cImage, gmi_alloc);
  rb_define_private_method(cImage, "initialize", gmi_initialize, -1);
  rb_define_method(cImage, "read", gmi_read_image, 1);
  rb_define_method(cImage, "write", gmi_write_image, -1);
  rb_define_method(cImage, "width", gmi_get_width, 0);
  rb_define_method(cImage, "height", gmi_get_height, 0);
  rb_define_method(cImage, "format", gmi_get_format, 0);
  rb_define_method(cImage, "count", gmi_get_number_images, 0);
  rb_define_method(cImage, "read_blob", gmi_read_image_blob, 1);
  rb_define_method(cImage, "write_blob", gmi_write_image_blob, 0);
  rb_define_method(cImage, "resize", gmi_resize_image, -1);
  rb_define_method(cImage, "rotate", gmi_rotate_image, 2);

  cPixel = rb_define_class_under(mGmagick, "Pixel", rb_cObject);
  rb_define_alloc_func(cPixel, gmp_alloc);
  rb_define_private_method(cPixel, "initialize", gmp_initialize, -1);
  rb_define_method(cPixel, "set_color", gmp_set_color, 1);
}
