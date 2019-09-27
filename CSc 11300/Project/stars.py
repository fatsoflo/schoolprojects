import pygame
from pygame.sprite import Group
import functions as f
import settings
from settings import Settings
import star_obj
from star_obj import Star

def run_game():
    pygame.init()
    settings = Settings()
    screen = pygame.display.set_mode((settings.screen_width, settings.screen_height))
    pygame.display.set_caption("Stars")
    star = Star(settings, screen)
    stars = Group()
    f.create_star_grid(settings, screen, stars, star)

    while True: 
        f.update_screen_grid(settings, screen, stars)
        f.check_events()

run_game()