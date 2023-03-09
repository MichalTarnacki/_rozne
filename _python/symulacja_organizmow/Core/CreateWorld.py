from enum import Enum, unique


@unique
class CreateWorldMode(Enum):
    Load = 1
    New = 2
