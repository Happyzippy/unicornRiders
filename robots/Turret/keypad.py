from threading import Thread
from Queue import Queue
from serial import Serial
import Tkinter as tk
import tkSimpleDialog
import time
import os
import matplotlib
matplotlib.use("TkAgg")
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2TkAgg
from matplotlib.figure import Figure
import numpy as np
import sys

## INITIALIZE SERIAL CONNECTION
#serial = Serial('/dev/ttyUSB0', baudrate=57600, timeout=0.7)

logFile = open("Output.txt", "w")

## SERIAL WORKER SETUP FOR ASYNC WRITING
serialQueue = Queue()
def serialWorkerFunction(queue):
    while True:
        # get job or wait for new job in queue 
        command = queue.get()
        addLineToConsole("send: '%s'\n" % command)
        #serial.write(command)
        #readSerial(command)
        queue.task_done()

## WORKER FUNCTION FOR PULLING STATS
def pollForStats():
    while(True):
        serialQueue.put('t')
        time.sleep(1)


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
            1

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


## TKINTER GUI
class Window():
    def __init__(self, master):
        self.frame = tk.Frame(master)

        self.player1Text = tk.StringVar()
        self.player1Text.set("0")
        self.player1Label = tk.Label(master, font=("Helvetica", 154), textvariable=self.player1Text).grid(row=0, column = 0, padx=10, pady=10)

        self.highscoreText = tk.StringVar()
        self.highscoreText.set("Highscore")
        self.highscoreLabel = tk.Label(master, font=("Helvetica", 16), textvariable=self.highscoreText).grid(row=1, column = 0, padx=10, pady=10)

        self.resetButton = tk.Button(root, text="reset", command=self.resetGame)
        self.resetButton.grid(row = 2, column = 1)

    def refreshPlot(self,y):
        x = range(len(y))
        self.line1.set_data(x,y)
        ax = self.canvas.figure.axes[0]
        ax.set_xlim(min(x), max(x))
        ax.set_ylim(min(y), max(y))    
        self.canvas.draw()

    def resetGame(self):
        os.system('play --no-show-progress ~/Dropbox/DTU/2.Sem/ModularRobotics31384/unicornRiders/robots/Turret/smw_coin.wav &')
        self.player1Text.set("1")
        self.win();

    def score(self):
        self.player1Text.set("10")

    def win(self):
        os.system('play --no-show-progress ~/Dropbox/DTU/2.Sem/ModularRobotics31384/unicornRiders/robots/Turret/smw_course_clear.wav &')
        label = tkSimpleDialog.askstring("Highscore", "Name of Player")
        print label


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

root.bind("<KeyPress>", keyDown)
root.bind("<KeyRelease>", keyRelease)


## Start Worker threads
serialWorker = Thread(target=serialWorkerFunction, args=(serialQueue,))
serialWorker.setDaemon(True)
serialWorker.start()

statWorker = Thread(target=pollForStats)
#statWorker.start()


# Hand main thread over to the Tkinter event loop
root.mainloop()

# Close open handles on exit
logFile.close()
serial.close()
serialWorker.stop()
statWorker.stop()