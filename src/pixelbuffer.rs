pub struct PixelBuffer {
    data: Vec<u8>,
    pub width: usize,
    pub height: usize
}

impl PixelBuffer {
    pub fn new (width: u32, height: u32) -> PixelBuffer {
        let w = width as usize;
        let h = height as usize;
        let capacity = w * h;
        let mut vec = Vec::with_capacity(capacity);
        for _ in 0..capacity {
            vec.push(0);
        }
        PixelBuffer {
            data: vec,
            width: w,
            height: h
        }
    }

    pub fn set (&mut self, x: usize, y: usize, value: u8) {
        self.data[x + y * self.width] = value;
    }

    pub fn get (&self, x: usize, y: usize) -> u8 {
        self.data[x + y * self.width]
    }
}
