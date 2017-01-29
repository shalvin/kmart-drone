# Use GPIO pins 13, 15, 16, 18
# 
# To convert input (-100, 100) to Voltage level
# 3.3 / 2 + 3.3 / 2 * input / 100

import readline
from RPi import GPIO
from cmd import Cmd
from time import sleep

def convert_direction(inp):
    voltage =  1.65 + 1.65 * float(inp) / 100.0
    print("Voltage: %f " % (voltage))
    return voltage / 3.3 * 100.0

def convert_throttle(inp):
    voltage = 3.3 * inp / 100
    return voltage / 3.3 * 100.0

def reset():
    global pwms
    for pwm in pwms:
        pwm.ChangeDutyCycle(0)

def cleanup():
    reset()
    global pwms
    for pwm in pwms:
        pwm.stop()
    GPIO.cleanup()


class ControllerShell(Cmd):
    intro = "Starting motor controller"
    prompt = "(motor-control): "

    def do_go(self, args):
        global pwms

        try:
            arr = [int(i) for i in args.split(" ")]
        except ValueError:
            print("Give us a number fool")
            return

        if len(arr) != len(pwms):
            print("Give us 4")
            return
        
        throttle = convert_throttle(arr[0])
        yaw = convert_direction(arr[1])
        pitch = convert_direction(arr[2])
        roll = convert_direction(arr[3])
        pwm_values = [throttle, yaw, pitch, roll]

        for i in range(len(pwm_values)):
            pwms[i].ChangeDutyCycle(pwm_values[i])

        print("Gone (%d, %d, %d, %d)" % (pwm_values[0], pwm_values[1], pwm_values[2], pwm_values[3]))

    def do_reset(self, args):
        reset()

    def do_pair(self, args):
        global pwms
        throttle = pwms[0]
        throttle.ChangeDutyCycle(50)
        sleep(0.5)
        throttle.ChangeDutyCycle(0)
        sleep(0.5)
        #throttle.ChangeDutyCycle(50)
        #sleep(0.5)
        #throttle.ChangeDutyCycle(0)
        #sleep(0.5)
        throttle.ChangeDutyCycle(50)

    def do_frequency(self, args):
        try:
            freq = int(args)
        except:
            print("Error parsing input")
            return
        global FREQUENCY
        FREQUENCY = freq
        for pwm in pwms:
            pwm.ChangeFrequency(freq)
 
    def close(self):
        cleanup()



# Setup GPIO
GPIO.setmode(GPIO.BOARD)
CHANNELS = [13, 15, 16, 18]
FREQUENCY = 10

GPIO.setup(CHANNELS, GPIO.OUT)
pwm_throttle = GPIO.PWM(CHANNELS[0], FREQUENCY)
pwm_throttle.ChangeDutyCycle(0)
pwm_yaw = GPIO.PWM(CHANNELS[1], FREQUENCY)
pwm_yaw.ChangeDutyCycle(50)
pwm_pitch = GPIO.PWM(CHANNELS[2], FREQUENCY)
pwm_pitch.ChangeDutyCycle(50)
pwm_roll = GPIO.PWM(CHANNELS[3], FREQUENCY)
pwm_roll.ChangeDutyCycle(50)
pwms = [pwm_throttle, pwm_yaw, pwm_pitch, pwm_roll]

for pwm in pwms:
    pwm.start(0)

shell = ControllerShell()
try:
    shell.cmdloop()
except KeyboardInterrupt:
    print("Exiting")
    #GPIO.cleanup()
