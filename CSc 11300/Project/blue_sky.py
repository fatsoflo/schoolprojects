import pygame
import functions as f
import settings
from settings import Settings

def run_game():
    pygame.init()
    settings = Settings()
    blue_bg = (130, 213, 255)
    settings.set_bg_color(blue_bg)
    screen = pygame.display.set_mode((settings.screen_width, settings.screen_height))
    pygame.display.set_caption("Blue Sky")

    while True: 
        f.update_screen_no_obj(settings, screen)
        f.check_events()

run_game() 