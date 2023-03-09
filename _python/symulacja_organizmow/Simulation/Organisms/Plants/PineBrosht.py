from abc import ABC

from Core.Location import Location
from Simulation.HexWorld import HexWorld
from Simulation.Organism import Organism
from Simulation.Organisms.Animals.CyberSheep import CyberSheep
from Simulation.Organisms.Plant import Plant


class PineBrosht(Plant, ABC):
    def __init__(self, world):
        super().__init__(world)
        self._set_strength()

    def draw(self):
        return 'b'

    def birth(self):
        return PineBrosht(self.world)

    def get_probability(self):
        return 5

    def can_be_partner(self, other: Organism):
        if isinstance(other, PineBrosht):
            return True
        return False

    def action(self):
        self.kill_everything_around()
        super().action()

    def collision(self, other: Organism):
        if not isinstance(other, CyberSheep):
            self.world.kill_organism(other)
        else:
            super().collision(other)

    def kill_everything_around(self):
        already_killed = False
        new_location = Location()
        for i in range(-1, 2, 1):
            for j in range(-1, 2, 1):
                new_location.set(self.get_location().get_x() + j, self.get_location().get_y() + i)
                if not isinstance(self.world, HexWorld):
                    if new_location.get_y() < 0 or new_location.get_x() < 0 or new_location.get_x() >= self.world.get_board().get_n() \
                            or new_location.get_y() >= self.world.get_board().get_m():
                        pass
                    else:
                        for organism in self.world.get_organisms():
                            if organism.check_if_it_is_alive() and organism.get_location().__eq__(new_location) and \
                                    organism is not self and not isinstance(organism, PineBrosht) \
                                    and not isinstance(organism, CyberSheep):
                                if not already_killed:
                                    self.world.event_listener.add_string("Barszcz " + str(self.get_location())
                                                                         + "zabija  wszystkich<br/> wokoło")
                                    already_killed = True
                                self.world.kill_organism(organism)
                                self.world.event_listener.add_string("  Ginie: " + organism.draw() + " " + str(organism.get_location()))
                else:
                    if j == -1 and i == 0:
                        new_location.set(new_location.get_x() + 2, new_location.get_y() - 2)
                    elif j == 1 and i == 0:
                        new_location.set(new_location.get_x() - 2, new_location.get_y() + 2)
                    if new_location.get_y() < 0 or new_location.get_x() < 0 or new_location.get_x() >= self.world.get_board().get_n() \
                            or new_location.get_y() >= self.world.get_board.get_m() or (i == 1 and j == 1) or (i == -1 and j == -1):
                        pass
                    else:
                        if not already_killed:
                            self.world.event_listener.add_string("Barszcz " + self.get_location() + "zabija "
                                                                                                    "wszystkich\n wokoło")
                            already_killed = True
                        self.world.kill_organism(organism)
                        self.world.event_listener.add_string(
                            "  Ginie: " + organism.draw() + " " + organism.get_location())

    def _set_strength(self):
        self._strength = 9

    def get_color(self):
        return "#404746"
