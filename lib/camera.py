import numpy as np

from vec3 import vec3


class Camera:
    def __init__(self, pos=vec3(0, 0, 0)):
        self.pos = pos
        self.direction = vec3(0, 0, -1)

    def lookat(self, target):
        self.direction = target / np.linalg.norm(self.pos + target)

    def __str__(self):
        return "<Camera pos" + \
                repr(tuple(self.pos)) + \
                " dir" + \
                repr(tuple(self.direction)) + \
                "]>"
