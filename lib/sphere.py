from vec3 import vec3


class Sphere:
    def __init__(self, pos=vec3(0, 0, 0), r=1):
        self.pos = pos
        self.r = r

    def __str__(self):
        return "<Sphere pos" + \
                repr(tuple(self.pos)) + \
                " r(" + str(self.r) + ")]>"
