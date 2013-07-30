#ifndef _GMAGICK_H_
#define _GMAGICK_H_

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

extern VALUE Module_Gmagick;
extern VALUE Class_Image;
extern VALUE Class_Pixel;
extern VALUE Class_Drawing;

extern ID id_new;

void gum_check_image_exception(MagickWand *wand, MagickPassFail status);
MagickWand* gmu_get_image_wand(VALUE self);
PixelWand* gmu_get_pixel_wand(VALUE self);
DrawingWand* gmu_get_drawing_wand(VALUE self);
char* gmu_str2cstr(VALUE src, long *len);
PixelWand* gmu_get_pixel_string_or_pixel(VALUE pixel_arg);
void gmu_clear_pixel_string_or_pixel(VALUE pixel_arg, PixelWand* pixel);

VALUE gmi_alloc(VALUE klass);
VALUE gmi_initialize(int argc, VALUE *argv, VALUE self);
VALUE gmi_read_image(VALUE self, VALUE path_arg);
VALUE gmi_write_image(int argc, VALUE *argv, VALUE self);
VALUE gmi_get_width(VALUE self);
VALUE gmi_get_height(VALUE self);
VALUE gmi_get_format(VALUE self);
VALUE gmi_get_depth(VALUE self);
VALUE gmi_get_colors(VALUE self);
VALUE gmi_get_resolution(VALUE self);
VALUE gmi_get_number_images(VALUE self);
VALUE gmi_read_image_blob(VALUE self, VALUE blob_arg);
VALUE gmi_write_image_blob(VALUE self);
VALUE gmi_resize(int argc, VALUE *argv, VALUE self);
VALUE gmi_rotate(VALUE self, VALUE pixel_arg, VALUE degree_arg);
VALUE gmi_draw(VALUE self, VALUE drawing_arg);
VALUE gmi_resample(int argc, VALUE *argv, VALUE self);
VALUE gmi_flip(VALUE self);
VALUE gmi_flop(VALUE self);
VALUE gmi_crop(VALUE self, VALUE width_arg, VALUE height_arg, VALUE x_arg, VALUE y_arg);
VALUE gmi_set_format(VALUE self, VALUE format_arg);
VALUE gmi_border(VALUE self, VALUE pixel_arg, VALUE width_arg, VALUE height_arg);
VALUE gmi_frame(VALUE self, VALUE pixel_arg, VALUE width_arg, VALUE height_arg, VALUE inner_arg, VALUE outer_arg);
VALUE gmi_blur(VALUE self, VALUE radius_arg, VALUE sigma_arg);
VALUE gmi_swirl(VALUE self, VALUE degree_arg);
VALUE gmi_charcoal(VALUE self, VALUE radius_arg, VALUE sigma_arg);
VALUE gmi_oil_paint(VALUE self, VALUE radius_arg);
VALUE gmi_cycle_colormap(VALUE self, VALUE displace_arg);
VALUE gmi_solarize(VALUE self, VALUE threshold_arg);
VALUE gmi_shear(VALUE self, VALUE pixel_arg, VALUE x_arg, VALUE y_arg);

VALUE gmp_alloc(VALUE klass);
VALUE gmp_initialize(int argc, VALUE *argv, VALUE self);
VALUE gmp_set_color(VALUE self, VALUE color_arg);
VALUE gmp_get_color(VALUE self);
VALUE gmp_set_color_count(VALUE self, VALUE color_count_arg);
VALUE gmp_get_color_count(VALUE self);

VALUE gmd_alloc(VALUE klass);
VALUE gmd_initialize(VALUE self);
VALUE gmd_annotation(VALUE self, VALUE x_arg, VALUE y_arg, VALUE text_arg);
VALUE gmd_arc(VALUE self, VALUE sx_arg, VALUE sy_arg, VALUE ex_arg, VALUE ey_arg, VALUE sd_arg, VALUE ed_arg);
VALUE gmd_bezier(VALUE self, VALUE points_arg);
VALUE gmd_set_fill_color(VALUE self, VALUE pixel_arg);
VALUE gmd_get_fill_color(VALUE self);
VALUE gmd_set_fill_opacity(VALUE self, VALUE opacity_arg);
VALUE gmd_get_fill_opacity(VALUE self);
VALUE gmd_set_stroke_color(VALUE self, VALUE pixel_arg);
VALUE gmd_get_stroke_color(VALUE self);
VALUE gmd_set_stroke_opacity(VALUE self, VALUE opacity_arg);
VALUE gmd_get_stroke_opacity(VALUE self);
VALUE gmd_set_stroke_width(VALUE self, VALUE width_arg);
VALUE gmd_get_stroke_width(VALUE self);
VALUE gmd_round_rectangle(VALUE self, VALUE x1_arg, VALUE y1_arg, VALUE x2_arg, VALUE y2_arg, VALUE rx_arg, VALUE ry_arg);
VALUE gmd_set_font(VALUE self, VALUE name_arg);
VALUE gmd_get_font(VALUE self);
VALUE gmd_set_font_family(VALUE self, VALUE family_arg);
VALUE gmd_get_font_family(VALUE self);
VALUE gmd_set_font_size(VALUE self, VALUE pointsize_arg);
VALUE gmd_get_font_size(VALUE self);
VALUE gmd_set_font_stretch(VALUE self, VALUE stretch_arg);
VALUE gmd_get_font_stretch(VALUE self);
VALUE gmd_set_font_style(VALUE self, VALUE style_arg);
VALUE gmd_get_font_style(VALUE self);
VALUE gmd_set_font_weight(VALUE self, VALUE weight_arg);
VALUE gmd_get_font_weight(VALUE self);
VALUE gmd_set_text_decoration(VALUE self, VALUE decoration_arg);
VALUE gmd_get_text_decoration(VALUE self);
VALUE gmd_set_text_encoding(VALUE self, VALUE encoding_arg);
VALUE gmd_get_text_encoding(VALUE self);
#endif
