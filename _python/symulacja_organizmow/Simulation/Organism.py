from __future__ import annotations

import copy
from abc import abstractmethod
from datetime import datetime

from Core.Location import Location
from Core.Mode import ToStringMode
from Simulation.HexWorld import HexWorld


class Organism:
    """Base class of all simulation organisms"""

    def __init__(self, world):
        self._strength = 0
        self._initiative = 0
        self._location = Location()
        self._location_before = Location()
        self.__date_of_birth = datetime.now()
        self.world = world
        self.__is_alive = True
        self.__capable_of_reproduction = False

    @abstractmethod
    def _set_initiative(self):
        pass

    @abstractmethod
    def _set_strength(self):
        pass

    @abstractmethod
    def action(self):
        pass

    def collision(self, other: Organism):
        self.world.event_listener.add_string("Organizm: " + other.draw() + " atakuje  \n organizm: " +
                                             self.draw() + " na polu:" + str(self.get_location()))
        if self.get_strength() > other.get_strength():
            self.world.kill_organism(other)
            self.world.event_listener.add_string("  Zwycieza: " + self.draw())

        else:
            pass
            self.world.kill_organism(self)
            self.world.event_listener.add_string("  Zwycieza: " + other.draw())

    @abstractmethod
    def draw(self):
        pass

    def get_initiative(self):
        return self._initiative

    def get_strength(self):
        return self._strength

    def get_lifetime(self):
        return datetime.now() - self.__date_of_birth  # posible error

    def set_location(self, new: Location):
        self._location = copy.copy(new)

    def set_previous_location(self, new: Location):
        self._location_before = copy.copy(new)

    def get_location(self):
        return self._location

    def get_previous_location(self):
        return self._location_before

    def set_reproduce_ability(self, condition: bool):
        self.__capable_of_reproduction = condition

    def check_if_there_is_safe_place_to_move(self, move_range: int = 1):
        for i in range(-1, 2, 1):
            for j in range(-1, 2, 1):
                new_location = Location(self.get_location().get_x() + j * move_range,
                                        self.get_location().get_y() + i * move_range)
                empty_field = True
                if not isinstance(self.world, HexWorld):
                    if new_location.get_y() < 0 or new_location.get_x() < 0 or new_location.get_x() >= self.world.get_board().get_n() \
                            or new_location.get_y() >= self.world.get_board().get_m():
                        empty_field = False
                    else:
                        for organism in self.world.get_organisms():
                            if organism.get_location().__eq__(new_location):
                                empty_field = False
                    if empty_field:
                        return True
                else:
                    if j == 1 and i == 0:
                        new_location.set(new_location.get_x() - 2 * move_range, new_location.get_y() + 2 * move_range)
                    elif j == -1 and i == 0:
                        new_location.set(new_location.get_x() + 2 * move_range, new_location.get_y() - 2 * move_range)
                    if new_location.get_y() < 0 or new_location.get_x() < 0 or new_location.get_x() \
                            >= self.world.get_board().get_n() or new_location.get_y() >= self.world.get_board().get_m() \
                            or (j == 1 and i == 1) or (j == -1 and i == -1):
                        empty_field = False
                    else:
                        for organism in self.world.get_organisms():
                            if organism.get_location().__eq__(new_location):
                                empty_field = False
                    if empty_field:
                        return True
        return False

    def check_if_it_is_alive(self):
        return self.__is_alive

    def kill(self):
        self.__is_alive = False

    @abstractmethod
    def birth(self):
        pass

    def increase_strength(self, how_much: int):
        self._strength += how_much

    def check_if_it_can_reproduce(self):
        return self.__capable_of_reproduction

    @abstractmethod
    def can_be_partner(self, other: Organism):
        pass

    def load_properties(self, strength, initiative, location: Location, location_before: Location,
                        date_of_birth: datetime, is_alive: bool, capable_of_reproduction: bool, opt_par1: bool = None,
                        opt_par2: int = None):
        self._strength = strength
        self._initiative = initiative
        self._location = Location(location.get_x(), location.get_y())
        self._location_before = Location(location_before.get_x(), location_before.y)
        self.__date_of_birth = date_of_birth
        self.__is_alive = is_alive
        self.__capable_of_reproduction = capable_of_reproduction

    def __str__(self, mode: ToStringMode = ToStringMode.Pretty):
        if mode == ToStringMode.Pretty:
            return "[" + self.draw() + "] " + "Strength: " + str(self._strength) + " Initiative: " + str(
                self._initiative) \
                   + " Polozenie: " + str(self._location) + " Czy zywy: " + str(self.__is_alive) \
                   + " Zdolny do rozrodu: " + str(self.__capable_of_reproduction)
        else:
            return self.draw() + " " + str(self.__date_of_birth.timestamp()) + " " + str(self._strength) + " " + \
                   str(self._initiative) + " " + self._location.__str__(ToStringMode.Simple) + " " + \
                   self._location_before.__str__(ToStringMode.Simple) + " " + str(self.__is_alive) + \
                   " " + str(self.__capable_of_reproduction)

    def __gt__(self, other: Organism):
        if self._initiative > other._initiative:
            return True
        elif self._initiative == self._initiative:
            if self.get_lifetime() > other.get_lifetime():
                return True
        return False

    @abstractmethod
    def get_color(self):
        pass
