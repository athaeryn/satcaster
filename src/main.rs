extern crate cgmath;
extern crate sdl2;

use cgmath::{Vector3};
use sdl2::pixels::PixelFormatEnum;
use sdl2::rect::Rect;
use sdl2::event::Event;
use sdl2::keyboard::Keycode;

const WIDTH: u32 = 500;
const HEIGHT: u32 = 500;

fn main() {
    let sdl_context = sdl2::init().unwrap();
    let video_subsystem = sdl_context.video().unwrap();

    let window = video_subsystem.window("satcaster", WIDTH, HEIGHT)
        .position_centered()
        .build()
        .unwrap();

    let mut renderer = window.renderer().build().unwrap();

    let mut texture = renderer.create_texture_streaming(PixelFormatEnum::RGB24, (WIDTH, HEIGHT)).unwrap();
    // Create a red-green gradient
    texture.with_lock(None, |buffer: &mut [u8], pitch: usize| {
        for y in 0..WIDTH {
            for x in 0..HEIGHT {
                let offset = y as usize * pitch + x as usize * 3;
                buffer[offset + 0] = 0;
                buffer[offset + 1] = 0;
                buffer[offset + 2] = 0;
            }
        }
    }).unwrap();

    renderer.clear();
    renderer.copy(&texture, None, Some(Rect::new_unwrap(0, 0, WIDTH, HEIGHT)));
    renderer.present();

    let mut event_pump = sdl_context.event_pump().unwrap();

    'running: loop {
        for event in event_pump.poll_iter() {
            match event {
                Event::Quit {..} | Event::KeyDown { keycode: Some(Keycode::Escape), .. } => {
                    break 'running
                },
                _ => {}
            }
        }
        // The rest of the game loop goes here...
    }

    // let v = Vector3 { x: 1.23f32, y: 4.56f32, z: 7.89f32};
    // println!("Hello again, Satcaster!\n{:?}", v);
}
