class OrganismsConfiguration:

    def __init__(self, human_number: int = 0,
                 wolf_number: int = 0,
                 sheep_number: int = 0,
                 fox_number: int = 0,
                 turtle_number: int = 0,
                 antilope_number: int = 0,
                 cyber_sheep_number: int = 0,
                 grass_number: int = 0,
                 dandelion_number: int = 0,
                 guarana_number: int = 0,
                 wolfberries_number: int = 0,
                 pine_brosht_number: int = 0):
        self.human_number = human_number
        self.wolf_number = wolf_number
        self.sheep_number = sheep_number
        self.fox_number = fox_number
        self.turtle_number = turtle_number
        self.antilope_number = antilope_number
        self.cyber_sheep_number = cyber_sheep_number
        self.grass_number = grass_number
        self.dandelion_number = dandelion_number
        self.guarana_number = guarana_number
        self.wolfberries_number = wolfberries_number
        self.pine_brosht_number = pine_brosht_number

    def get_total_number_of_organisms(self):
        return self.human_number + self.wolf_number + self.sheep_number + \
               self.fox_number + self.turtle_number + self.antilope_number + \
               self.cyber_sheep_number + self.grass_number + self.dandelion_number + \
               self.guarana_number + self.wolfberries_number + self.pine_brosht_number
