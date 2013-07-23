#include "gmagick.h"

VALUE gm_image_alloc(VALUE klass);
VALUE gm_initialize(VALUE self);
VALUE gm_magick_read_image(VALUE self, VALUE path_arg);
VALUE gm_magick_get_width(VALUE self);
VALUE gm_magick_get_height(VALUE self);
VALUE gm_magick_get_format(VALUE self);
VALUE gm_magick_get_number_images(VALUE self);
VALUE gm_magick_read_image_blob(VALUE self, VALUE blob_arg);
VALUE gm_magick_write_image_blob(VALUE self);

void 
Init_gmagickn(){
  VALUE mGmagick;
  VALUE cImage;

  InitializeMagick(NULL);
  mGmagick = rb_define_module("Gmagick");
  cImage = rb_define_class_under(mGmagick, "Image", rb_cObject);
  rb_define_alloc_func(cImage, gm_image_alloc);
  rb_define_private_method(cImage, "initialize", gm_initialize, 0);
  rb_define_method(cImage, "read", gm_magick_read_image, 1);
  rb_define_method(cImage, "width", gm_magick_get_width, 0);
  rb_define_method(cImage, "height", gm_magick_get_height, 0);
  rb_define_method(cImage, "format", gm_magick_get_format, 0);
  rb_define_method(cImage, "count", gm_magick_get_number_images, 0);
  rb_define_method(cImage, "read_blob", gm_magick_read_image_blob, 1);
  rb_define_method(cImage, "write_blob", gm_magick_write_image_blob, 0);
}

void 
gm_image_free(GmImage *gmImage)
{
  DestroyMagickWand(gmImage->wand);
  ruby_xfree(gmImage);
}

VALUE 
gm_image_alloc(VALUE klass) {
  GmImage *gmImage = ALLOC(GmImage);
  return Data_Wrap_Struct(klass, 0, gm_image_free, gmImage);
}

VALUE
gm_initialize(VALUE self) {
  GmImage *gmImage;
  Data_Get_Struct(self, GmImage, gmImage);
  gmImage->wand = NewMagickWand();
  return Qnil;
}

VALUE 
gm_magick_read_image(VALUE self, VALUE path_arg) {
  MagickWand *wand = gmu_get_wand(self);
  char *path = StringValuePtr(path_arg);
  MagickPassFail status = MagickReadImage(wand, path);
  gmu_check_exception(wand, status);
  return Qnil;
}

VALUE 
gm_magick_get_width(VALUE self) {
  MagickWand *wand = gmu_get_wand(self);
  return LONG2NUM(MagickGetImageWidth(wand));
}

VALUE 
gm_magick_get_height(VALUE self) {
  MagickWand *wand = gmu_get_wand(self);
  return LONG2NUM(MagickGetImageHeight(wand));
}

VALUE 
gm_magick_get_format(VALUE self) {
  MagickWand *wand = gmu_get_wand(self);
  return rb_str_new2(MagickGetImageFormat(wand));
}

VALUE
gm_magick_get_number_images(VALUE self) {
  MagickWand *wand = gmu_get_wand(self);
  return LONG2NUM(MagickGetNumberImages(wand));
}

VALUE 
gm_magick_read_image_blob(VALUE self, VALUE blob_arg) {
  MagickWand *wand = gmu_get_wand(self);
  unsigned char *blob;
  long length;
  Image* image;

  blob = (unsigned char *)gmu_str2cstr(blob_arg, &length);
  MagickPassFail status = MagickReadImageBlob(wand, blob, length);
  gmu_check_exception(wand, status);
  return Qnil;
}

VALUE gm_magick_write_image_blob(VALUE self) {
  MagickWand *wand = gmu_get_wand(self);
  unsigned char *blob;
  size_t length;
  VALUE result;

  blob = MagickWriteImageBlob(wand, &length);
  result = rb_str_new((char *)blob, (long)length);
  MagickRelinquishMemory(blob);
  return result;
}

