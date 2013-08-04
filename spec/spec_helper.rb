$LOAD_PATH.unshift File.expand_path('../../lib', __FILE__)
require 'gmagick'
FILES_PATH = File.dirname(__FILE__) + '/files'
SRC_PATH = FILES_PATH + '/src'
DICE_PATH = SRC_PATH + '/dice.png'
FLOWER_PATH = SRC_PATH + '/flower.jpg'
EARTH_PATH = SRC_PATH + '/earth.gif'
DST_PATH = FILES_PATH + '/dst'
DICE2_PATH = DST_PATH + '/dice2.png'
DICE_ROTATE_PATH = DST_PATH + '/dice_rotate.png'
DICE_ROTATE2_PATH = DST_PATH + '/dice_rotate2.png'
DICE_DRAW_PATH = DST_PATH + '/dice_draw.png'
DICE_RESAMPLE_PATH = DST_PATH + '/dice_resample.png'
DICE_FLIP_PATH = DST_PATH + '/dice_flip.png'
DICE_FLOP_PATH = DST_PATH + '/dice_flop.png'
DICE_CROP_PATH = DST_PATH + '/dice_crop.png'
DICE_BORDER_PATH = DST_PATH + '/dice_border.png'
DICE_FRAME_PATH = DST_PATH + '/dice_frame.png'
DICE_BLUR_PATH = DST_PATH + '/dice_blur.png'
DICE_SWIRL_PATH = DST_PATH + '/dice_swirl.png'
DICE_CHARCOAL_PATH = DST_PATH + '/dice_charcoal.png'
DICE_OIL_PAINT_PATH = DST_PATH + '/dice_oil_paint.png'
DICE_CYCLE_COLORMAP_PATH = DST_PATH + '/dice_cycle_colormap.png'
DICE_SOLARIZE_PATH = DST_PATH + '/dice_solarize.png'
DICE_SHEAR_PATH = DST_PATH + '/dice_shear.png'
DRAW_ANNOTATION_PATH = DST_PATH + '/dice_draw_annotation.png'
DRAW_ARC_PATH = DST_PATH + '/dice_draw_arc.png'
DRAW_CIRCLE_PATH = DST_PATH + '/dice_draw_circle.png'
DRAW_ELLIPSE_PATH = DST_PATH + '/dice_draw_ellipse.png'
DRAW_LINE_PATH = DST_PATH + '/dice_draw_line.png'
DRAW_POINT_PATH = DST_PATH + '/dice_draw_point.png'
DRAW_RECTANGLE_PATH = DST_PATH + '/dice_draw_rectangle.png'

def execute_draw(path)
  image = Gmagick::Image.new(DICE_PATH)
  drawing = Gmagick::Drawing.new
  yield drawing
  image.draw(drawing)
  image.write(path)
end