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
  GmImage *gmImage;
  Data_Get_Struct(self, GmImage, gmImage);
  return gmImage->wand;
}

char* 
gmu_str2cstr(VALUE src, long *length) {
  StringValue(src);
  if (length) {
    *length = RSTRING_LEN(src);
  }
  return RSTRING_PTR(src);
}