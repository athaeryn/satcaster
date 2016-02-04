extern crate cgmath;

use cgmath::Vector3;


pub struct Camera {
    pub pos: Vector3<f32>,
    pub dir: Vector3<f32>,
    pub fov: f32
}

impl Camera {
    pub fn new (px: f32, py: f32, pz: f32) -> Camera {
        Camera {
            pos: Vector3 { x: px, y: py, z: pz },
            dir: Vector3 { x: 0f32, y: 0f32, z: -1f32 },
            fov: 90f32
        }
    }
}
