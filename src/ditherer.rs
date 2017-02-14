extern crate rand;

use pixelbuffer::PixelBuffer;

pub fn dither (pixels: &mut PixelBuffer) {
    let mut error_buffer = PixelBuffer::new(pixels.width + 1, pixels.height + 1);

    for y in 0..(pixels.width - 1) {
        for x in 0..(pixels.height - 1) {
            let raw = pixels.get(x, y) + error_buffer.get(x, y);

            let high_diff = raw - 255;
            let low_diff = raw;

            let error = if high_diff.abs() <= low_diff.abs() {
                pixels.set(x, y, 255);
                high_diff
            } else {
                pixels.set(x, y, 0);
                low_diff
            };

            // Floyd-Steinberg
            error_buffer.add(x + 1, y, error * 7 / 16);
            error_buffer.add(x - 1, y + 1, error * 3 / 16);
            error_buffer.add(x, y + 1, error * 5 / 16);
            error_buffer.add(x + 1, y + 1, error / 16);

            // Atkinson
            // let eighth = error / 8;
            // error_buffer.add(x + 1, y, eighth);
            // error_buffer.add(x + 2, y, eighth);
            // error_buffer.add(x - 1, y + 1, eighth);
            // error_buffer.add(x, y + 1, eighth);
            // error_buffer.add(x + 1, y + 1, eighth);
            // error_buffer.add(x, y + 2, eighth);
        }
    }
}
