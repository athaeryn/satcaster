pub struct PixelBuffer {
    data: Vec<i32>,
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

    pub fn set (&mut self, x: usize, y: usize, value: i32) {
        self.data[x + y * self.width] = value;
    }

    pub fn get (&self, x: usize, y: usize) -> i32 {
        self.data[x + y * self.width]
    }

    pub fn add (&mut self, x: usize, y: usize, value: i32) {
        let current = self.get(x, y);
        self.set(x, y, current + value);
    }

    // pub fn print_pbm (&self) {
    //     println!("P1");
    //     println!("{} {}", self.width, self.height);
    //     for y in 0..self.height {
    //         for x in 0..self.width {
    //             if self.get(x, y) > 0 {
    //                 print!(" 0");
    //             } else {
    //                 print!(" 1");
    //             }
    //         }
    //         print!("\n");
    //     }
    // }

    // pub fn print_pgm (&self) {
    //     println!("P2");
    //     println!("{} {}", self.width, self.height);
    //     println!("255");
    //     for y in 0..self.height {
    //         for x in 0..self.width {
    //             print!(" {}", self.get(x, y));
    //         }
    //         print!("\n");
    //     }
    // }
}
