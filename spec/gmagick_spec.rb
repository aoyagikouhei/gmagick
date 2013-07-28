require 'spec_helper'

describe Gmagick do
  it 'should have a version number' do
    expect(Gmagick::VERSION).not_to be_nil
  end
end

describe Gmagick::Image do
  before(:all) do
    if !File.exists?(DST_PATH)
      Dir.mkdir(DST_PATH)
    end
    Dir::glob(DST_PATH + "/*.{jpg,png,gif}").each do |f|
      File.delete(f)
    end
  end

  it 'initialize and read' do
    image = Gmagick::Image.new(DICE_PATH)
    expect(image.width).to eq(200)
    expect(image.height).to eq(150)
    expect(image.format).to eq("PNG")
    expect(image.count).to eq(1)

    proc do
      image = Gmagick::Image.new(DICE_PATH, 1)
    end.should raise_error(ArgumentError, "wrong number of arguments (2 for 0 or 1)")

    proc do 
      image = Gmagick::Image.new(1)
    end.should raise_error(TypeError, "no implicit conversion of Fixnum into String")

    proc do
      image = Gmagick::Image.new(DICE_PATH+"a")
    end.should raise_error(RuntimeError, /^Unable to open file/)
  end

  it 'read png image' do
    image = Gmagick::Image.new
    image.read(DICE_PATH)
    expect(image.width).to eq(200)
    expect(image.height).to eq(150)
    expect(image.format).to eq("PNG")
    expect(image.count).to eq(1)
    expect(image.depth).to eq(8)
    expect(image.colors).to eq(7127)
    resolution = image.resolution
    expect(resolution[0]).to eq(72.0)
    expect(resolution[1]).to eq(72.0)
  end

  it 'read jpeg image' do
    image = Gmagick::Image.new
    image.read(FLOWER_PATH)
    expect(image.width).to eq(240)
    expect(image.height).to eq(214)
    expect(image.format).to eq('JPEG')
    expect(image.count).to eq(1)
  end

  it 'read gif image' do
    image = Gmagick::Image.new
    image.read(EARTH_PATH)
    expect(image.width).to eq(200)
    expect(image.height).to eq(200)
    expect(image.format).to eq('GIF')
    expect(image.count).to eq(44)
  end

  it 'read write blob' do
    image = Gmagick::Image.new
    image.read(DICE_PATH)
    image2 = Gmagick::Image.new
    image2.read_blob(image.write_blob)
    expect(image2.width).to eq(200)
    expect(image2.height).to eq(150)
    expect(image2.format).to eq('PNG')
  end

  it 'read write file' do
    image = Gmagick::Image.new(DICE_PATH)
    image.write(DICE2_PATH)
    image2 = Gmagick::Image.new(DICE2_PATH)
    expect(image2.width).to eq(200)
    expect(image2.height).to eq(150)
    expect(image2.format).to eq("PNG")
    expect(image2.count).to eq(1)
    image2.write

    proc do
      image2.write(DICE2_PATH, 1)
    end.should raise_error(ArgumentError, "wrong number of arguments (2 for 0 or 1)")

    proc do 
      image2.write(1)
    end.should raise_error(TypeError, "no implicit conversion of Fixnum into String")
  end

  it 'resize' do
    image = Gmagick::Image.new(DICE_PATH)
    image.resize(100, 75)
    image.write(DICE2_PATH)
    image2 = Gmagick::Image.new(DICE2_PATH)
    expect(image2.width).to eq(100)
    expect(image2.height).to eq(75)
    expect(image2.format).to eq('PNG')
    expect(image2.count).to eq(1)

    proc do
      image.resize(1, 2, 3, 4, 5)
    end.should raise_error(ArgumentError, "wrong number of arguments (5 for 2 or 4)")

    proc do
      image.resize("1", "2")
    end.should raise_error(TypeError, "no implicit conversion of String into Integer")
  end

  it 'resample' do
    image = Gmagick::Image.new(DICE_PATH)
    image.resample(400, 400)
    image.write(DICE_RESAMPLE_PATH)

    image2 = Gmagick::Image.new(DICE_RESAMPLE_PATH)
    expect(image2.width).to eq(1111)
    expect(image2.height).to eq(833)
    expect(image2.format).to eq('PNG')
    expect(image2.count).to eq(1)

    proc do
      image.resample(1, 2, 3, 4, 5)
    end.should raise_error(ArgumentError, "wrong number of arguments (5 for 2 or 4)")

    proc do
      image.resample("1", "2")
    end.should raise_error(TypeError, "no implicit conversion of String into Integer")
  end

  it 'rotate' do
    image = Gmagick::Image.new(DICE_PATH)
    pixel = Gmagick::Pixel.new("#00FF00")
    image.rotate(pixel, 30)
    image.write(DICE_ROTATE_PATH)

    image = Gmagick::Image.new(DICE_PATH)
    image.rotate("red", 30)
    image.write(DICE_ROTATE2_PATH)
  end

  it 'draw' do
    image = Gmagick::Image.new(DICE_PATH)
    drawing = Gmagick::Drawing.new
    pixel = Gmagick::Pixel.new("white")
    drawing.fill_color = pixel
    drawing.stroke_color = "black"
    drawing.stroke_width = 3.0
    drawing.round_rectangle(10, 10, 100, 100, 100, 100)
    image.draw(drawing)
    image.write(DICE_DRAW_PATH)
  end

  it 'flip' do
    image = Gmagick::Image.new(DICE_PATH)
    image.flip
    image.write(DICE_FLIP_PATH)
    image2 = Gmagick::Image.new(DICE_FLIP_PATH)
    expect(image2.width).to eq(200)
    expect(image2.height).to eq(150)
    expect(image2.format).to eq("PNG")
    expect(image2.count).to eq(1)
  end

  it 'flop' do
    image = Gmagick::Image.new(DICE_PATH)
    image.flop
    image.write(DICE_FLOP_PATH)
    image2 = Gmagick::Image.new(DICE_FLOP_PATH)
    expect(image2.width).to eq(200)
    expect(image2.height).to eq(150)
    expect(image2.format).to eq("PNG")
    expect(image2.count).to eq(1)
  end

  it 'crop' do
    image = Gmagick::Image.new(DICE_PATH)
    image.crop(50, 50, 30, 30)
    image.write(DICE_CROP_PATH)
    image2 = Gmagick::Image.new(DICE_CROP_PATH)
    expect(image2.width).to eq(50)
    expect(image2.height).to eq(50)
    expect(image2.format).to eq("PNG")
    expect(image2.count).to eq(1)
  end

  it 'set_format' do
    image = Gmagick::Image.new(DICE_PATH)
    image.format = "JPEG"
    image2 = Gmagick::Image.new
    image2.read_blob(image.write_blob)
    expect(image2.width).to eq(200)
    expect(image2.height).to eq(150)
    expect(image2.format).to eq("JPEG")
    expect(image2.count).to eq(1)
  end

  it 'border' do
    image = Gmagick::Image.new(DICE_PATH)
    image.border("blue", 4, 15)
    image.write(DICE_BORDER_PATH)
    image2 = Gmagick::Image.new(DICE_BORDER_PATH)
    expect(image2.width).to eq(208)
    expect(image2.height).to eq(180)
    expect(image2.format).to eq("PNG")
    expect(image2.count).to eq(1)
  end

  it 'frame' do
    image = Gmagick::Image.new(DICE_PATH)
    image.frame("silver", 20, 20, 5, 5)
    image.write(DICE_FRAME_PATH)
    image2 = Gmagick::Image.new(DICE_FRAME_PATH)
    expect(image2.width).to eq(240)
    expect(image2.height).to eq(190)
    expect(image2.format).to eq("PNG")
    expect(image2.count).to eq(1)
  end

  it 'frame' do
    image = Gmagick::Image.new(DICE_PATH)
    image.blur(8, 3)
    image.write(DICE_BLUR_PATH)
    image2 = Gmagick::Image.new(DICE_BLUR_PATH)
    expect(image2.width).to eq(200)
    expect(image2.height).to eq(150)
    expect(image2.format).to eq("PNG")
    expect(image2.count).to eq(1)
  end

  it 'swirl' do
    image = Gmagick::Image.new(DICE_PATH)
    image.swirl(180)
    image.write(DICE_SWIRL_PATH)
    image2 = Gmagick::Image.new(DICE_SWIRL_PATH)
    expect(image2.width).to eq(200)
    expect(image2.height).to eq(150)
    expect(image2.format).to eq("PNG")
    expect(image2.count).to eq(1)
  end

  it 'charcoal' do
    image = Gmagick::Image.new(DICE_PATH)
    image.charcoal(5, 0.2)
    image.write(DICE_CHARCOAL_PATH)
    image2 = Gmagick::Image.new(DICE_CHARCOAL_PATH)
    expect(image2.width).to eq(200)
    expect(image2.height).to eq(150)
    expect(image2.format).to eq("PNG")
    expect(image2.count).to eq(1)
  end

  it 'oil_paint' do
    image = Gmagick::Image.new(DICE_PATH)
    image.oil_paint(2.5)
    image.write(DICE_OIL_PAINT_PATH)
    image2 = Gmagick::Image.new(DICE_OIL_PAINT_PATH)
    expect(image2.width).to eq(200)
    expect(image2.height).to eq(150)
    expect(image2.format).to eq("PNG")
    expect(image2.count).to eq(1)
  end

  it 'cycle_colormap' do
    image = Gmagick::Image.new(DICE_PATH)
    image.cycle_colormap(100)
    image.cycle_colormap(100)
    image.cycle_colormap(100)
    image.cycle_colormap(100)
    image.write(DICE_CYCLE_COLORMAP_PATH)
    image2 = Gmagick::Image.new(DICE_CYCLE_COLORMAP_PATH)
    expect(image2.width).to eq(200)
    expect(image2.height).to eq(150)
    expect(image2.format).to eq("PNG")
    expect(image2.count).to eq(1)
  end

  it 'solarize' do
    image = Gmagick::Image.new(DICE_PATH)
    image.solarize(100)
    image.write(DICE_SOLARIZE_PATH)
    image2 = Gmagick::Image.new(DICE_SOLARIZE_PATH)
    expect(image2.width).to eq(200)
    expect(image2.height).to eq(150)
    expect(image2.format).to eq("PNG")
    expect(image2.count).to eq(1)
  end

  it 'shear' do
    image = Gmagick::Image.new(DICE_PATH)
    image.shear("white", 5, 70)
    image.write(DICE_SHEAR_PATH)
    image2 = Gmagick::Image.new(DICE_SHEAR_PATH)
    expect(image2.width).to eq(207)
    expect(image2.height).to eq(332)
    expect(image2.format).to eq("PNG")
    expect(image2.count).to eq(1)
  end
end

describe Gmagick::Pixel do
  it 'initialize' do
    pixel = Gmagick::Pixel.new
    expect(pixel).not_to be_nil
    pixel = Gmagick::Pixel.new("#000000")
    expect(pixel).not_to be_nil
    expect(pixel.color).to eq("0,0,0")
    pixel.color = "red"
    expect(pixel.color).to eq("255,0,0")

    proc do
      pixel = Gmagick::Pixel.new(1, 2)
    end.should raise_error(ArgumentError, "wrong number of arguments (2 for 0 or 1)")

    proc do 
      pixel = Gmagick::Pixel.new(1)
    end.should raise_error(TypeError, "no implicit conversion of Fixnum into String")
  end

  it 'color_count' do
    pixel = Gmagick::Pixel.new("#000000")
    pixel.color_count = 100
    expect(pixel.color_count).to eq(100)
  end
end

describe Gmagick::Drawing do
  it 'initialize' do
    drawing = Gmagick::Drawing.new
  end

  it 'fill_color' do
    drawing = Gmagick::Drawing.new
    drawing.fill_color = "red"
    pixel = drawing.fill_color
    expect(pixel.color).to eq("255,0,0")
    pixel.color = "blue"
    pixel2 = drawing.fill_color
    expect(pixel.color).to eq("0,0,255")
  end

  it 'fill_opacity' do
    drawing = Gmagick::Drawing.new
    drawing.fill_opacity = 0.5
    expect(drawing.fill_opacity.round(1)).to eq(0.5)
  end

  it 'stroke_color' do
    drawing = Gmagick::Drawing.new
    drawing.stroke_color = "red"
    pixel = drawing.stroke_color
    expect(pixel.color).to eq("255,0,0")
    pixel.color = "blue"
    pixel2 = drawing.stroke_color
    expect(pixel.color).to eq("0,0,255")
  end

  it 'stroke_opacity' do
    drawing = Gmagick::Drawing.new
    drawing.stroke_opacity = 0.5
    expect(drawing.stroke_opacity.round(1)).to eq(0.5)
  end

  it 'stroke_width' do
    drawing = Gmagick::Drawing.new
    drawing.stroke_width = 10
    expect(drawing.stroke_width).to eq(10)
  end

  it 'font' do
    drawing = Gmagick::Drawing.new
    drawing.font = "system"
    expect(drawing.font).to eq("system")
  end

  it 'font_family' do
    drawing = Gmagick::Drawing.new
    drawing.font_family = "system"
    expect(drawing.font_family).to eq("system")
  end

  it 'font_size' do
    drawing = Gmagick::Drawing.new
    drawing.font_size = 10
    expect(drawing.font_size).to eq(10)
  end

  it 'font_stretch' do
    drawing = Gmagick::Drawing.new
    drawing.font_stretch = 10
    expect(drawing.font_stretch).to eq(10)
  end

  it 'font_style' do
    drawing = Gmagick::Drawing.new
    drawing.font_style = 10
    expect(drawing.font_style).to eq(10)
  end

  it 'font_weight' do
    drawing = Gmagick::Drawing.new
    drawing.font_weight = 10
    expect(drawing.font_weight).to eq(10)
  end

  it 'text_decoration' do
    drawing = Gmagick::Drawing.new
    drawing.text_decoration = 2
    expect(drawing.text_decoration).to eq(2)
  end

  it 'text_encoding' do
    drawing = Gmagick::Drawing.new
    drawing.text_encoding = "UTF-8"
    expect(drawing.text_encoding).to eq("UTF-8")
  end

  it 'annotation' do
    execute_draw(DRAW_ANNOTATION_PATH) do |drawing|
      drawing.font = "Osaka"
      drawing.font_style = 1
      drawing.font_size = 32
      drawing.font_weight = 400
      drawing.fill_color = "black"
      drawing.stroke_color = "black"
      drawing.text_encoding = "UTF-8"
      drawing.annotation(30, 30, "Hello World")
      
      #drawing.round_rectangle(10, 10, 100, 100, 100, 100)
    end
  end
end
