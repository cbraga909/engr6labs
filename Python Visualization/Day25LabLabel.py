import serial #Import Serial Library
from visual import * #Import all the vPython library
arduinoSerialData = serial.Serial('com3', 9600) #Create an object for the Serial port. Adjust 'com11' to whatever port your arduino is sending to.
measuringRod = cylinder(axis=(0,1,0), radius= .5, length=6, color=color.yellow, pos=(-3,0,0))
lengthLabel = label(pos=(0,1,0), text='Target Distance is: ', box=false, height=30)
while (1==1): #Create a loop that continues to read and display the data
    rate(20)#Tell vpython to run this loop 20 times a second
    if (arduinoSerialData.inWaiting()>0): #Check to see if a data point is available on the serial port
        myData = arduinoSerialData.readline() #Read the distance measure as a string
        print myData #Print the measurement to confirm things are working
        distance = float(myData) #convert reading to a floating point number
        if (distance<=0):
            distance=1
        measuringRod.length=distance #Change the length of your measuring rod to your last measurement
        myLabel= 'Target Distance is: ' + myData #Create label by appending string myData to string
        lengthLabel.text = myLabel #display updated myLabel
