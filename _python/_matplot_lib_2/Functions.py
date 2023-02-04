import numpy as np
import Data as data
def stala_czasowa(p):
    return -1/ round((p(1) - p(0)) / 1, 4)
   # return (np.log(data.U0) - 1 - round(p(0), 2)) / round((p(1) - p(0)) / 1, 4)
def prosta(p):
    str = "y= " + (round((p(1) - p(0)) / 1, 4)).__str__() + "x + " + (round(p(0), 2)).__str__()
    return str