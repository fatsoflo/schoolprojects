import pygame
from pygame.sprite import Sprite

class Raindrop(Sprite):
    def __init__(self, settings, screen):
        super(Raindrop, self).__init__()
        self.screen = screen
        self.settings = settings

        self.image = pygame.image.load("images\raindrop.bmp")
        self.rect = self.image.get_rect()

        self.rect.x = self.rect.width
        self.rect.y = self.rect.height

        self.x = float(self.rect.x)

    def blitme(self):
        self.screen.blit(self.image, self.rect)

    def update(self):
        self.rect.y += self.settings.obj_speed

    def check_edges(self):
        screen_rect = self.screen.get_rect()
        if self.rect.bottom >= screen_rect.bottom:
            return True