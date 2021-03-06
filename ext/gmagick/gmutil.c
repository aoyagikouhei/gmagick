#include "gmagick.h"

void 
gum_check_image_exception(MagickWand *wand, MagickPassFail status) {
  if (status != MagickPass) {
    char *description;
    ExceptionType severity;

    description=MagickGetException(wand,&severity);
    rb_raise(rb_eRuntimeError, "%s", description);
  }
}

MagickWand*
gmu_get_image_wand(VALUE self) {
  GmImage *ptr;
  Data_Get_Struct(self, GmImage, ptr);
  return ptr->wand;
}

char* 
gmu_str2cstr(VALUE src, long *length) {
  StringValue(src);
  if (length) {
    *length = RSTRING_LEN(src);
  }
  return RSTRING_PTR(src);
}

PixelWand* 
gmu_get_pixel_wand(VALUE self) {
  GmPixel *ptr;
  Data_Get_Struct(self, GmPixel, ptr);
  return ptr->wand;
}

DrawingWand*
gmu_get_drawing_wand(VALUE self) {
  GmDrawing *ptr;
  Data_Get_Struct(self, GmDrawing, ptr);
  return ptr->wand;
}

PixelWand* 
gmu_get_pixel_string_or_pixel(VALUE color_arg) {
  PixelWand *pixel;
  if (T_STRING == TYPE(color_arg)) {
    pixel = NewPixelWand();
    char *color = StringValuePtr(color_arg);
    PixelSetColor(pixel, color);
  } else {
    pixel = gmu_get_pixel_wand(color_arg);
  }
  return pixel;
}

void 
gmu_clear_pixel_string_or_pixel(VALUE pixel_arg, PixelWand* pixel) {
  if (T_STRING == TYPE(pixel_arg)) {
    DestroyPixelWand(pixel);
  }
}