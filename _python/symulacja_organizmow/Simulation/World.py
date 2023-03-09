import copy
import datetime
import random
import time
from typing import List

from Core.BirthMode import BirthMode
from Core.Board import Board
from Core.CreateWorld import CreateWorldMode
from Core.Dimension import Dimension
from Core.HumanDirection import HumanDirection
from Core.Listener import Listener
from Core.Location import Location
from Core.Mode import ToStringMode
from Core.VariablesToLoad import VariablesToLoad
from Simulation.Organism import Organism
from Core.OrganismsConfiguration import OrganismsConfiguration
from Simulation.Organisms.Animals.Antilope import Antilope
from Simulation.Organisms.Animals.CyberSheep import CyberSheep
from Simulation.Organisms.Animals.Fox import Fox
from Simulation.Organisms.Animals.Sheep import Sheep
from Simulation.Organisms.Animals.Turtle import Turtle
from Simulation.Organisms.Animals.Wolf import Wolf
from Simulation.Organisms.Human import Human
from Simulation.Organisms.Plants.Dandelion import Dandelion
from Simulation.Organisms.Plants.Grass import Grass
from Simulation.Organisms.Plants.Guarana import Guarana
from Simulation.Organisms.Plants.PineBrosht import PineBrosht
from Simulation.Organisms.Plants.WolfBerries import WolfBerries


class World:
    def __init__(self, dimension: Dimension = None, organism_configuration: OrganismsConfiguration = None,
                 mode: CreateWorldMode = CreateWorldMode.New):
        self._board = None
        self._number_of_organisms = 0
        self._organisms: List[Organism] = list()
        self._new_organisms = []
        self.event_listener = Listener()
        self._round_number = 0
        self.__save_place = "file.txt"
        self._human_direction = HumanDirection.DoNotMove

        if dimension is not None:
            self._board = Board(dimension)
            if organism_configuration is not None:
                self._load_organisms(organism_configuration)
                self._draw_positions()
        if mode == CreateWorldMode.Load:
            self.load_game_state()

    def load(self):
        pass

    def initialize_window(self):
        pass

    def make_turn(self):
        self._sort_organisms()
        self._restore_reproduce_ability()
        # self.window.update()
        self.event_listener.clear()
        for first_organism in self._organisms:
            if first_organism.check_if_it_is_alive():
                first_organism.action()
                for second_organism in self._organisms:
                    if second_organism.check_if_it_is_alive() and first_organism.get_location().__eq__(
                            second_organism.get_location()) and first_organism is not second_organism:
                        second_organism.collision(first_organism)
                first_organism.set_previous_location(first_organism.get_location())
        self._remove_dead_bodies()
        self._update_round_number()
        self.__draw_world()

    def simulate(self):
        # window.set_size(800, 600)
        # window.set_visible()
        self.load_game_state()
        self.set_human_move_direction(HumanDirection.North)
        # while not self.check_if_only_one_organism_type_left():
        # window.update()
        # place for control
        self.event_listener.clear()
        self.make_turn()
        # window.update()
        self.__draw_world()

    def __draw_world(self):
        found = False
        location = Location()
        print("+-----------------------------------------+", end="\n")
        print("|Wirtualny Swiat - Michal Tarnacki s188627|", end="\n")
        print("+-----------------------------------------+", end="\n")
        for y in range(0, self._board.get_m() + 2, 1):
            for x in range(0, self._board.get_n() + 2, 1):
                if (x == 0 and y == 0) or (x == 0 and y == self._board.get_m() + 1) or (
                        x == self._board.get_n() + 1 and y == 0) or (
                        x == self._board.get_n() + 1 and y == self._board.get_m() + 1):
                    print('+', end="")
                elif x == 0 or x == self._board.get_n() + 1:
                    print('|', end="")
                elif y == 0 or y == self._board.get_m() + 1:
                    print('-', end="")
                else:
                    location.set(x - 1, y - 1)
                    found = False
                    for organism in self._organisms:
                        if organism.check_if_it_is_alive() and organism.get_location().__eq__(location):
                            print(organism.draw(), end="")
                            found = True
                    if not found:
                        print(' ', end="")
            print("", end="\n")
        print("Aktualna liczba organizmow:" + str(self._number_of_organisms), end="\n")

    def _sort_organisms(self):
        self._organisms.sort()

    def _load_organisms(self, conf: OrganismsConfiguration):
        for i in range (0, conf.human_number, 1):
            self._organisms.append(Human(self))
        for i in range(0, conf.antilope_number, 1):
            self._organisms.append(Antilope(self))
        for i in range(0, conf.wolf_number, 1):
            self._organisms.append(Wolf(self))
        for i in range(0, conf.sheep_number, 1):
            self._organisms.append(Sheep(self))
        for i in range(0, conf.fox_number, 1):
            self._organisms.append(Fox(self))
        for i in range(0, conf.turtle_number, 1):
            self._organisms.append(Turtle(self))
        for i in range(0, conf.cyber_sheep_number, 1):
            self._organisms.append(CyberSheep(self))
        for i in range(0, conf.grass_number, 1):
            self._organisms.append(Grass(self))
        for i in range(0, conf.dandelion_number, 1):
            self._organisms.append(Dandelion(self))
        for i in range(0, conf.guarana_number, 1):
            self._organisms.append(Guarana(self))
        for i in range(0, conf.wolfberries_number, 1):
            self._organisms.append(WolfBerries(self))
        for i in range(0, conf.pine_brosht_number, 1):
            self._organisms.append(PineBrosht(self))
        self._number_of_organisms = conf.get_total_number_of_organisms()

    def _draw_positions(self):
        location = Location()
        for first_organism in self._organisms:
            while True:
                location.set(random.randint(0, self._board.get_n()-1), random.randint(0, self._board.get_m()-1))
                unique = True
                for second_organism in self._organisms:
                    if location.__eq__(second_organism.get_location()):
                        unique = False
                if unique:
                    break
            first_organism.set_location(copy.copy(location))
            first_organism.set_previous_location(copy.copy(location))

    def get_board(self):
        return self._board

    def kill_organism(self, organism: Organism):
        organism.kill()
        self._number_of_organisms -= 1

    def birth_organism(self, parrent: Organism, location: Location, birth_mode: BirthMode):
        new_organism = parrent.birth()
        new_organism.set_location(location)
        new_organism.set_previous_location(location)
        new_organism.set_reproduce_ability(False)
        self._organisms.append(new_organism)
        self._number_of_organisms += 1
        # if birth_mode == BirthMode.Add:
        #     window.update()

    def check_if_only_one_organism_type_left(self):
        if self._number_of_organisms is not self._board.get_field_number():
            return False
        organism = self._organisms.__getitem__(0)
        for second_organism in self._organisms:
            if not second_organism.can_be_partner(organism):
                return False
        return True

    def save_game_state(self):
        file = open(self.__save_place, "w")
        file.write(self._board.__str__(ToStringMode.Simple) + "\n")
        file.write(str(self._round_number) + " " + str(self._number_of_organisms) + "\n")
        for organism in self._organisms:
            file.write(organism.__str__(ToStringMode.Simple) + "\n")
        file.close()

    def load_game_state(self):
        file = open(self.__save_place, "r")
        if not file.readable():
            return
        self._destroy_world()

        variables_to_load = VariablesToLoad(self)
        x = file.readline().split()
        variables_to_load.x = int(x[0])
        variables_to_load.y = int(x[1])
        x = file.readline().split()
        variables_to_load.round_number = x[0]
        variables_to_load.number_of_organisms = int(x[1])
        self._board.set(Board(Dimension(int(variables_to_load.x), int(variables_to_load.y))))
        self._round_number = int(variables_to_load.round_number)
        self._number_of_organisms = int(variables_to_load.number_of_organisms)
        for i in range(0, self._number_of_organisms, 1):
            x = file.readline().split()
            for organism in variables_to_load.temp_organisms:
                if x[0] == organism.draw():
                    self._organisms.append(organism.birth())
                    variables_to_load.date_of_birth = datetime.datetime.fromtimestamp(float(x[1]))
                    variables_to_load.strength = int(x[2])
                    variables_to_load.initiative = int(x[3])
                    variables_to_load.x = int(x[4])
                    variables_to_load.y = int(x[5])
                    variables_to_load.x2 = int(x[6])
                    variables_to_load.y2 = int(x[7])
                    variables_to_load.is_alive = True if x[8] == "True" else False
                    variables_to_load.capable_of_reproduction = True if x[9] == "True" else False
                    if isinstance(organism, Human):
                        variables_to_load.opt_par1 = bool(x[10])
                        variables_to_load.opt_par2 = int(x[11])
                    variables_to_load.location = Location(int(variables_to_load.x), int(variables_to_load.y))
                    variables_to_load.previous_location = Location(int(variables_to_load.x), int(variables_to_load.y))
                    self._organisms.__getitem__(-1).load_properties(variables_to_load.strength, variables_to_load.initiative, variables_to_load.location,
                                             variables_to_load.previous_location, variables_to_load.date_of_birth, variables_to_load.is_alive,
                                             variables_to_load.capable_of_reproduction, variables_to_load.opt_par1,variables_to_load.opt_par2)
                    break


    def _destroy_world(self):
        for organism in self._organisms:
            organism.kill()
            self._number_of_organisms -= 1
        self._remove_dead_bodies()
        self.event_listener.clear()

    def set_human_move_direction(self, direction: HumanDirection):
        for organism in self._organisms:
            if isinstance(organism, Human):
                organism.set_move_direction(direction)

    def _human_direction_to_string(self):
        if self._human_direction == HumanDirection.North:
            return "Gora"
        elif self._human_direction == HumanDirection.South:
            return "Dol"
        elif self._human_direction == HumanDirection.West:
            return "Lewo"
        elif self._human_direction == HumanDirection.East:
            return "Prawo"
        elif self._human_direction == HumanDirection.HexUp:
            return "GoraHex"
        elif self._human_direction == HumanDirection.HexDown:
            return "DolHex"
        else:
            return "Brak"

    def turn_on_special_ability(self):
        for organism in self._organisms:
            if isinstance(organism, Human):
                organism.special_ability()

    def human_exists(self):
        for organism in self._organisms:
            if isinstance(organism, Human):
                return True
        return False

    def update_round_number(self):
        self._round_number += 1

    def _remove_dead_bodies(self):
        organism = None
        self._new_organisms.clear()
        for organism in self._organisms:
            if organism.check_if_it_is_alive():
                self._new_organisms.append(organism)
        self._organisms.clear()
        self._organisms = copy.copy(self._new_organisms)

    def get_organisms(self):
        return self._organisms

    def _restore_reproduce_ability(self):
        for organism in self._organisms:
            if not organism.check_if_it_can_reproduce():
                organism.set_reproduce_ability(True)

    def _update_round_number(self):
        self._round_number += 1

    def get_round_number(self):
        return self._round_number
