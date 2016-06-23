from threading import Thread
from Queue import Queue
from serial import Serial
import Tkinter as tk
import time
import os
import matplotlib
from datetime import datetime
matplotlib.use("TkAgg")
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2TkAgg
from matplotlib.figure import Figure
import numpy as np
import sys

## INITIALIZE SERIAL CONNECTION
serial = Serial('/dev/ttyUSB0', baudrate=57600, timeout=0.7)

logFile = open("Output.txt", "w")
timeA = datetime.now();
timeB = datetime.now();
## SERIAL WORKER SETUP FOR ASYNC WRITING
serialQueue = Queue()
def serialWorkerFunction(queue):
    while True:
        # get job or wait for new job in queue 
        command = queue.get()
        timeA = datetime.now();
        addLineToConsole("send: '%s'\n" % command)
        serial.write(command)
        readSerial(command)
        queue.task_done()

## WORKER FUNCTION FOR PULLING STATS
def pollForStats():
    while(True):
        serialQueue.put('t')
        time.sleep(0.2)


## READ FROM SERIAL
def readSerial(command):
    try:
        while(serial.inWaiting()):
            serialLine = serial.readline()
            addLineToConsole(serialLine);
            serialCommander(command, serialLine)
    except Exception,e: 
        print str(e)
        pass

## SERIAL COMMANDER
def serialCommander(command, line):
    if len(line) > 0 and command == line[0]:
        # command is verified
        if len(line) > 1:
            addLineToConsole(line[1:] + "\n")
        else:
            addLineToConsole("command verified\n")


        # Update view state
        if command == 't':
            newData = [float(x) for x in line[1:].split(',')]
            print newData
            if(len(newData) > 0):
                logFile.write(line[1:])
                data = app.line1.get_ydata()
                app.refreshPlot(np.append(data[-20:], newData[0]))
        return 0
    else:
        print "comm not verified - %s" % line
        return 1

    print command;


## ADD LINE TO CONSOLE
def addLineToConsole(text):
    str_ = app.consoleText.get() + text
    app.consoleText.set(str_[-1000:])


## TKINTER GUI
class Window():
    def __init__(self, master):
        self.frame = tk.Frame(master)

        self.consoleText = tk.StringVar()
        self.consoleLabel = tk.Label(master, width=100, height=50, anchor=tk.S+tk.W, justify=tk.LEFT, bg='white', textvariable=self.consoleText).grid(row=0, column = 0, padx=10, pady=10)

        self.figure = Figure(figsize=(6, 6), dpi=80)
        self.ax = self.figure.add_subplot(111)
        self.line1, = self.ax.plot([],"r-", label='line1')
        self.ax.legend()
        #self.ax.set_xlabel( 'Time (s)' )
        self.ax.set_title( 'IR sensor data' )
        self.canvas = FigureCanvasTkAgg(self.figure, master=root)
        self.canvas.show()
        self.canvas.get_tk_widget().grid(row=0, column=1)

    def refreshPlot(self,y):
        x = range(len(y))
        self.line1.set_data(x,y)
        ax = self.canvas.figure.axes[0]
        ax.set_xlim(min(x), max(x))
        ax.set_ylim(min(y), max(y))    
        self.canvas.draw()


## START APPLICATION
root = tk.Tk()
app = Window(root)
root.title('Unicorn Walker Robot Control interface')
#root.geometry('400x200+100+100')


## KEYBINDINGS
def keyDown(event):
    serialQueue.put(event.char)

def keyRelease(event):
    serialQueue.put(event.char.upper())

os.system('xset r off') #stop X repeat multiple key presses
root.bind("<KeyPress>", keyDown)
root.bind("<KeyRelease>", keyRelease)


## Start Worker threads
serialWorker = Thread(target=serialWorkerFunction, args=(serialQueue,))
serialWorker.setDaemon(True)
serialWorker.start()

statWorker = Thread(target=pollForStats)
statWorker.start()


# Hand main thread over to the Tkinter event loop
root.mainloop()
os.system('xset r on')

# Close open handles on exit
logFile.close()
serial.close()
serialWorker.stop()
statWorker.stop()