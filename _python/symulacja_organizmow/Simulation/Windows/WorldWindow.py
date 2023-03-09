import copy
from tkinter import Tk, Button, Canvas, PhotoImage, Label

from Core.Dimension import Dimension
from Core.HumanDirection import HumanDirection
from Core.Location import Location
from Core.OrganismsConfiguration import OrganismsConfiguration
from Simulation.Windows.AddOrganismWindow import AddOrganismWindow
from Simulation.World import World


class SpecialBut(Button):
    def __init__(self, window, location: Location):
        super().__init__(window, text="")
        self.location = location


class WorldWindow(Tk):

    def __init__(self):
        super().__init__()
        self.title("Symulacja organizmow - s188627")
        self.field_height = None
        self.field_width = None
        self.dim = Dimension(10, 10)
        self.org_conf = OrganismsConfiguration(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
        self.world = World(self.dim, self.org_conf)
        self.height = 600
        self.width = 1200
        self.margin = 5
        self.bar = 25
        self.right_margin = 600
        self.update_geometry()
        self.geometry("1100x600")
        self.bind('<w>', lambda event: self.human_action(self, "w"))
        self.bind('<a>', lambda event: self.human_action(self, "a"))
        self.bind('<s>', lambda event: self.human_action(self, "s"))
        self.bind('<d>', lambda event: self.human_action(self, "d"))
        self.bind('<r>', lambda event: self.human_action(self, "r"))
        self.click_button = Button(self, text="Nastepna runda!", width=8, height=10)
        self.click_button.place(x=self.width-self.right_margin+self.margin, y=30)
        self.save_button = Button(self, text="Zapisz", width=8, height=10)
        self.save_button.place(x=self.width-self.right_margin+self.margin, y=180)
        self.load_button = Button(self, text="Wczytaj", width=8, height=10)
        self.load_button.place(x=self.width - self.right_margin+self.margin, y=330)
        self.canvas = Canvas(self, width=self.width-self.right_margin, height=self.height)
        self.canvas.place(x=0, y=0)
        self.iss = 0
        self.label = Label(self, text=str(self.iss), width=8, height=10)
        self.label.place(x=self.width-10*self.margin, y=30)

        self.click_button.config(command=lambda: self.click_action(self.click_button))
        self.save_button.config(command=lambda: self.save_action(self.save_button))
        self.load_button.config(command=lambda: self.load_action(self.load_button))
        self.update()
        self.mainloop()

    def update_geometry(self):
        self.field_height = (self.height - 2 * self.margin) / self.world.get_board().get_m()
        self.field_width = (self.width - 2 * self.margin - self.right_margin) / self.world.get_board().get_n()

    def click_action(self, button):
        if not self.world.check_if_only_one_organism_type_left():
            self.world.make_turn()
        self.update()

    def save_action(self, button):
        self.world.save_game_state()

    def load_action(self, button):
        self.world.load_game_state()
        self.update_geometry()
        self.update()

    def add_organism_action(self, button, x, y):
        window = AddOrganismWindow(self, Location(x,y))
        window.grab_set()
        self.update()

    def human_action(self, canvas, key):
        if key == "w" or key == "a" or key == "s" or key == "d":
            if key == "w":
                self.world.set_human_move_direction(HumanDirection.North)
            elif key =="a":
                self.world.set_human_move_direction(HumanDirection.West)
            elif key =="s":
                self.world.set_human_move_direction(HumanDirection.South)
            elif key =="d":
                self.world.set_human_move_direction(HumanDirection.East)
            self.click_action(0)
        if key == "r":
            self.world.turn_on_special_ability()
            self.update()

    def update(self):
        self.canvas = Canvas(self, width=self.width-self.right_margin, height=self.height)
        self.canvas.place(x=0, y=0)
        self.iss += 1
        self.label.destroy()
        self.label = Label(self, text=str(self.world.event_listener.__str__()), width=30, height=30)
        self.label.place(x=self.width -  self.right_margin + 130, y=30)
        self.canvas.create_line(self.margin, self.margin, self.margin, self.height - self.margin, fill="black", width=5)
        self.canvas.create_line(self.margin, self.margin, self.width-self.right_margin-self.margin, self.margin, fill="black", width=5)
        self.canvas.create_line(self.margin, self.height - self.margin, self.width - self.right_margin - self.margin, self.height - self.margin, fill="black", width=5)
        self.canvas.create_line(self.width - self.margin - self.right_margin, self.margin, self.width - self.margin - self.right_margin, self.height - self.margin, fill="black", width=5)
        for y in range(self.world.get_board().get_m()):
            for x in range(self.world.get_board().get_n()):
                found = False
                for organism in self.world.get_organisms():
                    if organism.check_if_it_is_alive() and organism.get_location().__eq__(Location(x,y)):
                        self.canvas.create_rectangle((self.margin+x*self.field_width,self.margin+y*self.field_height,
                            self.margin+(x+1)*self.field_width, self.margin+(y+1)*self.field_height), fill = organism.get_color())
                        found = True
                if not found:
                    organism_button = SpecialBut(self.canvas, Location(x, y))
                    organism_button.config(command=copy.copy(lambda x=x, y=y: self.add_organism_action(organism_button, x, y)))
                    organism_button.place(x=self.margin + x * self.field_width, y=self.margin + y * self.field_height, width=self.field_width, height=self.field_height)

        # self.canvas.create_rectangle((0, 0, 10, 10))

    def options(self):
        pass
