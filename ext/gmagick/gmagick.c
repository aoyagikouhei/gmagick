#include "gmagick.h"

VALUE gmi_image_alloc(VALUE klass);
VALUE gmi_initialize(int argc, VALUE *argv, VALUE self);
VALUE gmi_read_image(VALUE self, VALUE path_arg);
VALUE gmi_write_image(int argc, VALUE *argv, VALUE self);
VALUE gmi_get_width(VALUE self);
VALUE gmi_get_height(VALUE self);
VALUE gmi_get_format(VALUE self);
VALUE gmi_get_number_images(VALUE self);
VALUE gmi_read_image_blob(VALUE self, VALUE blob_arg);
VALUE gmi_write_image_blob(VALUE self);
VALUE gmi_resize_image(int argc, VALUE *argv, VALUE self);

void 
Init_gmagickn(){
  VALUE mGmagick;
  VALUE cImage;

  InitializeMagick(NULL);
  mGmagick = rb_define_module("Gmagick");
  cImage = rb_define_class_under(mGmagick, "Image", rb_cObject);
  rb_define_alloc_func(cImage, gmi_image_alloc);
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
}

void 
gmi_image_free(GmImage *gmImage)
{
  if (gmImage != (GmImage *)NULL) {
    if (gmImage->wand != (MagickWand *)NULL) {
      DestroyMagickWand(gmImage->wand);
    }
    ruby_xfree(gmImage);
  }
}

VALUE 
gmi_image_alloc(VALUE klass) {
  GmImage *gmImage = ALLOC(GmImage);
  gmImage->wand = (MagickWand *)NULL;
  return Data_Wrap_Struct(klass, 0, gmi_image_free, gmImage);
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
  MagickWand *wand = gmu_get_wand(self);
  char *path = StringValuePtr(path_arg);
  if (NULL == wand) {
    puts("null");
  }
  MagickPassFail status = MagickReadImage(wand, path);
  gmu_check_exception(wand, status);
  MagickSetImageFilename(wand, path);
  return Qnil;
}

VALUE 
gmi_write_image(int argc, VALUE *argv, VALUE self) {
  if (argc > 1) {
    rb_raise(rb_eArgError, "wrong number of arguments (%d for 0 or 1)", argc);
  }
  MagickWand *wand = gmu_get_wand(self);
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
  gmu_check_exception(wand, status);
  return Qnil;
}

VALUE 
gmi_get_width(VALUE self) {
  MagickWand *wand = gmu_get_wand(self);
  return LONG2NUM(MagickGetImageWidth(wand));
}

VALUE 
gmi_get_height(VALUE self) {
  MagickWand *wand = gmu_get_wand(self);
  return LONG2NUM(MagickGetImageHeight(wand));
}

VALUE 
gmi_get_format(VALUE self) {
  MagickWand *wand = gmu_get_wand(self);
  return rb_str_new2(MagickGetImageFormat(wand));
}

VALUE
gmi_get_number_images(VALUE self) {
  MagickWand *wand = gmu_get_wand(self);
  return LONG2NUM(MagickGetNumberImages(wand));
}

VALUE 
gmi_read_image_blob(VALUE self, VALUE blob_arg) {
  MagickWand *wand = gmu_get_wand(self);
  unsigned char *blob;
  long length;
  Image* image;

  blob = (unsigned char *)gmu_str2cstr(blob_arg, &length);
  MagickPassFail status = MagickReadImageBlob(wand, blob, length);
  gmu_check_exception(wand, status);
  return Qnil;
}

VALUE
gmi_write_image_blob(VALUE self) {
  MagickWand *wand = gmu_get_wand(self);
  unsigned char *blob;
  size_t length;
  VALUE result;

  blob = MagickWriteImageBlob(wand, &length);
  result = rb_str_new((char *)blob, (long)length);
  MagickRelinquishMemory(blob);
  return result;
}

VALUE 
gmi_resize_image(int argc, VALUE *argv, VALUE self) {
  if (argc < 2 || argc > 4) {
    rb_raise(rb_eArgError, "wrong number of arguments (%d for 2 or 4)", argc);
  }
  long width = NUM2LONG(argv[0]);
  long height = NUM2LONG(argv[1]);
  int filter = argc > 2 ? NUM2INT(argv[2]) : 0;
  double blur = argc > 3 ? NUM2DBL(argv[3]) : 1.0;

  MagickWand *wand = gmu_get_wand(self);
  MagickPassFail status = MagickResizeImage(wand, width, height, filter, blur);
  gmu_check_exception(wand, status);
  return Qnil;
}

