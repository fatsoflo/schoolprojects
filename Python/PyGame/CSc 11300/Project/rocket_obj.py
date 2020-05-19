import pygame

class Rocket():
    def __init__(self, settings, screen):
        self.image = pygame.image.load("images\rocket.bmp")
        self.screen = screen
        self.settings = settings
        self.rect = self.image.get_rect()
        self.screen_rect = screen.get_rect()
        self.rect.center = self.screen_rect.center
        self.center = float(self.rect.centerx)

        self.moving_left = False
        self.moving_right = False
        self.moving_up = False
        self.moving_down = False

    def update(self):
        if self.moving_right and self.rect.right < self.screen_rect.right:
            self.rect.centerx += self.settings.obj_speed
        if self.moving_left and self.rect.left > 0:
            self.rect.centerx -= self.settings.obj_speed
        if self.moving_up and self.rect.top > self.screen_rect.top:
            self.rect.centery -= self.settings.obj_speed
        if self.moving_down and self.rect.bottom < self.screen_rect.bottom:
            self.rect.centery += self.settings.obj_speed
        #self.rect.centerx = self.center     

    def blitme(self):
        self.screen.blit(self.image, self.rect)