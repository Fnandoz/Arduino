'''
http://kivy.org/docs/_modules/kivy/uix/switch.html
Using the lastest version

'''

import urllib

from kivy.uix.widget import Widget
from kivy.animation import Animation
from kivy.properties import BooleanProperty, ObjectProperty, NumericProperty


class Switch(Widget):

    active = BooleanProperty(False)
    touch_control = ObjectProperty(None, allownone=True)
    touch_distance = NumericProperty(0)
    active_norm_pos = NumericProperty(0)

    def on_touch_down(self, touch):
        if self.disabled or self.touch_control is not None:
            return
        if not self.collide_point(*touch.pos):
            return
        touch.grab(self)
        self.touch_distance = 0
        self.touch_control = touch
        return True

    def on_touch_move(self, touch):
        if touch.grab_current is not self:
            return
        self.touch_distance = touch.x - touch.ox
        return True

    def on_touch_up(self, touch):
        if touch.grab_current is not self:
            return
        touch.ungrab(self)
        # depending of the distance, activate by norm pos or invert
        if abs(touch.ox - touch.x) < 5:
            self.active = not self.active

        else:
            self.active = self.active_norm_pos > 0.5
        Animation(active_norm_pos=int(self.active), t='out_quad',
                  d=.2).start(self)
        self.touch_control = None

         if self.active is True:
            url1 = "http://192.168.0.177/?ledon1"
            url2 = "http://192.168.0.177/?ledon2"
            f = urllib.urlopen(url1)
            f = urllib.urlopen(url2)
            f.close()
        else:
            url1 = "http://192.168.0.177/?ledoff1"
            url2 = "http://192.168.0.177/?ledoff2"
            f = urllib.urlopen(url1)
            f = urllib.urlopen(url2)
            f.close()
        return True

if __name__ == '__main__':
    from kivy.base import runTouchApp
    runTouchApp(Switch())
