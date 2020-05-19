import pygame
import functions as f
import settings
from settings import Settings
import game_character_obj
from game_character_obj import Character

def run_game():
    pygame.init()
    settings = Settings()
    screen = pygame.display.set_mode((settings.screen_width, settings.screen_height))
    pygame.display.set_caption("Game Character")
    game_char = Character(screen)

    while True:
        f.check_events()
        f.update_screen(settings, screen, game_char)

run_game()

