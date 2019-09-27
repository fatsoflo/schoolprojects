import pygame
from pygame.sprite import Group
import functions as f
import settings
from settings import Settings
import ball_obj
from ball_obj import Ball
import dog_obj
from dog_obj import Dog
import stats
from stats import Stats
import game_over_obj
from game_over_obj import Game_Over

def run_game():
    pygame.init()
    settings = Settings()
    screen = pygame.display.set_mode((settings.screen_width, settings.screen_height))
    pygame.display.set_caption("Game Over")
    ball = Ball(settings, screen)
    balls = Group()
    dog = Dog(settings, screen)
    balls.add(ball)
    stats = Stats(settings)
    text = Game_Over(settings, screen)

    while True: 
        f.check_events_catch(settings, screen, dog)
        if stats.game_active:
            dog.update()
            f.update_balls_stats(settings, stats, screen, dog, balls)
            f.update_screen_sprite(settings, screen, dog, balls)
        else:
            #missed 3 balls, display game over
            text.blitme()
            pygame.display.flip()

run_game()