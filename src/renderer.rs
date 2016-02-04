use std::ops::Add;
use std::ops::Mul;
use std::ops::Sub;

use cgmath::Vector;
use cgmath::Vector3;
use cgmath::EuclideanVector;

use pixelbuffer::PixelBuffer;
use scene::Scene;
use sphere::Sphere;

pub fn render(scene: &Scene, pixels: &mut PixelBuffer) {
    let w = pixels.width as f32;
    let h = pixels.height as f32;

    let aspect = w / h;
    let fov = (scene.camera.fov / 2f32 * 3.14f32 / 180f32).tan();

    for y in 0..pixels.height {
        for x in 0..pixels.width {
            // "Screen" coordinates
            let sx = ((2f32 * (x as f32 + 0.5f32) / pixels.width as f32) - 1f32) * aspect * fov;
            let sy = 1f32 - (2f32 * (y as f32 + 0.5f32) / pixels.height as f32) * fov;
            let ray_dir: Vector3<f32> = (Vector3 { x: sx, y: sy, z: 0f32 }).add(scene.camera.pos).add(scene.camera.dir).normalize();
            let ray = Ray {
                pos: scene.camera.pos,
                dir: ray_dir
            };

            let mut nearest_intersection: Option<Intersection> = None;
            for sphere in scene.spheres.iter() {
                // TODO: Actually find the nearest one.
                if let Some(i) = get_intersection(&ray, &sphere) {
                    nearest_intersection = Some(i);
                }
            }

            if let Some(intersection) = nearest_intersection {
                let light_dir = scene.light.sub(intersection.pos).normalize();
                let light_ray = Ray { pos: intersection.pos, dir: light_dir };
                let mut shadowed = false;
                for sphere in scene.spheres.iter() {
                    if let Some(_) = get_intersection(&light_ray, &sphere) {
                        shadowed = true;
                        break;
                    }
                }
                if shadowed {
                    pixels.set(x, y, 0);
                    continue;
                }
                let angle_to_light = light_dir.dot(intersection.normal);
                let mut value = 255f32 * angle_to_light;
                if value < 0f32 { value = 0f32 }
                pixels.set(x, y, value as u8);
            } else {
                pixels.set(x, y, 0);
            }
        }
    }
}


fn get_intersection (ray: &Ray, sphere: &Sphere) -> Option<Intersection> {
    let t0 = get_intersction_dist(&ray, &sphere);
    if t0 < 0f32 { return None }

    let hit = ray.pos.add(ray.dir.mul(t0));
    let normal = hit.sub(sphere.pos).normalize();

    let intersection = Intersection {
        pos: hit,
        normal: normal,
        z: t0
    };

    Some(intersection)
}


// TODO: better variable names and explanation of this.
// I'm using the geometric solution described here:
// http://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
fn get_intersction_dist (ray: &Ray, sphere: &Sphere) -> f32 {
    let no_intersection = -1f32;

    let l = sphere.pos.sub(ray.pos);
    let tca: f32 = l.dot(ray.dir);
    if tca < 0f32 { return no_intersection }
    let d2 = l.length2() - tca * tca;
    if d2 > sphere.rad { return no_intersection }
    let thc = (sphere.rad - d2).sqrt();
    let mut t0 = tca - thc;
    let t1 = tca + thc;

    if t1 < t0 {
        t0 = t1
    }

    if t0 > 0f32 {
        t0
    } else {
        no_intersection
    }
}


struct Ray {
    pos: Vector3<f32>,
    dir: Vector3<f32>
}


struct Intersection {
    pos: Vector3<f32>,
    normal: Vector3<f32>,
    z: f32
}
