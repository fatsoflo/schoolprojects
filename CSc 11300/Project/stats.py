class Stats():
    def __init__(self, settings):
        self.settings = settings
        self.reset_stats()
        self.game_active = True

    def reset_stats(self):
        self.lives_left = self.settings.lives_limit