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
gmd_annotation(VALUE self, VALUE x_arg, VALUE y_arg, VALUE text_arg) {
  DrawingWand *drawing = gmu_get_drawing_wand(self);
  double x = NUM2DBL(x_arg);
  double y = NUM2DBL(y_arg);
  char* text = StringValuePtr(text_arg);
  DrawAnnotation(drawing, 50, 50, (unsigned char*)text);
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

VALUE
gmd_set_text_decoration(VALUE self, VALUE decoration_arg) {
  DrawingWand *drawing = gmu_get_drawing_wand(self);
  unsigned long decoration = NUM2LONG(decoration_arg);
  DrawSetTextDecoration(drawing, decoration);
  return Qnil;
}

VALUE
gmd_get_text_decoration(VALUE self) {
  DrawingWand *drawing = gmu_get_drawing_wand(self);
  return LONG2NUM(DrawGetTextDecoration(drawing));
}

VALUE
gmd_set_text_encoding(VALUE self, VALUE encoding_arg) {
  DrawingWand *drawing = gmu_get_drawing_wand(self);
  char *encoding = StringValuePtr(encoding_arg);
  DrawSetTextEncoding(drawing, encoding);
  return Qnil;
}

VALUE
gmd_get_text_encoding(VALUE self) {
  DrawingWand *drawing = gmu_get_drawing_wand(self);
  return rb_str_new2(DrawGetTextEncoding(drawing));
}

VALUE
gmd_arc(VALUE self, VALUE sx_arg, VALUE sy_arg, VALUE ex_arg, VALUE ey_arg, VALUE sd_arg, VALUE ed_arg) {
  DrawingWand *drawing = gmu_get_drawing_wand(self);
  double sx = NUM2DBL(sx_arg);
  double sy = NUM2DBL(sy_arg);
  double ex = NUM2DBL(ex_arg);
  double ey = NUM2DBL(ey_arg);
  double sd = NUM2DBL(sd_arg);
  double ed = NUM2DBL(ed_arg);
  DrawArc(drawing, sx, sy, ex, ey, sd, ed);
  return Qnil;
}

VALUE
gmd_bezier(VALUE self, VALUE points_arg) {
  DrawingWand *drawing = gmu_get_drawing_wand(self);
  return Qnil;
}

VALUE gmd_circle(VALUE self, VALUE ox_arg, VALUE oy_arg, VALUE px_arg, VALUE py_arg) {
  DrawingWand *drawing = gmu_get_drawing_wand(self);
  double ox = NUM2DBL(ox_arg);
  double oy = NUM2DBL(oy_arg);
  double px = NUM2DBL(px_arg);
  double py = NUM2DBL(py_arg);
  DrawCircle(drawing, ox, oy, px, py);
  return Qnil;
}

VALUE gmd_ellipse(int argc, VALUE *argv, VALUE self) {
  if ((argc < 4) || (argc > 6)) {
    rb_raise(rb_eArgError, "wrong number of arguments (%d for 4 or 6)", argc);
  }
  DrawingWand *drawing = gmu_get_drawing_wand(self);
  double ox = NUM2DBL(argv[0]);
  double oy = NUM2DBL(argv[1]);
  double rx = NUM2DBL(argv[2]);
  double ry = NUM2DBL(argv[3]);
  double start = 0;
  double end = 0;
  if (argc > 4) {
    start = NUM2DBL(argv[4]);
  }
  if (argc > 5) {
    end = NUM2DBL(argv[5]);
  }
  DrawEllipse(drawing, ox, oy, rx, ry, start, end);
  return Qnil;
}

VALUE gmd_line(VALUE self, VALUE sx_arg, VALUE sy_arg, VALUE ex_arg, VALUE ey_arg) {
  DrawingWand *drawing = gmu_get_drawing_wand(self);
  double sx = NUM2DBL(sx_arg);
  double sy = NUM2DBL(sy_arg);
  double ex = NUM2DBL(ex_arg);
  double ey = NUM2DBL(ey_arg);
  DrawLine(drawing, sx, sy, ex, ey);
  return Qnil;
}

VALUE gmd_point(VALUE self, VALUE x_arg, VALUE y_arg) {
  DrawingWand *drawing = gmu_get_drawing_wand(self);
  double x = NUM2DBL(x_arg);
  double y = NUM2DBL(y_arg);
  DrawPoint(drawing, x, y);
  return Qnil;
}

VALUE gmd_rectangle(VALUE self, VALUE x1_arg, VALUE y1_arg, VALUE x2_arg, VALUE y2_arg) {
  DrawingWand *drawing = gmu_get_drawing_wand(self);
  double x1 = NUM2DBL(x1_arg);
  double y1 = NUM2DBL(y1_arg);
  double x2 = NUM2DBL(x2_arg);
  double y2 = NUM2DBL(y2_arg);
  DrawRectangle(drawing, x1, y1, x2, y2);
  return Qnil;
}

VALUE gmd_rotate(VALUE self, VALUE degree_arg) {
  DrawingWand *drawing = gmu_get_drawing_wand(self);
  double degree = NUM2DBL(degree_arg);
  DrawRotate(drawing, degree);
  return Qnil;
}

VALUE gmd_scale(VALUE self, VALUE x_arg, VALUE y_arg) {
  DrawingWand *drawing = gmu_get_drawing_wand(self);
  double x = NUM2DBL(x_arg);
  double y = NUM2DBL(y_arg);
  DrawScale(drawing, x, y);
  return Qnil;
}
