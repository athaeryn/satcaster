use cgmath::{Vector3};


pub struct Sphere {
    rad: f32,
    pos: Vector3<f32>
}

impl Sphere {
    pub fn new (rad: f32, (x, y, z): (f32, f32, f32)) -> Sphere {
        Sphere {
            rad: rad,
            pos: Vector3 { x: x, y: y, z: z }
        }
    }
}
