import pygame

class Shooter():
    def __init__(self, settings, screen):
        img = pygame.image.load("images\rocket.bmp")
        self.image = pygame.transform.rotozoom(img, -90, 1)
        self.screen = screen
        self.settings = settings
        self.rect = self.image.get_rect()
        self.screen_rect = screen.get_rect()
        self.rect.left = 0

        self.moving_up = False
        self.moving_down = False

    def update(self):
        if self.moving_up and self.rect.top > self.screen_rect.top:
            self.rect.centery -= self.settings.obj_speed
        if self.moving_down and self.rect.bottom < self.screen_rect.bottom:
            self.rect.centery += self.settings.obj_speed

    def blitme(self):
        self.screen.blit(self.image, self.rect)