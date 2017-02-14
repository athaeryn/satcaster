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

    pub fn set (&mut self, x: usize, y: usize, value: u8) {
        self.data[x + y * self.width] = value;
    }

    pub fn get (&self, x: usize, y: usize) -> u8 {
        self.data[x + y * self.width]
    }

    pub fn print_pbm (&self) {
        println!("P1");
        println!("{} {}", self.width, self.height);
        for y in 0..self.height {
            for x in 0..self.width {
                if self.get(x, y) > 0 {
                    print!(" 0");
                } else {
                    print!(" 1");
                }
            }
            print!("\n");
        }
    }
}
