extern crate cgmath;
extern crate sdl2;

mod pixelbuffer;
mod camera;
mod display;
mod sphere;

use pixelbuffer::{PixelBuffer};
use camera::{Camera};
use display::{Display};
use sphere::{Sphere};

use sdl2::event::Event;
use sdl2::keyboard::Keycode;


fn main() {
    let mut display = Display::new(500, 500);

    let sphere = Sphere::new(1f32, (0f32, 0f32, 0f32));
    let camera = Camera::new(0f32, 0f32, 10f32);
    let mut pixels = PixelBuffer::new(500, 500);

    let mut count: i8 = 0;
    let mut dir: i8 = 1;

    'running: loop {
        for event in display.events.poll_iter() {
            match event {
                Event::Quit {..} | Event::KeyDown { keycode: Some(Keycode::Escape), .. } => {
                    break 'running
                },
                _ => {}
            }
        }

        count += dir;
        if count > 32 {
            dir = -1;
        } else if count < 8 {
            dir = 1;
        }

        // Draw to the pixels.
        for y in 0..pixels.height as usize {
            for x in 0..pixels.width as usize {
                let color = if x % count as usize == 0 { 255 } else { 0 };
                pixels.set(x, y, color);
            }
        }

        display.draw(&pixels);
    }
}
