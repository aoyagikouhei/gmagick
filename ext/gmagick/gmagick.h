#include <stdio.h>
#include <ruby.h>
#include <wand/magick_wand.h>

typedef struct {
  MagickWand* wand;
} GmImage;

void gmu_check_exception(MagickWand *wand, MagickPassFail status);
MagickWand* gmu_get_wand(VALUE self);
char* gmu_str2cstr(VALUE src, long *len);