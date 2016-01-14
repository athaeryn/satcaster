use std::fmt;

struct Vec2<T> {
    x: T,
    y: T
}

impl<T: fmt::Display> fmt::Display for Vec2<T> {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "<Vec2 x={} y={}>", self.x, self.y)
    }
}

fn main() {
    let v = Vec2 { x: 1.23f32, y: 4.56f32 };
    println!("Hello again, Satcaster!\n{}", v);
}
