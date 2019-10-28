#ROBÔ DE FRENTE

def desliga():
    motor1i.off()
    motor2i.off()
    motor3i.off()
    motor4i.off()

def frente():
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

def re():
    motor1.on()
    motor2.on()
    motor3.on()
    motor4.on()
    motor1i.on()
    motor2i.on()
    motor3i.on()
    motor4i.on()
    #vel1.on
    #vel2.on
    #vel3.on
    #vel4.on

def direita():
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

def esquerda():
    motor1.off()
    motor2.on()
    motor3.on()
    motor4.off()
    motor1i.on()
    motor2i.on()
    motor3i.on()
    motor4i.on()
    #vel1.on
    #vel2.on
    #vel3.on
    #vel4.on

def horario():
    motor1.on()
    motor2.on()
    motor3.off()
    motor4.off()
    motor1i.on()
    motor2i.on()
    motor3i.on()
    motor4i.on()
    #vel1.off
    #vel2.off
    #vel3.off
    #vel4.off

def anti_horario():
    motor1.off()
    motor2.off()
    motor3.on()
    motor4.on()
    motor1i.on()
    motor2i.on()
    motor3i.on()
    motor4i.on()
    #vel1.off
    #vel2.off
    #vel3.off
    #vel4.off