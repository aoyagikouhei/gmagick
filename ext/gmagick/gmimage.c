#include "gmagick.h"

void 
gmi_free(GmImage *ptr)
{
  if (ptr != (GmImage *)NULL) {
    if (ptr->wand != (MagickWand *)NULL) {
      DestroyMagickWand(ptr->wand);
    }
    ruby_xfree(ptr);
  }
}

VALUE 
gmi_alloc(VALUE klass) {
  GmImage *ptr = ALLOC(GmImage);
  ptr->wand = (MagickWand *)NULL;
  return Data_Wrap_Struct(klass, 0, gmi_free, ptr);
}

/*
 * Document-method: new
 *
 * call-seq:
 *   Gmagick::Image.new -> image
 *   Gmagick::Image.new(path) -> image
 *
 * Create a GraphicsMagick Object
 *
 * [+path+]
 *   image file path
 *
 * Examples:
 *
 *   # Make image object
 *   Gmagick::Image.new
 *
 *   # Make image object with path
 *   Gmagick::Image.new(path)
 *
 */
VALUE
gmi_initialize(int argc, VALUE *argv, VALUE self) {
  if (argc > 1) {
    rb_raise(rb_eArgError, "wrong number of arguments (%d for 0 or 1)", argc);
  }
  volatile GmImage *gmImage;
  Data_Get_Struct(self, GmImage, gmImage);
  gmImage->wand = NewMagickWand();
  if (argc > 0) {
    gmi_read_image(self, argv[0]);
  }
  return Qnil;
}

VALUE 
gmi_read_image(VALUE self, VALUE path_arg) {
  MagickWand *wand = gmu_get_image_wand(self);
  char *path = StringValuePtr(path_arg);
  if (NULL == wand) {
    puts("null");
  }
  MagickPassFail status = MagickReadImage(wand, path);
  gum_check_image_exception(wand, status);
  MagickSetImageFilename(wand, path);
  return Qnil;
}

VALUE 
gmi_write_image(int argc, VALUE *argv, VALUE self) {
  if (argc > 1) {
    rb_raise(rb_eArgError, "wrong number of arguments (%d for 0 or 1)", argc);
  }
  MagickWand *wand = gmu_get_image_wand(self);
  char* path;
  if (argc > 0) {
    path = StringValuePtr(argv[0]);
  } else {
    path = MagickGetImageFilename(wand);
    if (NULL == path) {
      rb_raise(rb_eRuntimeError, "filename never setted");
    }
  }
  MagickPassFail status = MagickWriteImage(wand, path);
  gum_check_image_exception(wand, status);
  return Qnil;
}

VALUE 
gmi_get_width(VALUE self) {
  MagickWand *wand = gmu_get_image_wand(self);
  return LONG2NUM(MagickGetImageWidth(wand));
}

VALUE 
gmi_get_height(VALUE self) {
  MagickWand *wand = gmu_get_image_wand(self);
  return LONG2NUM(MagickGetImageHeight(wand));
}

VALUE 
gmi_get_format(VALUE self) {
  MagickWand *wand = gmu_get_image_wand(self);
  return rb_str_new2(MagickGetImageFormat(wand));
}

VALUE 
gmi_get_depth(VALUE self) {
  MagickWand *wand = gmu_get_image_wand(self);
  return LONG2NUM(MagickGetImageDepth(wand));
}

VALUE 
gmi_get_colors(VALUE self) {
  MagickWand *wand = gmu_get_image_wand(self);
  return LONG2NUM(MagickGetImageColors(wand));
}

VALUE 
gmi_get_resolution(VALUE self) {
  MagickWand *wand = gmu_get_image_wand(self);
  double x;
  double y;
  MagickPassFail status = MagickGetImageResolution(wand, &x, &y);
  gum_check_image_exception(wand, status);
  VALUE ary = rb_ary_new();
  rb_ary_push(ary, DBL2NUM(x));
  rb_ary_push(ary, DBL2NUM(y));
  return ary;
}

VALUE
gmi_get_number_images(VALUE self) {
  MagickWand *wand = gmu_get_image_wand(self);
  return LONG2NUM(MagickGetNumberImages(wand));
}

VALUE 
gmi_read_image_blob(VALUE self, VALUE blob_arg) {
  MagickWand *wand = gmu_get_image_wand(self);
  unsigned char *blob;
  long length;
  Image* image;

  blob = (unsigned char *)gmu_str2cstr(blob_arg, &length);
  MagickPassFail status = MagickReadImageBlob(wand, blob, length);
  gum_check_image_exception(wand, status);
  return Qnil;
}

VALUE
gmi_write_image_blob(VALUE self) {
  MagickWand *image = gmu_get_image_wand(self);
  unsigned char *blob;
  size_t length;
  VALUE result;

  blob = MagickWriteImageBlob(image, &length);
  result = rb_str_new((char *)blob, (long)length);
  MagickRelinquishMemory(blob);
  return result;
}

VALUE 
gmi_resize(int argc, VALUE *argv, VALUE self) {
  if (argc < 2 || argc > 4) {
    rb_raise(rb_eArgError, "wrong number of arguments (%d for 2 or 4)", argc);
  }
  long width = NUM2LONG(argv[0]);
  long height = NUM2LONG(argv[1]);
  int filter = argc > 2 ? NUM2INT(argv[2]) : 0;
  double blur = argc > 3 ? NUM2DBL(argv[3]) : 1.0;

  MagickWand *image = gmu_get_image_wand(self);
  MagickPassFail status = MagickResizeImage(image, width, height, filter, blur);
  gum_check_image_exception(image, status);
  return Qnil;
}

VALUE
gmi_rotate(VALUE self, VALUE pixel_arg, VALUE degree_arg) {
  MagickWand *image = gmu_get_image_wand(self);
  PixelWand *pixel = gmu_get_pixel_string_or_pixel(pixel_arg);
  double degree = NUM2DBL(degree_arg);
  MagickPassFail status = MagickRotateImage(image, pixel, degree);
  gmu_clear_pixel_string_or_pixel(pixel_arg, pixel);
  gum_check_image_exception(image, status);
  return Qnil;
}

VALUE 
gmi_draw(VALUE self, VALUE drawing_arg)
{
  MagickWand *image = gmu_get_image_wand(self);
  DrawingWand *drawing =  gmu_get_drawing_wand(drawing_arg);
  MagickPassFail status = MagickDrawImage(image, drawing);
  gum_check_image_exception(image, status);
  return Qnil;
}

VALUE 
gmi_resample(int argc, VALUE *argv, VALUE self) {
  if (argc < 2 || argc > 4) {
    rb_raise(rb_eArgError, "wrong number of arguments (%d for 2 or 4)", argc);
  }
  long x = NUM2LONG(argv[0]);
  long y = NUM2LONG(argv[1]);
  int filter = argc > 2 ? NUM2INT(argv[2]) : 0;
  double blur = argc > 3 ? NUM2DBL(argv[3]) : 1.0;

  MagickWand *image = gmu_get_image_wand(self);
  MagickPassFail status = MagickResampleImage(image, x, y, filter, blur);
  gum_check_image_exception(image, status);
  return Qnil;
}

VALUE 
gmi_flip(VALUE self) {
  MagickWand *image = gmu_get_image_wand(self);
  MagickPassFail status = MagickFlipImage(image);
  gum_check_image_exception(image, status);
  return Qnil;
}

VALUE 
gmi_flop(VALUE self) {
  MagickWand *image = gmu_get_image_wand(self);
  MagickPassFail status = MagickFlopImage(image);
  gum_check_image_exception(image, status);
  return Qnil;
}

VALUE
gmi_crop(VALUE self, VALUE width_arg, VALUE height_arg, VALUE x_arg, VALUE y_arg) {
  MagickWand *image = gmu_get_image_wand(self);
  unsigned long width = NUM2LONG(width_arg);
  unsigned long height = NUM2LONG(height_arg);
  long x = NUM2LONG(x_arg);
  long y = NUM2LONG(y_arg);
  MagickPassFail status = MagickCropImage(image, width, height, x, y);
  gum_check_image_exception(image, status);
  return Qnil;
}

VALUE
gmi_set_format(VALUE self, VALUE format_arg) {
  MagickWand *image = gmu_get_image_wand(self);
  char *format = StringValuePtr(format_arg);
  MagickPassFail status = MagickSetImageFormat(image, format);
  gum_check_image_exception(image, status);
  return Qnil;
}

VALUE 
gmi_border(VALUE self, VALUE pixel_arg, VALUE width_arg, VALUE height_arg) {
  MagickWand *image = gmu_get_image_wand(self);
  PixelWand *pixel = gmu_get_pixel_string_or_pixel(pixel_arg);
  unsigned long width = NUM2LONG(width_arg);
  unsigned long height = NUM2LONG(height_arg);
  MagickPassFail status = MagickBorderImage(image, pixel, width, height);
  gmu_clear_pixel_string_or_pixel(pixel_arg, pixel);
  gum_check_image_exception(image, status);
  return Qnil;
}

VALUE
gmi_frame(VALUE self, VALUE pixel_arg, VALUE width_arg, VALUE height_arg, VALUE inner_arg, VALUE outer_arg) {
  MagickWand *image = gmu_get_image_wand(self);
  PixelWand *pixel = gmu_get_pixel_string_or_pixel(pixel_arg);
  unsigned long width = NUM2LONG(width_arg);
  unsigned long height = NUM2LONG(height_arg);
  long inner = NUM2LONG(inner_arg);
  long outer = NUM2LONG(outer_arg);
  MagickPassFail status = MagickFrameImage(image, pixel, width, height, inner, outer);
  gmu_clear_pixel_string_or_pixel(pixel_arg, pixel);
  gum_check_image_exception(image, status);
  return Qnil;
}

VALUE
gmi_blur(VALUE self, VALUE radius_arg, VALUE sigma_arg) {
  MagickWand *image = gmu_get_image_wand(self);
  double radius = NUM2DBL(radius_arg);
  double sigma = NUM2DBL(sigma_arg);
  MagickPassFail status = MagickBlurImage(image, radius, sigma);
  gum_check_image_exception(image, status);
  return Qnil;
}

VALUE
gmi_swirl(VALUE self, VALUE degree_arg) {
  MagickWand *image = gmu_get_image_wand(self);
  double degree = NUM2DBL(degree_arg);
  MagickPassFail status = MagickSwirlImage(image, degree);
  gum_check_image_exception(image, status);
  return Qnil;
}

VALUE
gmi_charcoal(VALUE self, VALUE radius_arg, VALUE sigma_arg) {
  MagickWand *image = gmu_get_image_wand(self);
  double radius = NUM2DBL(radius_arg);
  double sigma = NUM2DBL(sigma_arg);
  MagickPassFail status = MagickCharcoalImage(image, radius, sigma);
  gum_check_image_exception(image, status);
  return Qnil;
}

VALUE
gmi_oil_paint(VALUE self, VALUE radius_arg) {
  MagickWand *image = gmu_get_image_wand(self);
  double radius = NUM2DBL(radius_arg);
  MagickPassFail status = MagickOilPaintImage(image, radius);
  gum_check_image_exception(image, status);
  return Qnil;
}

VALUE
gmi_cycle_colormap(VALUE self, VALUE displace_arg) {
  MagickWand *image = gmu_get_image_wand(self);
  long displace = NUM2LONG(displace_arg);
  MagickPassFail status = MagickCycleColormapImage(image, displace);
  gum_check_image_exception(image, status);
  return Qnil;
}

VALUE
gmi_solarize(VALUE self, VALUE threshold_arg) {
  MagickWand *image = gmu_get_image_wand(self);
  double threshold = NUM2DBL(threshold_arg);
  MagickPassFail status = MagickSolarizeImage(image, threshold);
  gum_check_image_exception(image, status);
  return Qnil;
}

VALUE
gmi_shear(VALUE self, VALUE pixel_arg, VALUE x_arg, VALUE y_arg) {
  MagickWand *image = gmu_get_image_wand(self);
  PixelWand *pixel = gmu_get_pixel_string_or_pixel(pixel_arg);
  double x = NUM2DBL(x_arg);
  double y = NUM2DBL(y_arg);
  MagickPassFail status = MagickShearImage(image, pixel, x, y);
  gmu_clear_pixel_string_or_pixel(pixel_arg, pixel);
  gum_check_image_exception(image, status);
  return Qnil;
}
