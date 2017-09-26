from Tkinter import *
import cv2
import numpy as np
from matplotlib import pyplot as plt
import time
from PIL import ImageGrab
import serial

font = cv2.FONT_HERSHEY_SIMPLEX

ard = serial.Serial('COM3', 19200)
tagword = ['ax', 'ay', 'az', 'gx', 'gy', 'gz', 'mx', 'my', 'mz', 'end']
resultpt = np.zeros((10,), dtype=np.int)
agm = np.zeros((9,), dtype=np.int)  ## sensor values savings on here
agm_mean = np.zeros((50, 9), dtype=np.int)
agm_ax = np.zeros((50,), dtype=np.int)
agm_ay = np.zeros((50,), dtype=np.int)
agm_az = np.zeros((50,), dtype=np.int)

size = [0, 0, 1000, 1000]
init_axline = [int(size[2] * 0.4), int(size[3] * 0.5), int(size[2] * 0.6), int(size[3] * 0.5)]
axline = [int(size[2] * 0.4), int(size[3] * 0.5), int(size[2] * 0.6), int(size[3] * 0.5)]
ayline = [int(size[2] * 0.2), int(size[3] * 0.3), int(size[2] * 0.2), int(size[3] * 0.7)]
azline = [int(size[2] * 0.3), int(size[3] * 0.2), int(size[2] * 0.7), int(size[3] * 0.2)]

meancount = 0
tempint = 10
ayinfo = [tempint, (ayline[0] - 125), int(np.mean([ayline[3], ayline[1]]))]
nptemp = [ayline[3], ayline[1]]
azinfo = [tempint, int(np.mean([azline[2], azline[0]])), (azline[1] - 25)]

gyroinfo = [int(size[2] * 0.5), int(size[3] * 0.5), int(size[3] * 0.2)]
gyrocir = [int(size[2] * 0.5), int(size[3] * 0.5), int(size[3] * 0.2)]

accelometer_init = [-1300, 200, 17000]

def getaverage():
    global meancount
    while meancount <= 49:
        count = 0
        time.sleep(0.2)
        msg = ''
        msg = ard.read(ard.inWaiting())
        print msg
        if msg <> '':
            try:
                for i in tagword:
                    if msg.index(i):
                        resultpt[count] = msg.index(i)
                        count += 1
            except:
                count = 0
                print 'no word'
                pass
            if count == 10:
                for i in range(count - 1):
                    pos = [resultpt[i] + 3, (resultpt[(i + 1)] - 1)]
                    agm[i] = msg[pos[0]: pos[1]]
                    agm_mean[meancount][i] = agm[i]
                meancount += 1
            count = 0
            print 'sensor value'
            print agm
    count = 0
    for i in agm_mean:
        agm_ax[count] = i[0]
        agm_ay[count] = i[1]
        agm_az[count] = i[2]
        count += 1
    print int(np.mean(agm_ax))
    print int(np.mean(agm_ay))
    print int(np.mean(agm_az))

def gy91():
    count = 0
    time.sleep(0.1)
    msg = ''
    msg = ard.read(ard.inWaiting())
    if msg <> '':
        try:
            for i in tagword:
                if msg.index(i):
                    resultpt[count] = msg.index(i)
                    count += 1
        except:
            count = 0
            print 'no word'
            pass
        if count == 10:
            try:
                for i in range(count - 1):
                    pos = [resultpt[i] + 3, (resultpt[(i + 1)] - 1)]
                    agm[i] = msg[pos[0]: pos[1]]
                    agm_mean[meancount][i] = agm[i]
            except:
                pass
        count = 0
        print 'sensor value'
        print agm



def going():
    while True:
        gy91()
        screen = np.array(ImageGrab.grab(bbox=size))
        accelometer(agm[1], agm[0], agm[2])
        gyroscope(agm[3], agm[4], agm[5])
        print ('gyroscope %d, %d, %d,' %(gyroinfo[0], gyroinfo[1], gyroinfo[2]))
        cv2.line(screen, (axline[0], axline[1]), (axline[2], axline[3]), (0, 125, 0), 2)
        cv2.line(screen, (ayline[0], ayline[1]), (ayline[2], ayline[3]), (0, 125, 0), 2)
        cv2.line(screen, (azline[0], azline[1]), (azline[2], azline[3]), (0, 125, 0), 2)
        cv2.line(screen, ((ayline[0] - 5), ayline[1]), ((ayline[0]), ayline[1]), (0, 125, 0), 2)
        cv2.line(screen, ((ayline[0] - 5), ayline[3]), ((ayline[0]), ayline[3]), (0, 125, 0), 2)
        cv2.line(screen, (azline[0], (azline[1] - 5)), ((azline[0]), azline[1]), (0, 125, 0), 2)
        cv2.line(screen, (azline[2], (azline[3] - 5)), ((azline[2]), azline[3]), (0, 125, 0), 2)
        cv2.putText(screen, '[ %s ]' % ayinfo[0], (ayinfo[1], ayinfo[2]), font, 0.6, (0, 0, 0), 2)
        cv2.putText(screen, '[ %s ]' % azinfo[0], (azinfo[1], azinfo[2]), font, 0.6, (0, 0, 0), 2)
        cv2.circle(screen, (gyrocir[0], gyrocir[1]), gyrocir[2], (125, 0, 0), 2)
        cv2.circle(screen, (gyroinfo[0], gyroinfo[1]), gyroinfo[2], (0, 0, 250), 2)
        cv2.imshow('title', screen)
        if cv2.waitKey(25) & 0xFF == ord('q'):
            cv2.destroyAllWindows()
            break


def indata():
    global agm
    global resultpt

#axline = [int(size[2] * 0.4), int(size[3] * 0.5), int(size[2] * 0.6), int(size[3] * 0.5)]
def accelometer(x, y, z):
    global axline
    move = 1
    ayinfo[0] = y
    azinfo[0] = z
    count = 0
    for i in init_axline:
        axline[count] = i
        count += 1
    while x > 100 or x < -100:
        if x > 100:
            if axline[0] <= 400 and axline[1] < 600 and axline[1] >= 400:
                axline[1] += move
                axline[3] -= move
            elif axline[1] >= 600 and axline[0] < 600 and axline[0] >= 400:
                axline[0] += move
                axline[2] -= move
            elif axline[0] >= 600 and axline[1] <= 600 and axline[1] > 400:
                axline[1] -= move
                axline[3] += move
            elif axline[1] <= 400 and axline[0] <= 600 and axline[0] > 400:
                axline[0] -= move
                axline[2] += move
            x = x - 100
        elif x < -100:
            if axline[0] <= 400 and axline[1] < 600 and axline[1] >= 400:
                axline[1] -= move
                axline[3] += move
            elif axline[1] >= 600 and axline[0] < 600 and axline[0] >= 400:
                axline[0] -= move
                axline[2] += move
            elif axline[0] >= 600 and axline[1] <= 600 and axline[1] > 400:
                axline[1] += move
                axline[3] -= move
            elif axline[1] <= 400 and axline[0] <= 600 and axline[0] > 400:
                axline[0] += move
                axline[2] -= move
            x = x + 100



# maybe getting over 30000 value
# must to find average values
def gyroscope(x, y, z):
    global gyroinfo
    print ('input gyro %d, %d, %d' %(x, y, z))
    move = 1
    count = 0
    for i in gyrocir:
        gyroinfo[count] = i
        count += 1
    if x > 100 or x < -100:
        x = int(x * 0.01)
        gyroinfo[0] += x
    if y > 100 or y < -100:
        y = int(y * 0.01)
        gyroinfo[1] += y
    if z > 100 or z < -100:
        z = int(z * 0.01)
        gyroinfo[2] += z
    if gyroinfo[2] <= 0:
        gyroinfo[2] = 1

def magneticfield():
    return

going()

