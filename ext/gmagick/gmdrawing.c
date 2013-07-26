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

VALUE gmd_set_fill_color(VALUE self, VALUE pixel_arg) {
  DrawingWand *drawing = gmu_get_drawing_wand(self);
  PixelWand *pixel =  gmu_get_pixel_string_or_pixel(pixel_arg);
  DrawSetFillColor(drawing, pixel);
  gmu_clear_pixel_string_or_pixel(pixel_arg, pixel);
  return Qnil;
}

VALUE gmd_set_stroke_color(VALUE self, VALUE pixel_arg) {
  DrawingWand *drawing = gmu_get_drawing_wand(self);
  PixelWand *pixel =  gmu_get_pixel_string_or_pixel(pixel_arg);
  DrawSetStrokeColor(drawing, pixel);
  gmu_clear_pixel_string_or_pixel(pixel_arg, pixel);
  return Qnil;
}

VALUE 
gmd_set_stroke_width(VALUE self, VALUE width_arg) {
  DrawingWand *drawing = gmu_get_drawing_wand(self);
  double width = NUM2DBL(width_arg);
  DrawSetStrokeWidth(drawing, width);
  return Qnil;
}

VALUE gmd_draw_round_rectangle(VALUE self, VALUE x1_arg, VALUE y1_arg, VALUE x2_arg, VALUE y2_arg, VALUE rx_arg, VALUE ry_arg) {
  DrawingWand *drawing = gmu_get_drawing_wand(self);
  double x1 = NUM2DBL(x1_arg);
  double y1 = NUM2DBL(y1_arg);
  double x2 = NUM2DBL(x2_arg);
  double y2 = NUM2DBL(y2_arg);
  double rx = NUM2DBL(rx_arg);
  double ry = NUM2DBL(ry_arg);
  DrawRoundRectangle(drawing, x1, y1, x2, y2, rx, ry);
  return Qnil;
}