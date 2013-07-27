#include "gmagick.h"

static void 
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

VALUE
gmd_set_fill_color(VALUE self, VALUE pixel_arg) {
  DrawingWand *drawing = gmu_get_drawing_wand(self);
  PixelWand *pixel =  gmu_get_pixel_string_or_pixel(pixel_arg);
  DrawSetFillColor(drawing, pixel);
  gmu_clear_pixel_string_or_pixel(pixel_arg, pixel);
  return Qnil;
}

VALUE
gmd_get_fill_color(VALUE self) {
  DrawingWand *drawing = gmu_get_drawing_wand(self);
  VALUE pixel_value = rb_funcall(Class_Pixel, id_new, 0);
  PixelWand *pixel = gmu_get_pixel_wand(pixel_value);
  DrawGetFillColor(drawing, pixel);
  return pixel_value;
}

VALUE
gmd_set_fill_opacity(VALUE self, VALUE opacity_arg) {
  DrawingWand *drawing = gmu_get_drawing_wand(self);
  double opacity = NUM2DBL(opacity_arg);
  DrawSetFillOpacity(drawing, opacity);
  return Qnil;
}

VALUE
gmd_get_fill_opacity(VALUE self) {
  DrawingWand *drawing = gmu_get_drawing_wand(self);
  return DBL2NUM(DrawGetFillOpacity(drawing));
}

VALUE gmd_set_stroke_color(VALUE self, VALUE pixel_arg) {
  DrawingWand *drawing = gmu_get_drawing_wand(self);
  PixelWand *pixel =  gmu_get_pixel_string_or_pixel(pixel_arg);
  DrawSetStrokeColor(drawing, pixel);
  gmu_clear_pixel_string_or_pixel(pixel_arg, pixel);
  return Qnil;
}

VALUE
gmd_get_stroke_color(VALUE self) {
  DrawingWand *drawing = gmu_get_drawing_wand(self);
  VALUE pixel_value = rb_funcall(Class_Pixel, id_new, 0);
  PixelWand *pixel = gmu_get_pixel_wand(pixel_value);
  DrawGetStrokeColor(drawing, pixel);
  return pixel_value;
}

VALUE
gmd_set_stroke_opacity(VALUE self, VALUE opacity_arg) {
  DrawingWand *drawing = gmu_get_drawing_wand(self);
  double opacity = NUM2DBL(opacity_arg);
  DrawSetStrokeOpacity(drawing, opacity);
  return Qnil;
}

VALUE
gmd_get_stroke_opacity(VALUE self) {
  DrawingWand *drawing = gmu_get_drawing_wand(self);
  return DBL2NUM(DrawGetStrokeOpacity(drawing));
}

VALUE 
gmd_set_stroke_width(VALUE self, VALUE width_arg) {
  DrawingWand *drawing = gmu_get_drawing_wand(self);
  double width = NUM2DBL(width_arg);
  DrawSetStrokeWidth(drawing, width);
  return Qnil;
}

VALUE 
gmd_get_stroke_width(VALUE self) {
  DrawingWand *drawing = gmu_get_drawing_wand(self);
  return DBL2NUM(DrawGetStrokeWidth(drawing));
}

VALUE gmd_round_rectangle(VALUE self, VALUE x1_arg, VALUE y1_arg, VALUE x2_arg, VALUE y2_arg, VALUE rx_arg, VALUE ry_arg) {
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

VALUE
gmd_set_font(VALUE self, VALUE name_arg) {
  DrawingWand *drawing = gmu_get_drawing_wand(self);
  char *name = StringValuePtr(name_arg);
  DrawSetFont(drawing, name);
  return Qnil;
}

VALUE
gmd_get_font(VALUE self) {
  DrawingWand *drawing = gmu_get_drawing_wand(self);
  return rb_str_new2(DrawGetFont(drawing));
}

VALUE
gmd_set_font_family(VALUE self, VALUE family_arg) {
  DrawingWand *drawing = gmu_get_drawing_wand(self);
  char *family = StringValuePtr(family_arg);
  DrawSetFontFamily(drawing, family);
  return Qnil;
}

VALUE
gmd_get_font_family(VALUE self) {
  DrawingWand *drawing = gmu_get_drawing_wand(self);
  return rb_str_new2(DrawGetFontFamily(drawing));
}

VALUE
gmd_set_font_size(VALUE self, VALUE pointsize_arg) {
  DrawingWand *drawing = gmu_get_drawing_wand(self);
  double pointsize = NUM2DBL(pointsize_arg);
  DrawSetFontSize(drawing, pointsize);
  return Qnil;
}

VALUE
gmd_get_font_size(VALUE self) {
  DrawingWand *drawing = gmu_get_drawing_wand(self);
  return DBL2NUM(DrawGetFontSize(drawing));
}

VALUE
gmd_set_font_stretch(VALUE self, VALUE stretch_arg) {
  DrawingWand *drawing = gmu_get_drawing_wand(self);
  unsigned long stretch = NUM2LONG(stretch_arg);
  DrawSetFontStretch(drawing, stretch);
  return Qnil;
}

VALUE
gmd_get_font_stretch(VALUE self) {
  DrawingWand *drawing = gmu_get_drawing_wand(self);
  return LONG2NUM(DrawGetFontStretch(drawing));
}

VALUE
gmd_set_font_style(VALUE self, VALUE style_arg) {
  DrawingWand *drawing = gmu_get_drawing_wand(self);
  unsigned long style = NUM2LONG(style_arg);
  DrawSetFontStyle(drawing, style);
  return Qnil;
}

VALUE
gmd_get_font_style(VALUE self) {
  DrawingWand *drawing = gmu_get_drawing_wand(self);
  return LONG2NUM(DrawGetFontStyle(drawing));
}

VALUE
gmd_set_font_weight(VALUE self, VALUE weight_arg) {
  DrawingWand *drawing = gmu_get_drawing_wand(self);
  unsigned long weight = NUM2LONG(weight_arg);
  DrawSetFontWeight(drawing, weight);
  return Qnil;
}

VALUE
gmd_get_font_weight(VALUE self) {
  DrawingWand *drawing = gmu_get_drawing_wand(self);
  return LONG2NUM(DrawGetFontWeight(drawing));
}
