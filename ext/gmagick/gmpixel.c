#include "gmagick.h"

void 
gmp_free(GmPixel *ptr)
{
  if (ptr != (GmPixel *)NULL) {
    if (ptr->wand != (PixelWand *)NULL) {
      DestroyPixelWand(ptr->wand);
    }
    ruby_xfree(ptr);
  }
}

VALUE 
gmp_alloc(VALUE klass) {
  GmPixel *ptr = ALLOC(GmPixel);
  ptr->wand = (PixelWand *)NULL;
  return Data_Wrap_Struct(klass, 0, gmp_free, ptr);
}

/*
 * Document-method: new
 *
 * call-seq:
 *   Gmagick::Pixel.new -> pixel
 *   Gmagick::Pixel.new(color) -> pixel
 *
 * Create a GraphicsMagick Object
 *
 * [+color+]
 *   initialize color
 *
 * Examples:
 *
 *   # Make pixel object
 *   Gmagick::Pixel.new
 *
 *   # Make pixel object with color
 *   Gmagick::Pixel.new("#000000")
 *
 */
VALUE
gmp_initialize(int argc, VALUE *argv, VALUE self) {
  if (argc > 1) {
    rb_raise(rb_eArgError, "wrong number of arguments (%d for 0 or 1)", argc);
  }
  volatile GmPixel *ptr;
  Data_Get_Struct(self, GmPixel, ptr);
  ptr->wand = NewPixelWand();
  if (argc > 0) {
    gmp_set_color(self, argv[0]);
  }
  return Qnil;
}

VALUE
gmp_set_color(VALUE self, VALUE color_arg) {
  char *color = StringValuePtr(color_arg);
  PixelWand *wand = gmu_get_pixel_wand(self);
  PixelSetColor(wand, color);
  return Qnil;
}