import pygame
from pygame.sprite import Group
import functions as f
import settings
from settings import Settings
import ball_obj
from ball_obj import Ball
import dog_obj
from dog_obj import Dog

def run_game():
    pygame.init()
    settings = Settings()
    screen = pygame.display.set_mode((settings.screen_width, settings.screen_height))
    pygame.display.set_caption("Catch")
    ball = Ball(settings, screen)
    balls = Group()
    dog = Dog(settings, screen)
    balls.add(ball)

    while True: 
        f.check_events_catch(settings, screen, dog)
        dog.update()
        f.update_balls(settings, screen, dog, balls)
        f.update_screen_sprite(settings, screen, dog, balls)

run_game()