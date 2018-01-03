#![recursion_limit="2048"]

#[macro_use]
extern crate stdweb;

use stdweb::web;

extern crate cgmath;

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
    stdweb::initialize();

    let canvas = web::document().get_element_by_id("viewport").unwrap();
    let ctx: stdweb::Value = js!( return @{canvas}.getContext("2d"); );

    let draw_pixel = |ctx: &stdweb::Value, color: &str, pos: (f32, f32)| {
        js!(
            @{ctx}.beginPath();
            @{ctx}.rect(@{pos.0}, @{pos.1}, 1, 1);
            @{ctx}.fillStyle = @{color};
            @{ctx}.fill();
        );
    };

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

    for y in 0..pixels.height {
        for x in 0..pixels.width {
            let value = pixels.get(x, y);
            let color = if value == 0i32 { "black" } else { "white" };
            draw_pixel(&ctx, color, (x as f32, y as f32));
        }
    }

    stdweb::event_loop();
}
