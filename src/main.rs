extern crate cgmath;
extern crate sdl2;

mod pixelbuffer;
mod camera;
mod display;
mod sphere;
mod scene;

use pixelbuffer::PixelBuffer;
use camera::Camera;
use display::Display;
use sphere::Sphere;
use scene::Scene;

use sdl2::event::Event;
use sdl2::keyboard::Keycode;

use cgmath::Vector3;


fn main() {
    let mut display = Display::new(500, 500);

    let mut scene;
    {
        let sphere = Sphere::new(1f32, (0f32, 0f32, 0f32));
        let camera = Camera::new(0f32, 0f32, 10f32);
        let light = Vector3 { x: 5f32, y: -5f32, z: 5f32 };

        scene = Scene {
            camera: camera,
            spheres: vec![sphere],
            lights: vec![light]
        };
    }

    let mut pixels = PixelBuffer::new(500, 500);

    // // Draw to the pixels.
    // for y in 0..pixels.height as usize {
    //     for x in 0..pixels.width as usize {
    //         pixels.set(x, y, color);
    //     }
    // }

    display.draw(&pixels);

    'running: loop {
        for event in display.events.poll_iter() {
            match event {
                Event::Quit {..} | Event::KeyDown { keycode: Some(Keycode::Escape), .. } => {
                    break 'running
                },
                _ => {}
            }
        }
        // update
        // render
    }
}
