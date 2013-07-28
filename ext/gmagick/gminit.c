#include "gmagick.h"

VALUE Module_Gmagick;
VALUE Class_Image;
VALUE Class_Pixel;
VALUE Class_Drawing;

ID id_new;

void 
Init_gmagickn(){
  InitializeMagick(NULL);

  Module_Gmagick = rb_define_module("Gmagick");
  Class_Image = rb_define_class_under(Module_Gmagick, "Image", rb_cObject);
  rb_define_alloc_func(Class_Image, gmi_alloc);
  rb_define_private_method(Class_Image, "initialize", gmi_initialize, -1);
  rb_define_method(Class_Image, "read", gmi_read_image, 1);
  rb_define_method(Class_Image, "write", gmi_write_image, -1);
  rb_define_method(Class_Image, "width", gmi_get_width, 0);
  rb_define_method(Class_Image, "height", gmi_get_height, 0);
  rb_define_method(Class_Image, "format", gmi_get_format, 0);
  rb_define_method(Class_Image, "depth", gmi_get_depth, 0);
  rb_define_method(Class_Image, "colors", gmi_get_colors, 0);
  rb_define_method(Class_Image, "resolution", gmi_get_resolution, 0);
  rb_define_method(Class_Image, "count", gmi_get_number_images, 0);
  rb_define_method(Class_Image, "read_blob", gmi_read_image_blob, 1);
  rb_define_method(Class_Image, "write_blob", gmi_write_image_blob, 0);
  rb_define_method(Class_Image, "resize", gmi_resize, -1);
  rb_define_method(Class_Image, "rotate", gmi_rotate, 2);
  rb_define_method(Class_Image, "draw", gmi_draw, 1);
  rb_define_method(Class_Image, "resample", gmi_resample, -1);
  rb_define_method(Class_Image, "flip", gmi_flip, 0);
  rb_define_method(Class_Image, "flop", gmi_flop, 0);
  rb_define_method(Class_Image, "crop", gmi_crop, 4);
  rb_define_method(Class_Image, "format=", gmi_set_format, 1);
  rb_define_method(Class_Image, "border", gmi_border, 3);
  rb_define_method(Class_Image, "frame", gmi_frame, 5);
  rb_define_method(Class_Image, "blur", gmi_blur, 2);
  rb_define_method(Class_Image, "swirl", gmi_swirl, 1);
  rb_define_method(Class_Image, "charcoal", gmi_charcoal, 2);
  rb_define_method(Class_Image, "oil_paint", gmi_oil_paint, 1);
  rb_define_method(Class_Image, "cycle_colormap", gmi_cycle_colormap, 1);
  rb_define_method(Class_Image, "solarize", gmi_solarize, 1);
  rb_define_method(Class_Image, "shear", gmi_shear, 3);

  Class_Pixel = rb_define_class_under(Module_Gmagick, "Pixel", rb_cObject);
  rb_define_alloc_func(Class_Pixel, gmp_alloc);
  rb_define_private_method(Class_Pixel, "initialize", gmp_initialize, -1);
  rb_define_method(Class_Pixel, "color=", gmp_set_color, 1);
  rb_define_method(Class_Pixel, "color", gmp_get_color, 0);
  rb_define_method(Class_Pixel, "color_count=", gmp_set_color_count, 1);
  rb_define_method(Class_Pixel, "color_count", gmp_get_color_count, 0);

  Class_Drawing = rb_define_class_under(Module_Gmagick, "Drawing", rb_cObject);
  rb_define_alloc_func(Class_Drawing, gmd_alloc);
  rb_define_private_method(Class_Drawing, "initialize", gmd_initialize, 0);
  rb_define_method(Class_Drawing, "fill_color=", gmd_set_fill_color, 1);
  rb_define_method(Class_Drawing, "fill_color", gmd_get_fill_color, 0);
  rb_define_method(Class_Drawing, "fill_opacity=", gmd_set_fill_opacity, 1);
  rb_define_method(Class_Drawing, "fill_opacity", gmd_get_fill_opacity, 0);
  rb_define_method(Class_Drawing, "font=", gmd_set_font, 1);
  rb_define_method(Class_Drawing, "font", gmd_get_font, 0);
  rb_define_method(Class_Drawing, "font_family=", gmd_set_font_family, 1);
  rb_define_method(Class_Drawing, "font_family", gmd_get_font_family, 0);
  rb_define_method(Class_Drawing, "font_size=", gmd_set_font_size, 1);
  rb_define_method(Class_Drawing, "font_size", gmd_get_font_size, 0);
  rb_define_method(Class_Drawing, "font_stretch=", gmd_set_font_stretch, 1);
  rb_define_method(Class_Drawing, "font_stretch", gmd_get_font_stretch, 0);
  rb_define_method(Class_Drawing, "font_style=", gmd_set_font_style, 1);
  rb_define_method(Class_Drawing, "font_style", gmd_get_font_style, 0);
  rb_define_method(Class_Drawing, "font_weight=", gmd_set_font_weight, 1);
  rb_define_method(Class_Drawing, "font_weight", gmd_get_font_weight, 0);
  rb_define_method(Class_Drawing, "round_rectangle", gmd_round_rectangle, 6);
  rb_define_method(Class_Drawing, "stroke_color=", gmd_set_stroke_color, 1);
  rb_define_method(Class_Drawing, "stroke_color", gmd_get_stroke_color, 0);
  rb_define_method(Class_Drawing, "stroke_opacity=", gmd_set_stroke_opacity, 1);
  rb_define_method(Class_Drawing, "stroke_opacity", gmd_get_stroke_opacity, 0);
  rb_define_method(Class_Drawing, "stroke_width=", gmd_set_stroke_width, 1);
  rb_define_method(Class_Drawing, "stroke_width", gmd_get_stroke_width, 0);
  rb_define_method(Class_Drawing, "text_decoration=", gmd_set_text_decoration, 1);
  rb_define_method(Class_Drawing, "text_decoration", gmd_get_text_decoration, 0);
  rb_define_method(Class_Drawing, "text_encoding=", gmd_set_text_encoding, 1);
  rb_define_method(Class_Drawing, "text_encoding", gmd_get_text_encoding, 0);


  id_new = rb_intern("new");
}
