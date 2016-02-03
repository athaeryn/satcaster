use cgmath::Vector3;

use camera::Camera;
use sphere::Sphere;

pub struct Scene {
    pub camera: Camera,
    pub spheres: Vec<Sphere>,
    pub lights: Vec<Vector3<f32>>
}

