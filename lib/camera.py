from vec3 import vec3


class Camera:
    def __init__(self, pos=vec3(0, 0, 0)):
        self.pos = pos
        self.looktarget = pos

    def lookat(self, target):
        self.looktarget = target

    def log(self):
        print("<Camera pos=[%s, %s, %s] target=[%s, %s, %s]>" %
              (self.pos.x, self.pos.y, self.pos.z,
               self.looktarget.x, self.looktarget.y, self.looktarget.z))
