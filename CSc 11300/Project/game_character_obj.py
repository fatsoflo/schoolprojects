import pygame

class Character():
    def __init__(self, screen):
        img = pygame.image.load("images\faust.bmp")
        img = pygame.transform.scale(img, [200, 211])

        self.screen = screen
        self.image = img
        self.rect = self.image.get_rect()
        self.screen_rect = screen.get_rect()

        self.rect.center = self.screen_rect.center

    def blitme(self):
        self.screen.blit(self.image, self.rect)