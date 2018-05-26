from visual import *
from visual.graph import * # import graphing features

graph1 = gdisplay() #Create Graph Display
funct1 = gcurve(gdisplay = graph1,color=color.cyan) #Create a function
x = 1
y = 0
while (x<100):
    rate(1)
    funct1.plot(pos=(x,y))
    x=x+1
    y=x*x                
