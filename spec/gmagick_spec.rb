require 'spec_helper'

describe Gmagick do
  it 'should have a version number' do
    expect(Gmagick::VERSION).not_to be_nil
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
end
