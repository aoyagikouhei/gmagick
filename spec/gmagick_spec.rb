require 'spec_helper'

describe Gmagick do
  it 'should have a version number' do
    expect(Gmagick::VERSION).not_to be_nil
  end
end

describe Gmagick::Image do
  before(:all) do
    [DICE2_PATH, DICE_ROTATE_PATH].each do |path|
      if File.exists?(path)
        File.delete(path)
      end
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

  it 'rotate' do
    image = Gmagick::Image.new(DICE_PATH)
    pixel = Gmagick::Pixel.new("#00FF00")
    image.rotate(pixel, 30)
    image.write(DICE_ROTATE_PATH)
  end
end

describe Gmagick::Pixel do
  it 'initialize' do
    pixel = Gmagick::Pixel.new
    expect(pixel).not_to be_nil
    pixel = Gmagick::Pixel.new("#000000")
    expect(pixel).not_to be_nil

    proc do
      pixel = Gmagick::Pixel.new(1, 2)
    end.should raise_error(ArgumentError, "wrong number of arguments (2 for 0 or 1)")

    proc do 
      pixel = Gmagick::Pixel.new(1)
    end.should raise_error(TypeError, "no implicit conversion of Fixnum into String")
  end
end
