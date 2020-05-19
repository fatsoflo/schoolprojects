class Settings():
    def __init__(self):
        self.screen_width = 900
        self.screen_height = 800
        self.bg_color = (255,255,255)
        self.obj_speed = 2.5
        self.bullet_speed = 1.5
        self.bullet_width = 30
        self.bullet_height = 10
        self.bullet_color = (204, 43, 43)
        self.ball_speed = 1
        self.lives_limit = 3

    def set_bg_color(self, *new_color):
        self.bg_color = new_color 