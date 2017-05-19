extern crate cgmath;
extern crate noise;

mod camera;
mod ditherer;
mod pixelbuffer;
mod renderer;
mod scene;
mod sphere;

use camera::Camera;
use pixelbuffer::PixelBuffer;
use scene::Scene;
use sphere::Sphere;

use cgmath::Vector3;


fn main() {
    let sphere1 = Sphere::new(2f32, (0f32, 0f32, -5f32));
    let sphere2 = Sphere::new(0.25f32, (-2.75f32, -0.5f32, -6f32));
    let camera = Camera::new(0f32, 0f32, 0f32);
    let light = Vector3 { x: 10f32, y: 10f32, z: 5f32 };

    let scene = Scene {
        camera: camera,
        spheres: vec![sphere1, sphere2],
        light: light
    };

    // render
    let mut pixels = PixelBuffer::new(500, 500);
    renderer::render(&scene, &mut pixels);
    ditherer::dither(&mut pixels);

    // pixels.print_pbm();
    pixels.print_pgm();
}
