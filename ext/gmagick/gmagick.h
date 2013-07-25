#include <stdio.h>
#include <ruby.h>
#include <wand/magick_wand.h>

typedef struct {
  MagickWand* wand;
} GmImage;

typedef struct {
  PixelWand* wand;
} GmPixel;

typedef struct {
  DrawingWand* wand;
} GmDrawing;

void gum_check_image_exception(MagickWand *wand, MagickPassFail status);
MagickWand* gmu_get_image_wand(VALUE self);
PixelWand* gmu_get_pixel_wand(VALUE self);
DrawingWand* gmu_get_drawing_wand(VALUE self);
char* gmu_str2cstr(VALUE src, long *len);

VALUE gmi_alloc(VALUE klass);
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
VALUE gmi_rotate_image(VALUE self, VALUE pixel_arg, VALUE degree_arg);
VALUE gmi_draw_image(VALUE self, VALUE drawing_arg);

VALUE gmp_alloc(VALUE klass);
VALUE gmp_initialize(int argc, VALUE *argv, VALUE self);
VALUE gmp_set_color(VALUE self, VALUE color_arg);

VALUE gmd_alloc(VALUE klass);
VALUE gmd_initialize(VALUE self);