#[macro_use]
extern crate glium;

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
use std::time::Duration;

use sdl2::event::Event;
use sdl2::keyboard::Keycode;

use cgmath::Vector3;

use std::f32::consts::PI;

type Tri = [Vert; 3];

fn make_sphere (stacks: u8, slices: u8) -> Vec<Tri> {
    let mut tris: Vec<Tri> = Vec::new();
    for stack in 0..stacks {
        let is_cap = stack == 0 || stack == stacks - 1;

        let phi0 = stack as f32 / stacks as f32 * PI;
        let phi1 = (stack + 1) as f32 / stacks as f32 * PI;

        for slice in 0..slices {

            let theta0 = slice as f32 / slices as f32 * PI * 2f32;
            let theta1 = (slice + 1) as f32 / slices as f32 * PI;

            //
            //  t1  t0
            //  b - a p0
            //  | / |
            //  c - d p1
            //

            let a = make_vert_from_phi_theta(phi0, theta0);
            let b = make_vert_from_phi_theta(phi0, theta1);
            let c = make_vert_from_phi_theta(phi1, theta1);
            let d = make_vert_from_phi_theta(phi1, theta0);

            tris.push([a, c, d]);
            if !is_cap {
                tris.push([a, b, c]);
            }
        }
    }

    tris
}

fn make_vert_from_phi_theta(phi: f32, theta: f32) -> Vert {
    Vert::new(
        theta.cos() * phi.sin(),
        phi.cos(),
        theta.sin() * phi.sin()
    )
}


#[derive(Copy, Clone)]
struct Vert {
    position: [f32; 3]
}

impl Vert {
    fn new(x: f32, y: f32, z: f32) -> Vert {
        Vert { position: [x, y, z] }
    }
}

implement_vertex!(Vert, position);

fn main() {
    use glium::{DisplayBuild, Surface};

    let display = glium::glutin::WindowBuilder::new().build_glium().unwrap();

    let sphere: Vec<Tri> = make_sphere(32, 32);
    let mut shape: Vec<Vert> = vec![];
    for tri in sphere {
        for vert in tri.iter() {
            shape.push(*vert);
        }
    }

    let vbuffer = glium::VertexBuffer::new(&display, &shape).unwrap();
    let indices = glium::index::NoIndices(glium::index::PrimitiveType::TrianglesList);

    let vert_src = r#"
        #version 140

        in vec3 position;

        uniform mat4 matrix;

        void main() {
            gl_Position = matrix * vec4(position, 1.0);
        }
    "#;

    let frag_src = r#"
        #version 140

        out vec4 color;

        void main() {
            color = vec4(1.0, 1.0, 1.0, 1.0);
        }
    "#;

    let program = glium::Program::from_source(&display, vert_src, frag_src, None).unwrap();

    let mut t: f32 = -0.5;

    loop {
        t += 0.0002;
        if t > 0.5 {
            t = -0.5;
        }

        let uniforms = uniform! {
            matrix: [
                [t.cos(), t.sin(), 0.0, 0.0],
                [-t.sin(), t.cos(), 0.0, 0.0],
                [0.0, 0.0, 1.0, 0.0],
                [0.0, 0.0, 0.0, 1.0f32]
            ]
        };

        let mut target = display.draw();
        target.clear_color(0.0, 0.0, 0.0, 1.0);
        target.draw(&vbuffer, &indices, &program, &uniforms, &Default::default()).unwrap();
        target.finish().unwrap();

        for event in display.poll_events() {
            match event {
                glium::glutin::Event::Closed => return,
                glium::glutin::Event::KeyboardInput(_, _, Some(code)) => {
                    if code == glium::glutin::VirtualKeyCode::Escape {
                        return
                    }
                },
                _ => ()
            }
        }
    }


//     let mut display = Display::new(500, 500);
//     let mut scene;
//     let sphere1 = Sphere::new(2f32, (0f32, 0f32, -5f32));
//     let sphere2 = Sphere::new(0.1f32, (0f32, 0f32, -5f32));
//     let camera = Camera::new(0f32, 0f32, 0f32);
//     let light = Vector3 { x: 10f32, y: 3f32, z: 2f32 };

//     scene = Scene {
//         camera: camera,
//         spheres: vec![sphere1, sphere2],
//         light: light
//     };

//     let mut t: u64 = 0;

//     let mut mouse_x: i32 = 0;
//     let mut mouse_y: i32 = 0;

//     'running: loop {
//         t += 1;

//         for event in display.events.poll_iter() {
//             match event {
//                 Event::Quit {..} | Event::KeyDown { keycode: Some(Keycode::Escape), .. } => {
//                     break 'running
//                 },
//                 Event::MouseMotion { x, y, .. } => {
//                     mouse_x = x;
//                     mouse_y = y;
//                 },
//                 _ => {}
//             }
//         }

//         // follow the mouse
//         scene.light.x = (mouse_x as f32 - 250f32) / 25f32;
//         scene.light.y = (mouse_y as f32 - 250f32) / -25f32;

//         // orbit
//         scene.spheres[1].pos.x = (t as f32 / 75f32).sin() * 3f32;
//         scene.spheres[1].pos.z = ((t as f32 / 75f32).cos() * 3f32) - 5f32;

//         // render
//         let mut pixels = PixelBuffer::new(500, 500);
//         renderer::render(&scene, &mut pixels);
//         pixels = ditherer::dither(&mut pixels);
//         display.draw(&pixels);
//     }

//     std::thread::sleep(Duration::from_millis(16));
}
