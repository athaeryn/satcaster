extern crate rand;

use pixelbuffer::PixelBuffer;

pub fn dither (pixels: &mut PixelBuffer) {
    // let mut output = PixelBuffer::with_same_shape_as(pixels);

    for y in 0..pixels.width {
        for x in 0..pixels.height {
            let raw = pixels.get(x, y);
            let value = if raw > rand::random::<u8>() {
                255
            } else {
                0
            };
            pixels.set(x, y, value);
        }
    }
}
