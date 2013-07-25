#include "gmagick.h"

void 
gmd_free(GmDrawing *ptr)
{
  if (ptr != (GmDrawing *)NULL) {
    if (ptr->wand != (DrawingWand *)NULL) {
      DestroyDrawingWand(ptr->wand);
    }
    ruby_xfree(ptr);
  }
}

VALUE 
gmd_alloc(VALUE klass) {
  GmDrawing *ptr = ALLOC(GmDrawing);
  ptr->wand = (DrawingWand *)NULL;
  return Data_Wrap_Struct(klass, 0, gmd_free, ptr);
}

/*
 * Document-method: new
 *
 * call-seq:
 *   Gmagick::Drawing.new -> drawing
 *
 * Create a GraphicsMagick Drawing Object
 *
 * Examples:
 *
 *   # Make drawing object
 *   Gmagick::Drawing.new
 *
 */
VALUE
gmd_initialize(VALUE self) {
  GmDrawing *ptr;
  Data_Get_Struct(self, GmDrawing, ptr);
  ptr->wand = NewDrawingWand();
  return Qnil;
}
