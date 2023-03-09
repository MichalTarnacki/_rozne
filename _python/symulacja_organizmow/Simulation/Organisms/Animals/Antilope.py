import random
from abc import ABC

from Simulation.Organism import Organism
from Simulation.Organisms.Animal import Animal


class Antilope(Animal, ABC):

    def __init__(self, world):
        super().__init__(world)
        self._set_initiative()
        self._set_strength()

    def _set_initiative(self):
        self._initiative = 4

    def _set_strength(self):
        self._strength = 4

    def draw(self):
        return 'A'

    def birth(self):
        return Antilope(self.world)

    def can_be_partner(self, other: Organism):
        if isinstance(other, Antilope):
            return True
        return False

    def action(self):
        self.move(2)

    def collision(self, other: Organism):
        x = random.randint(0, 100)
        if x >= 50 and not isinstance(other, Antilope):
            has_moved = self.move_without_collision(2)
            if not has_moved:
                super().collision(other)
            else:
                self.world.event_listener.add_string("Antylopa: " + str(self.get_location()) + " ucieka bez kolizji")
        else:
            super().collision(other)

    def get_color(self):
        return "#005aff"
        pass
