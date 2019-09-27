import sys
import pygame
from pygame.sprite import Sprite
from bullet_obj import Bullet
from star_obj import Star
from random import randint
from raindrop_obj import Raindrop
from ball_obj import Ball

def update_screen_no_obj(settings, screen):
    screen.fill(settings.bg_color)
    pygame.display.flip()

def update_screen(settings, screen, obj):
    screen.fill(settings.bg_color)
    obj.blitme()
    pygame.display.flip()

def update_screen_sprite(settings, screen, obj, sprites):
    screen.fill(settings.bg_color)
    obj.blitme()
    for sprite in sprites.sprites():
        sprite.draw()
    pygame.display.flip()

def update_screen_grid(settings, screen, obj):
    screen.fill(settings.bg_color)
    obj.draw(screen)
    pygame.display.flip()

#general
def check_events():
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()

#key
def check_events_keys():
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()   
        elif event.type == pygame.KEYDOWN:
            print(event.key)        

#rocket
def check_events_rocket(ship):
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()
        elif event.type == pygame.KEYDOWN:
            check_keydown_events(event, ship)
        elif event.type == pygame.KEYUP:
            check_keyup_events(event, ship)

def check_keydown_events(event, ship):
    if event.key == pygame.K_RIGHT:
        ship.moving_right = True
    elif event.key == pygame.K_LEFT:
        ship.moving_left = True
    elif event.key == pygame.K_UP:
        ship.moving_up = True
    elif event.key == pygame.K_DOWN:
        ship.moving_down = True

def check_keyup_events(event, ship):
    if event.key == pygame.K_RIGHT:
        ship.moving_right = False
    elif event.key == pygame.K_LEFT:
        ship.moving_left = False
    elif event.key == pygame.K_UP:
        ship.moving_up = False
    elif event.key == pygame.K_DOWN:
        ship.moving_down = False

#bullet 
def check_events_bullet(settings, screen, ship, bullets):
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()
        elif event.type == pygame.KEYDOWN:
            check_keydown_events_bullet(event, settings, screen, ship, bullets)
        elif event.type == pygame.KEYUP:
            check_keyup_events_bullet(event, ship)

def check_keydown_events_bullet(event, settings, screen, ship, bullets):
    #ship
    if event.key == pygame.K_UP:
        ship.moving_up = True
    elif event.key == pygame.K_DOWN:
        ship.moving_down = True
    #bullets
    elif event.key == pygame.K_SPACE:
        new_bullet = Bullet(settings, screen, ship)
        bullets.add(new_bullet)

def check_keyup_events_bullet(event, ship):
    if event.key == pygame.K_UP:
        ship.moving_up = False
    elif event.key == pygame.K_DOWN:
        ship.moving_down = False

def update_bullets(bullets, settings):
    bullets.update()
    for bullet in bullets.copy():
            if bullet.rect.right >= settings.screen_width:
                bullets.remove(bullet)

#star
def get_number_rows(settings, star_height):
    avail_space_y = settings.screen_height - 2 * star_height
    number_rows = int(avail_space_y / (2 * star_height))
    return number_rows

def get_number_cols(settings, star_width):
    avail_space_x = settings.screen_width - 2 * star_width
    number_cols = int(avail_space_x / (2 * star_width))
    return number_cols

def create_star_grid(settings, screen, stars, star):
    number_rows = get_number_rows(settings, star.rect.height)
    number_cols = get_number_cols(settings, star.rect.width)

    for row_index in range(number_rows):
        for col_index in range(number_cols):
            create_star(settings, screen, stars, col_index, row_index)

def create_star(settings, screen, stars, col_index, row_index):
    star = Star(settings, screen)
    star_width = star.rect.width
    star_height = star.rect.height
    star.x = star_width + 2 * star_width * col_index
    star.rect.x = star.x
    star.rect.y = star_height + 2 * star_height * row_index
    stars.add(star)

def create_better_star_grid(settings, screen, stars, star):
    number_rows = get_number_rows(settings, star.rect.height)
    number_cols = get_number_cols(settings, star.rect.width)
    for row_index in range(number_rows):
        for col_index in range(number_cols):
            random_number = randint(-20,20)
            create_star(settings, screen, stars, col_index + random_number, row_index + random_number)

#raindrop
def create_raindrop_grid(settings, screen, raindrops, raindrop):
    number_rows = get_number_rows(settings, raindrop.rect.height)
    number_cols = get_number_cols(settings, raindrop.rect.width)

    for row_index in range(number_rows):
        for col_index in range(number_cols):
            create_raindrop(settings, screen, raindrops, col_index, row_index)   

def create_raindrop(settings, screen, raindrops, col_index, row_index):
    raindrop = Raindrop(settings, screen)
    raindrop_width = raindrop.rect.width
    raindrop_height = raindrop.rect.height
    raindrop.x = raindrop_width + 2 * raindrop_width * col_index
    raindrop.rect.x = raindrop.x
    raindrop.rect.y = raindrop_height + 2 * raindrop_height * row_index
    raindrops.add(raindrop)

def update_raindrops(settings, raindrops):
    for raindrop in raindrops.sprites():
        if raindrop.check_edges():
            raindrops.remove(raindrop)
    raindrops.update()

#steady rain
def update_steady_rain(settings, screen, raindrops, raindrop):
    number_cols = get_number_cols(settings, raindrop.rect.width)
    raindrop_count = 1
    for raindrop in raindrops.sprites():
        if raindrop.check_edges():
            raindrops.remove(raindrop)
            raindrop_count += 1
        if raindrop_count % number_cols == 0:
            for col_index in range(number_cols):
                create_raindrop(settings, screen, raindrops, col_index, 0)
    raindrops.update()  

#catch
def update_balls(settings, screen, dog, balls):
    for ball in balls:
        ball.update()
        if ball.check_edges():
            balls.remove(ball)
            new_ball = Ball(settings, screen)
            balls.add(new_ball)
    collisions = pygame.sprite.spritecollide(dog, balls, True)
    for collision in collisions:
        new_ball = Ball(settings, screen)
        balls.add(new_ball)
    balls.update()

def check_events_catch(settings, screen, dog):
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()
        elif event.type == pygame.KEYDOWN:
            check_keydown_events_catch(event, settings, screen, dog)
        elif event.type == pygame.KEYUP:
            check_keyup_events_catch(event, dog)

def check_keydown_events_catch(event, settings, screen, dog):
    if event.key == pygame.K_LEFT:
        dog.moving_left = True
    elif event.key == pygame.K_RIGHT:
        dog.moving_right = True

def check_keyup_events_catch(event, dog):
    if event.key == pygame.K_LEFT:
        dog.moving_left = False
    elif event.key == pygame.K_RIGHT:
        dog.moving_right = False

def update_balls_stats(settings, stats, screen, dog, balls):
    for ball in balls:
        ball.update()
        if ball.check_edges():
            balls.remove(ball)
            stats.lives_left -= 1
            if stats.lives_left == 0:
                stats.game_active = False
            new_ball = Ball(settings, screen)
            balls.add(new_ball)
    collisions = pygame.sprite.spritecollide(dog, balls, True)
    for collision in collisions:
        new_ball = Ball(settings, screen)
        balls.add(new_ball)
    balls.update()  