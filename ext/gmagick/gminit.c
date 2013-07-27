#include "gmagick.h"

void 
Init_gmagickn(){
  VALUE mGmagick;
  VALUE cImage;
  VALUE cPixel;
  VALUE cDrawing;

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
  rb_define_method(cImage, "depth", gmi_get_depth, 0);
  rb_define_method(cImage, "colors", gmi_get_colors, 0);
  rb_define_method(cImage, "resolution", gmi_get_resolution, 0);
  rb_define_method(cImage, "count", gmi_get_number_images, 0);
  rb_define_method(cImage, "read_blob", gmi_read_image_blob, 1);
  rb_define_method(cImage, "write_blob", gmi_write_image_blob, 0);
  rb_define_method(cImage, "resize", gmi_resize, -1);
  rb_define_method(cImage, "rotate", gmi_rotate, 2);
  rb_define_method(cImage, "draw", gmi_draw, 1);
  rb_define_method(cImage, "resample", gmi_resample, -1);
  rb_define_method(cImage, "flip", gmi_flip, 0);
  rb_define_method(cImage, "flop", gmi_flop, 0);
  rb_define_method(cImage, "crop", gmi_crop, 4);
  rb_define_method(cImage, "format=", gmi_set_format, 1);
  rb_define_method(cImage, "border", gmi_border, 3);
  rb_define_method(cImage, "frame", gmi_frame, 5);
  rb_define_method(cImage, "blur", gmi_blur, 2);
  rb_define_method(cImage, "swirl", gmi_swirl, 1);
  rb_define_method(cImage, "charcoal", gmi_charcoal, 2);
  rb_define_method(cImage, "oil_paint", gmi_oil_paint, 1);

  cPixel = rb_define_class_under(mGmagick, "Pixel", rb_cObject);
  rb_define_alloc_func(cPixel, gmp_alloc);
  rb_define_private_method(cPixel, "initialize", gmp_initialize, -1);
  rb_define_method(cPixel, "color=", gmp_set_color, 1);
  rb_define_method(cPixel, "color", gmp_get_color, 0);

  cDrawing = rb_define_class_under(mGmagick, "Drawing", rb_cObject);
  rb_define_alloc_func(cDrawing, gmd_alloc);
  rb_define_private_method(cDrawing, "initialize", gmd_initialize, 0);
  rb_define_method(cDrawing, "fill_color=", gmd_set_fill_color, 1);
  rb_define_method(cDrawing, "stroke_color=", gmd_set_stroke_color, 1);
  rb_define_method(cDrawing, "stroke_width=", gmd_set_stroke_width, 1);
  rb_define_method(cDrawing, "round_rectangle", gmd_draw_round_rectangle, 6);
}
