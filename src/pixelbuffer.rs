pub struct PixelBuffer {
    data: Vec<u8>,
    pub width: usize,
    pub height: usize
}

impl PixelBuffer {
    pub fn new (w: usize, h: usize) -> PixelBuffer {
        PixelBuffer {
            data: vec![0; w * h],
            width: w,
            height: h
        }
    }

    pub fn with_same_shape_as(other: &PixelBuffer) -> PixelBuffer {
        PixelBuffer::new(other.width, other.height)
    }

    pub fn set (&mut self, x: usize, y: usize, value: u8) {
        self.data[x + y * self.width] = value;
    }

    pub fn get (&self, x: usize, y: usize) -> u8 {
        self.data[x + y * self.width]
    }
}
