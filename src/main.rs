extern crate cgmath;
extern crate sdl2;

use cgmath::{Vector3};
use sdl2::pixels::PixelFormatEnum;
use sdl2::rect::Rect;
use sdl2::event::Event;
use sdl2::keyboard::Keycode;

const WIDTH: u32 = 500;
const HEIGHT: u32 = 500;



struct Sphere {
    rad: f32,
    pos: Vector3<f32>
}

impl Sphere {
    fn new (rad: f32, (x, y, z): (f32, f32, f32)) -> Sphere {
        Sphere {
            rad: rad,
            pos: Vector3 { x: x, y: y, z: z }
        }
    }
}



struct Camera {
    pos: Vector3<f32>,
    dir: Vector3<f32>
}

impl Camera {
    fn new (px: f32, py: f32, pz: f32) -> Camera {
        Camera {
            pos: Vector3 { x: px, y: py, z: pz },
            dir: Vector3 { x: 0f32, y: 0f32, z: -1f32 }
        }
    }
}



fn main() {
    let sdl_context = sdl2::init().unwrap();
    let video_subsystem = sdl_context.video().unwrap();

    let window = video_subsystem.window("satcaster", WIDTH, HEIGHT)
        .position_centered()
        .build()
        .unwrap();

    let mut renderer = window.renderer().present_vsync().build().unwrap();
    let mut texture = renderer.create_texture_streaming(PixelFormatEnum::RGB24, (WIDTH, HEIGHT)).unwrap();



    let sphere = Sphere::new(1f32, (0f32, 0f32, 0f32));
    let camera = Camera::new(0f32, 0f32, 10f32);
    let mut pixels = [[0u8; WIDTH as usize]; HEIGHT as usize];

    let mut event_pump = sdl_context.event_pump().unwrap();

    let mut count: i8 = 0;
    let mut dir: i8 = 1;

    'running: loop {
        for event in event_pump.poll_iter() {
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
        for y in 0..WIDTH as usize {
            for x in 0..HEIGHT as usize {
                let color = if x % count as usize == 0 { 255 } else { 0 };
                pixels[x][y] = color;
            }
        }

        // Copy to the texture.
        texture.with_lock(None, |buffer: &mut [u8], pitch: usize| {
            for y in 0..WIDTH as usize {
                for x in 0..HEIGHT as usize {
                    let offset = y * pitch + x * 3;
                    let color = pixels[x][y];
                    buffer[offset + 0] = color;
                    buffer[offset + 1] = color;
                    buffer[offset + 2] = color;
                }
            }
        }).unwrap();

        // Display the texture.
        renderer.copy(&texture, None, Some(Rect::new_unwrap(0, 0, WIDTH, HEIGHT)));
        renderer.present();

        // std::thread::sleep_ms(16);
    }
}
