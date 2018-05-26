from visual import *
from visual.graph import * # import graphing features

graph1 = gdisplay() #Create Graph Display
graph2 = gdisplay(y = 100) #Create 2nd Graph Display
funct1 = gcurve(gdisplay = graph1,color=color.cyan) #Create a function
funct2 = gdots(gdisplay = graph2, color=color.blue)
for x in arange(0., 8.1, 0.1):
    funct1.plot(pos=(x,5.*cos(2.*x)*exp(-0.2*x))) # curve
    funct2.plot(pos=(x,4.*cos(0.5*x)*exp(-0.1*x))) # dots
    
                
