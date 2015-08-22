from vec3 import vec3


class Sphere:
    def __init__(self, pos=vec3(0, 0, 0), r=1):
        self.pos = pos
        self.r = r

    def log(self):
        return "<Sphere r=[%s] pos=[%s, %s, %s]>".format(
                    self.r,
                    self.pos.x,
                    self.pos.y,
                    self.pos.z
                )
