extern crate sdl2;

use sdl2::EventPump;
use sdl2::pixels::PixelFormatEnum;
use sdl2::rect::Rect;
use sdl2::render::Renderer;
use sdl2::render::Texture;
use pixelbuffer::PixelBuffer;


pub struct Display<'a> {
    height: u32,
    width: u32,
    renderer: Renderer<'a>,
    pub texture: Texture,
    pub events: EventPump
}


impl<'a> Display<'a> {
    pub fn new (w: u32, h: u32) -> Display<'a> {
        let sdl_context = sdl2::init().unwrap();
        let video_subsystem = sdl_context.video().unwrap();

        let window = video_subsystem.window("satcaster", w, h)
            .position_centered()
            .build()
            .unwrap();

        let renderer = window.renderer().present_vsync().build().unwrap();
        let texture = renderer.create_texture_streaming(PixelFormatEnum::RGB24, (w, h)).unwrap();
        let event_pump = sdl_context.event_pump().unwrap();

        Display {
            width: w,
            height: h,
            renderer: renderer,
            texture: texture,
            events: event_pump
        }
    }

    pub fn draw (&mut self, pixels: &PixelBuffer) {
        // TODO: just use self.{w.h} in the closure somehow.
        let w = self.width as usize;
        let h = self.height as usize;

        // Copy to the texture.
        self.texture.with_lock(None, |buffer: &mut [u8], pitch: usize| {
            for y in 0..w {
                for x in 0..h {
                    let offset = y * pitch + x * 3;
                    let color = pixels.get(x, y);
                    buffer[offset + 0] = color;
                    buffer[offset + 1] = color;
                    buffer[offset + 2] = color;
                }
            }
        }).unwrap();

        self.renderer.copy(&(self.texture), None, Some(Rect::new_unwrap(0, 0, self.width, self.height)));
        self.renderer.present();
    }
}


