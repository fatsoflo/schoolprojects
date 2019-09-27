import pygame
import functions as f
import settings
from settings import Settings
import rocket_obj
from rocket_obj import Rocket

def run_game():
    pygame.init()
    settings = Settings()
    screen = pygame.display.set_mode((settings.screen_width, settings.screen_height))
    pygame.display.set_caption("Rocket")
    rocket = Rocket(settings, screen)

    while True:
        f.check_events_rocket(rocket) 
        rocket.update()
        f.update_screen(settings, screen, rocket)

run_game()