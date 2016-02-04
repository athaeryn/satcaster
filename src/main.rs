extern crate cgmath;
extern crate sdl2;

mod camera;
mod display;
mod ditherer;
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
    let sphere1 = Sphere::new(2f32, (0f32, 0f32, -5f32));
    let sphere2 = Sphere::new(0.2f32, (-2.75f32, -0.5f32, -6f32));
    let camera = Camera::new(0f32, 0f32, 0f32);
    let light = Vector3 { x: 10f32, y: 3f32, z: 2f32 };

    scene = Scene {
        camera: camera,
        spheres: vec![sphere1, sphere2],
        light: light
    };

    let mut t: u64 = 0;

    'running: loop {
        t += 1;

        for event in display.events.poll_iter() {
            match event {
                Event::Quit {..} | Event::KeyDown { keycode: Some(Keycode::Escape), .. } => {
                    break 'running
                },
                _ => {}
            }
        }

        scene.spheres[1].pos.x = (t as f32 / 50f32).sin() * 3f32;
        scene.spheres[1].pos.y = (t as f32 / 50f32).cos() * -0.3f32;
        scene.spheres[1].pos.z = ((t as f32 / 50f32).cos() * 3f32) - 6f32;

        // render
        let mut pixels = PixelBuffer::new(500, 500);
        renderer::render(&scene, &mut pixels);
        pixels = ditherer::dither(&mut pixels);
        display.draw(&pixels);
    }
}
