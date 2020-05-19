import pygame
from pygame.sprite import Sprite
from random import randint

class Ball(Sprite):
    def __init__(self, settings, screen):
        super(Ball, self).__init__()
        self.screen = screen
        self.settings = settings

        self.image = pygame.image.load("images\ball.bmp")
        self.rect = self.image.get_rect()

        self.screen_rect = screen.get_rect()
        self.rect.x = randint(0, self.screen_rect.right)
        self.rect.y = self.screen_rect.top

        self.x = float(self.rect.x)

    def draw(self):
        self.screen.blit(self.image, self.rect)

    def update(self):
        self.rect.y += self.settings.ball_speed

    def check_edges(self):
        screen_rect = self.screen.get_rect()
        if self.rect.bottom >= screen_rect.bottom:
            return True