from lcd_widget_ui import Ui_distancewindow             #importing class from lcdwindow.py
import os, sys
from serial import Serial 
from PyQt5 import QtCore, QtGui, QtWidgets 
from PyQt5.QtCore import QTimer

class DistanceLED:
    def __init__(self,ui):
        self.ui = ui
        self.alert
        print("Initialising")
        self.arduinoSerialData = Serial('/dev/ttyACM0',9600) 
        self.timer = QTimer()
        self.timer.timeout.connect(self.updateValue)
        self.timer.start(1)

    def print_distance(self,l):
        if len(l)>2:   #checking if the list have more than 2 elements or not
            dis=l[1]      #assigning list element at pos 1 to dis
            os.system('clear')      #clears terminal
            self.ui.lcdNumber.display(dis)
            self.alert(dis)   #invoking alert()
    
    def alert(self,x):
        if str.isdigit(x):
            final_distance=int(x)
            if final_distance>50:
               
                self.ui.label2.setText("<font color='red'>Alert!Too Far!</font>")
            elif final_distance<10:

                self.ui.label2.setText("<font color='red'>Alert!Too Close!</font>")
            else:

                self.ui.label2.setText(f"<font color='green'>{final_distance} is a valid distance.</font>")    

    def updateValue(self):
        myData = self.arduinoSerialData.readline()     #read the serial data from arduino and store it in myData variable
        string=str(myData)           #converting bytes into str               
        l=string.split(" ")   #slicing the string and entering into a list
        self.print_distance(l)
        
        
    
          
def window():
    app = QtWidgets.QApplication(sys.argv)
    distancewindow = QtWidgets.QMainWindow()
    ui = Ui_distancewindow()
    ui.setupUi(distancewindow) 
    disLed=DistanceLED(ui)
    distancewindow.show()
    sys.exit(app.exec_())


if __name__=="__main__":
    window()
