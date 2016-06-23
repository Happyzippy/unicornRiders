from threading import Thread
from Queue import Queue
from serial import Serial
import Tkinter as tk
import tkSimpleDialog
import time
import os
import numpy as np
import sys
from twython import Twython


## GAME STATE

CONSUMER_KEY = 'e'
CONSUMER_SECRET = 'e'
OAUTH_TOKEN = 'e'
OAUTH_TOKEN_SECRET = 'e'

twitter = Twython(CONSUMER_KEY, CONSUMER_SECRET,
                  OAUTH_TOKEN, OAUTH_TOKEN_SECRET)

#auth = twitter.oauth.OAuth(OAUTH_TOKEN, OAUTH_TOKEN_SECRET, CONSUMER_KEY, CONSUMER_SECRET)
#twitter_api = twitter.Api(domain='api.twitter.com', api_version='1.1', auth=auth)
#status = twitter_api.PostUpdate('I love python-twitter!')

## INITIALIZE SERIAL CONNECTION
serial = Serial('/dev/ttyUSB0', baudrate=57600, timeout=0.7)

logFile = open("Output.txt", "w")

## SERIAL WORKER SETUP FOR ASYNC WRITING
serialQueue = Queue()
def serialWorkerFunction(queue):
    while True:
        # get job or wait for new job in queue 
        command = queue.get()
        readSerial(command)
        queue.task_done()

## WORKER FUNCTION FOR PULLING STATS
def pollForStats():
    while(True):
        serialQueue.put('t')
        time.sleep(0.5)


## READ FROM SERIAL
def readSerial(command):
    try:
        while(serial.inWaiting()):
            serialLine = serial.readline()
            print serialLine
            if str.strip(serialLine) == "GOAL":
                app.score()
            if str.strip(serialLine) == "THROW":
                app.throw()
    except Exception,e: 
        print str(e)
        pass



    print command;

def postOnTwitter(name, score):
    twitter.update_status(status="%s just scored %u on the unicorn turret" % (name, score))
    print 


## TKINTER GUI
class Window():
    def __init__(self, master):
        self.frame = tk.Frame(master)

        self.player1Text = tk.StringVar()
        self.player1Text.set("0")
        self.player1Label = tk.Label(master, font=("Helvetica", 154), textvariable=self.player1Text).grid(row=0, column = 0, padx=10, pady=10)

        self.resetButton = tk.Button(root, text="Start", command=self.resetGame)
        self.resetButton.grid(row = 2, column = 1)

        self.player1Points = 0;
        self.highscore = 10;

        self.throws = 0

    def updateUi(self):
        self.player1Text.set(self.player1Points)

    def resetGame(self):
        self.player1Points += 1;
        self.updateUi();
        self.win();
        self.player1Points = 0
        self.throws = 0
        self.updateUi();

    def throw(self):
        self.throws += 1
        if self.throws > 5:
            self.win();

    def score(self):
        os.system('play --no-show-progress ~/Dropbox/DTU/2.Sem/ModularRobotics31384/unicornRiders/robots/Turret/smw_coin.wav &')
        self.player1Points += 1
        self.updateUi();

    def win(self):
        os.system('play --no-show-progress ~/Dropbox/DTU/2.Sem/ModularRobotics31384/unicornRiders/robots/Turret/smw_course_clear.wav &')
        name = tkSimpleDialog.askstring("Highscore!! Post it to twitter", "Name of Player")
        score = self.player1Points
        if name:
            postOnTwitter(name, score)


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
statWorker.start()


# Hand main thread over to the Tkinter event loop
root.mainloop()

# Close open handles on exit
serial.close()
serialWorker.stop()
statWorker.stop()