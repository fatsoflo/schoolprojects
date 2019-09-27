import pygame
from pygame.sprite import Sprite

class Dog(Sprite):
    def __init__(self, settings, screen):
        super().__init__()
        self.image = pygame.image.load("images\dog.bmp")
        self.screen = screen
        self.settings = settings
        self.rect = self.image.get_rect()
        self.screen_rect = screen.get_rect()
        self.rect.centerx = self.screen_rect.centerx
        self.rect.bottom = self.screen_rect.bottom
        self.center = float(self.rect.centerx)

        self.moving_left = False
        self.moving_right = False

    def update(self):
        if self.moving_right and self.rect.right < self.screen_rect.right:
            self.rect.centerx += self.settings.obj_speed
        if self.moving_left and self.rect.left > 0:
            self.rect.centerx -= self.settings.obj_speed

    def blitme(self):
        self.screen.blit(self.image, self.rect)