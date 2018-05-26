import serial #Import Serial Library
from visual import * #Import all the vPython library
from visual.graph import *

arduinoSerialData = serial.Serial('com3', 9600) #Create an object for the Serial port. Adjust 'com11' to whatever port your arduino is sending to.
measuringRod = cylinder(axis=(0,1,0),title="My Meter", radius= .5, length=6, color=color.yellow, pos=(-3,0,0))
lengthLabel=label(pos=(0,5,0), text='Target Distance is: ', box=false,height=30)
target=box(axis=(0,1,0),pos=(-3,0,0), length=.2, width=3, height=3, color=color.green)
graph1=gdisplay()
funct1=gcurve(gdisplay=graph1,color=color.cyan)
x=1
y=0

while (1==1): #Create a loop that continues to read and display the data
    rate(20)#Tell vpython to run this loop 20 times a second
    if (arduinoSerialData.inWaiting()>0): #Check to see if a data point is available
        myData = arduinoSerialData.readline() #Read the distance measure as a string
        print myData #Print the measurement to confirm things are working
        distance = float(myData) #convert reading to a floating point number
        if(distance<=0):
            distance=0.1
        measuringRod.length=distance #Change the length of your measuring rod
        target.pos=(-3, distance, 0)
        myLabel='Target Distance is: ' + myData
        lengthLabel.text=myLabel
        funct1.plot(pos=(x,y))
        x=x+1
        y=distance
