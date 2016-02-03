extern crate cgmath;
extern crate sdl2;

mod camera;
mod display;
mod pixelbuffer;
mod renderer;
mod scene;
mod sphere;

use std::ops::Add;
use std::ops::Sub;

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
        let sphere1 = Sphere::new(2f32, (0f32, 0f32, -5f32));
        let sphere2 = Sphere::new(0.25f32, (-2.75f32, -0.5f32, -6f32));
        let camera = Camera::new(0f32, 0f32, 0f32);
        let light = Vector3 { x: 10f32, y: 10f32, z: 5f32 };

        scene = Scene {
            camera: camera,
            spheres: vec![sphere1, sphere2],
            light: light
        };
    }

    let mut pixels = PixelBuffer::new(500, 500);
    let mut dir = 1;

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
        if scene.light.x > 20f32 {
            dir = -1;
        } else if scene.light.x < -20f32 {
            dir = 1;
        }
        match dir {
            1 => scene.light = scene.light.add(Vector3::unit_x()),
            -1 => scene.light = scene.light.sub(Vector3::unit_x()),
            _ => {}
        }
        // render
        renderer::render(&scene, &mut pixels);
        display.draw(&pixels);
    }
}
