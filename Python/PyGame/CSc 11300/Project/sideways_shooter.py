import pygame
from pygame.sprite import Group
import functions as f
import settings
from settings import Settings
import sideways_shooter_obj
from sideways_shooter_obj import Shooter
import bullet_obj
from bullet_obj import Bullet

def run_game():
    pygame.init()
    settings = Settings()
    screen = pygame.display.set_mode((settings.screen_width, settings.screen_height))
    pygame.display.set_caption("Sideways Shooter")
    shooter = Shooter(settings, screen)
    bullets = Group()

    while True:
        f.check_events_bullet(settings, screen, shooter, bullets) 
        shooter.update()
        f.update_bullets(bullets, settings)
        f.update_screen_sprite(settings, screen, shooter, bullets)

run_game()