#include <stdio.h>
#include <ruby.h>
#include <wand/magick_wand.h>

typedef struct {
  MagickWand* wand;
} GmImage;

void gum_check_image_exception(MagickWand *wand, MagickPassFail status);
MagickWand* gmu_get_image_wand(VALUE self);
char* gmu_str2cstr(VALUE src, long *len);

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