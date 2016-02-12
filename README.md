satcaster
=========

## !!!

I'm rewriting the Satcaster from scratch in Rust in this branch.

> render from the C++ version:

![render](old_renders/1449064301.bmp)


## Text format

Scenes are specified in a text file with the following format:

```
width height
(cameraPosition) (cameraDirection) fov

(lightPosition)

(sphereCenter) sphereRadius randomSeed
...
```
