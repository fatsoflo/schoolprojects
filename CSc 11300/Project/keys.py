import pygame
import functions as f
import settings
from settings import Settings

def run_game():
    pygame.init()
    settings = Settings()
    screen = pygame.display.set_mode((settings.screen_width, settings.screen_height))
    pygame.display.set_caption("Keys")

    while True:
        f.check_events_keys()     
        f.update_screen_no_obj(settings, screen)   

run_game()

