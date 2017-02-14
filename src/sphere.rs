use cgmath::Vector3;

pub struct Sphere {
    pub rad: f32,
    pub pos: Vector3<f32>
}

impl Sphere {
    pub fn new (rad: f32, (x, y, z): (f32, f32, f32)) -> Sphere {
        Sphere {
            rad: rad,
            pos: Vector3 { x: x, y: y, z: z }
        }
    }
}
