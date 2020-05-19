import pygame

class Game_Over():
    def __init__(self, settings, screen):
        self.font = pygame.font.SysFont('bauhaus93', 50)
        self.text = self.font.render('Game Over!', False, (0,0,0))
        self.text_rect = self.text.get_rect()
        self.screen = screen
        self.screen_rect = self.screen.get_rect()
        self.text_rect.center = self.screen_rect.center
    
    def blitme(self):
        self.screen.blit(self.text, self.text_rect)