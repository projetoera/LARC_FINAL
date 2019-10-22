from __future__ import print_function
import numpy as np
import cv2 as cv
from math import atan
from gpiozero import LED
import time
import serial
import argparse

def make_1080p():
    cap.set(3, 1920)
    cap.set(4, 1080)

def make_720p():
    cap.set(3, 1280)
    cap.set(4, 720)

def make_480p():
    cap.set(3, 640)
    cap.set(4, 480)

def change_res(width, height):
    cap.set(3, width)
    cap.set(4, height)

#arduino = serial.Serial('/dev/ttyACM0', 9600)
#open_can

def cam():
 cap = cv.VideoCapture(0)

 make_480p()
 change_res(640, 480)

#variables
 qx=0
 qy=0
 i=0
 a=0
 b=0
 cX0=0
 cX1=0
 cX2=0
 cX3=0
 cY0=0
 cY1=0
 cY2=0
 cY3=0
 A=0
 Cximg=320
 Cyimg=240
 q=0
 k=0
 metadedafita=20
 motor1 = LED(19)
 motor2 = LED(6)
 motor3 = LED(11)
 motor4 = LED(10)
 motor1i = LED(26)
 motor2i = LED(13)
 motor3i = LED(5)
 motor4i = LED(9)
 o=0
 oa=0
 vel1 = LED(22)
 vel2 = LED(27)
 vel3 = LED(17)
 vel4 = LED(4)
 
 while (cap.isOpened()):
    ret, img = cap.read()
    
    if ret == True:
        #gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
        gray = cv.cvtColor(img, cv.COLOR_BGR2HSV)
        gray_filter=cv.inRange(gray, (0, 0, 120), (180, 242, 255))
        #ret,thresh = cv2.threshold(dst,100,255,0)
        ret,thresh = cv.threshold(gray_filter,100,255,0)
        #img_filter=cv.morphologyEx(thresh, cv.MORPH_OPEN,
        #cv.imshow('Morph', img_filter)
        kernel1 = np.ones((3,3),np.uint8)
        img_filter = cv.dilate(thresh, kernel1, iterations=5)
        kernel = np.ones((3,3),np.uint8)
        img_filter1 = cv.erode(img_filter,kernel,iterations = 20)
        #cv.imshow('Erode', img_filter)
        contours, hierarchy = cv.findContours(img_filter1,cv.RETR_TREE,cv.CHAIN_APPROX_SIMPLE)
        #ret,thresh = cv.threshold(gray,100,255,0)

        #contours, hierarchy = cv.findContours(thresh,cv.RETR_TREE,cv.CHAIN_APPROX_SIMPLE)
        for c in contours:
            M = cv.moments(c)
            if M["m00"] != 0:
             cX = int(M["m10"] / M["m00"])
             cY = int(M["m01"] / M["m00"])
             cX3=cX2
             cX2=cX1
             cX1=cX0
             cX0=cX
             cY3=cY2
             cY2=cY1
             cY1=cY0
             cY0=cY
             q=q+1
             k=abs(int(Cximg-cX))
             j=abs(int(Cyimg-cY))
             if (j-k)<0:
                 if (abs(cX0-cX2)<=10) & (abs(cX1-cX3)<=10) & (abs(cX0-cX1)>50) & (abs(cX2-cX3)>50):
                  if (a!=0) & ((a%2)==0):
                      i=0
                      a=0
                  elif (a!=0) & ((a%2)==1):
                      i=1
                      a=0
                  elif (b!=0) & ((b%2)==0):
                      i=1
                      b=0
                  elif (b!=0) & ((b%2)==1):
                      i=0
                      b=0
                  
                  i=i+1
                  dy=int(qy-cY)
                  qy=cY
                  dx=Cximg-cX
                  erro=int(dx+qx)
                  qx=dx
                  print('I:',i)
                  if (abs(erro)<=25) & (abs(dy)<=15):
                     oa=1
                     if (o!=oa):
                         o=oa
                         motor1i.off()
                         motor2i.off()
                         motor3i.off()
                         motor4i.off()
                         time.sleep(0.1)
                     print('Correto')
                     motor1.off()
                     motor2.off()
                     motor3.off()
                     motor4.off()
                     motor1i.on()
                     motor2i.on()
                     motor3i.on()
                     motor4i.on()
                     #vel1.on
                     #vel2.on
                     #vel3.on
                     #vel4.on
                     

                     
                     #ré
                     #if (o!=oa):
                      #   o=oa
                       #  motor1i.off()
                         #motor2i.off()
                         #motor3i.off()
                         #motor4i.off()
                         #time.sleep(0.1)
                     #motor1.on()
                     #motor2.on()
                     #motor3.on()
                     #motor4.on()
                     #motor1i.on()
                     #motor2i.on()
                     #motor3i.on()
                     #motor4i.on()
                     #vel1.on
                     #vel2.on
                     #vel3.on
                     #vel4.on
                     
                     
                  #elif ((abs(Cyimg-cY1)<=10) & (abs(Cyimg-cY0)>30)) or ((abs(Cyimg-cY0)<=10) & (abs(Cyimg-cY1)>30)) :
                     #print('Translação esquerda tantos mm')
                     #translação esquerda tantos mm.
                     #rotaciona horario 90 graus
                     #anda ré tantos mm.
                
                  else:
                     #vel1.off()
                     #vel2.off()
                     #vel3.off()
                     #vel4.off()
                     if (abs(dy)<=15):
                         oa=2
                         if (o!=oa):
                             o=oa
                             motor1i.off()
                             motor2i.off()
                             motor3i.off()
                             motor4i.off()
                             time.sleep(0.1)
                         if (A==0):
                             print('Movimento 2 translacional, distancia de',-erro)
                             if (erro<0):
                                 motor1.on()
                                 motor2.off()
                                 motor3.off()
                                 motor4.on()
                                 motor1i.on()
                                 motor2i.on()
                                 motor3i.on()
                                 motor4i.on()
                             else:
                                 motor1.off()
                                 motor2.on()
                                 motor3.on()
                                 motor4.off()
                                 motor1i.on()
                                 motor2i.on()
                                 motor3i.on()
                                 motor4i.on()
                         elif (A==1):
                             i=i-1
                             A=0                 
                     else:
                         oa=3
                         if (o!=oa):
                             o=oa
                             motor1i.off()
                             motor2i.off()
                             motor3i.off()
                             motor4i.off()
                             time.sleep(0.1)
                         angulo=atan((cY-Cyimg)/(cX-Cximg))*180/3.14
                         print('Movimento 2 rotacional, angulo de',angulo)
                         if (angulo<0):
                             motor1.off()
                             motor2.off()
                             motor3.on()
                             motor4.on()
                             motor1i.on()
                             motor2i.on()
                             motor3i.on()
                             motor4i.on()
                         else:
                             motor1.on()
                             motor2.on()
                             motor3.off()
                             motor4.off()
                             motor1i.on()
                             motor2i.on()
                             motor3i.on()
                             motor4i.on()
                                        
                 else:
                  motor1i.off()
                  motor2i.off()
                  motor3i.off()
                  motor4i.off()
                  if (i%2)==0:
                      a=a+1
                      b=0
                      A=1
                      print('A:',a)
                  elif (i%2)==1:
                      b=b+1
                      a=0
                      A=1
                      print('B:',b)

               
             elif  (j-k)>0:
                 if (abs(cY0-cY2)<=10) & (abs(cY1-cY3)<=10) & (abs(cY0-cY1)>50) & (abs(cY2-cY3)>50):
                  if (a!=0) & ((a%2)==0):
                      i=0
                      a=0
                  elif (a!=0) & ((a%2)==1):
                      i=1
                      a=0
                  elif (b!=0) & ((b%2)==0):
                      i=1
                      b=0
                  elif (b!=0) & ((b%2)==1):
                      i=0
                      b=0
                  
                  i=i+1
                  dx=int(qx-cX)
                  qx=cX
                  dy=Cyimg-cY
                  erro=int(dy+qy)
                  qy=dy
                  print('I:',i)
                  if (abs(erro)<=25) & (abs(dx)<=15):
                      motor1.on()
                      motor2.off()
                      motor3.off()
                      motor4.on()
                      motor1i.on()
                      motor2i.on()
                      motor3i.on()
                      motor4i.on()
                      #vel1.on
                      #vel2.on
                      #vel3.on
                      #vel4.on
                      
                      #ré
                      #motor1.off()
                      #motor2.on()
                      #motor3.on()
                      #motor4.off()
                      #motor1i.on()
                      #motor2i.on()
                      #motor3i.on()
                      #motor4i.on()
                      #vel1.on
                      #vel2.on
                      #vel3.on
                      #vel4.on
                      print('Correto')
                  else:
                     #vel1.off
                     #vel2.off
                     #vel3.off
                     #vel4.off
                     if (abs(dx)<=15):
                         if (A==0):
                             print('Movimento translacional, distancia de', erro)
                             if (erro>0):
                                 motor1.off()
                                 motor2.off()
                                 motor3.off()
                                 motor4.off()
                                 motor1i.on()
                                 motor2i.on()
                                 motor3i.on()
                                 motor4i.on()
                             else:
                                 
                                 motor1.on()
                                 motor2.on()
                                 motor3.on()
                                 motor4.on()
                                 motor1i.on()
                                 motor2i.on()
                                 motor3i.on()
                                 motor4i.on()
                         elif (A==1):
                             i=i-1
                             A=0
                     else:
                         angulo=atan((cX-Cximg)/(cY-Cyimg))*180/3.14
                         if (angulo<0):
                             motor1.on()
                             motor2.on()
                             motor3.off()
                             motor4.off()
                             motor1i.on()
                             motor2i.on()
                             motor3i.on()
                             motor4i.on()
                         else:
                             motor1.off()
                             motor2.off()
                             motor3.on()
                             motor4.on()
                             motor1i.on()
                             motor2i.on()
                             motor3i.on()
                             motor4i.on()
                         print('Movimento rotacional, angulo de',-angulo)                  
                    
                     
                 else:
                  motor1i.off()
                  motor2i.off()
                  motor3i.off()
                  motor4i.off()
                  if (i%2)==0:
                      a=a+1
                      b=0
                      A=1
                      print('A:',a)
                  elif (i%2)==1:
                      b=b+1
                      a=0
                      A=1
                      print('B:',b)

            else:
             cX, cY = 0, 0
            
             
            cv.circle(thresh, (cX, cY), 5, (255, 255, 255), -1)
            cv.circle(thresh, (320,240), 5, (255, 255, 255), -1)
            cv.putText(thresh, "o", (cX , cY),cv.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 2)        
            #cv2.imshow('img',img)
            cv.imshow('Thresh',thresh)
            
        

        if cv.waitKey(1) & 0xFF == ord ('q'):
            break
    else:
        break


 cap.release()
 cv.destroyAllWindows() 
