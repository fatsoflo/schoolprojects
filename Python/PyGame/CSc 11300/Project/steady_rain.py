import pygame
from pygame.sprite import Group
import functions as f
import settings
from settings import Settings
import raindrop_obj
from raindrop_obj import Raindrop

def run_game():
    pygame.init()
    settings = Settings()
    screen = pygame.display.set_mode((settings.screen_width, settings.screen_height))
    pygame.display.set_caption("Steady Rain")
    raindrop = Raindrop(settings, screen)
    raindrops = Group()
    f.create_raindrop_grid(settings, screen, raindrops, raindrop)

    while True: 
        f.update_screen_grid(settings, screen, raindrops)    
        f.update_steady_rain(settings, screen, raindrops, raindrop)
        f.check_events()

run_game()