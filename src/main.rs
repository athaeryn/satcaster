extern crate cgmath;
extern crate sdl2;

mod camera;
mod display;
mod pixelbuffer;
mod renderer;
mod scene;
mod sphere;

use camera::Camera;
use display::Display;
use pixelbuffer::PixelBuffer;
use scene::Scene;
use sphere::Sphere;

use sdl2::event::Event;
use sdl2::keyboard::Keycode;

use cgmath::Vector3;


fn main() {
    let mut display = Display::new(500, 500);

    let mut scene;
    {
        let sphere = Sphere::new(2f32, (0f32, 0f32, -5f32));
        let camera = Camera::new(0f32, 0f32, 0f32);
        let light = Vector3 { x: 10f32, y: 10f32, z: 5f32 };

        scene = Scene {
            camera: camera,
            spheres: vec![sphere],
            light: light
        };
    }

    let mut pixels = PixelBuffer::new(500, 500);

    renderer::render(&scene, &mut pixels);

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
