from visual import *
from visual.graph import *

funct1 = gcurve(color=color.cyan)
funct2 = gdots(delta=0.05, color=color.blue)
for x in arange(0., 8.1, 0.1):
    funct1.plot(pos=(x,5.*cos(2.*x)*exp(-0.2*x))) # curve
    funct2.plot(pos=(x,4.*cos(0.5*x)*exp(-0.1*x))) # dots
    
                
