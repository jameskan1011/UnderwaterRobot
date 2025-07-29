LED = machine.Pin("LED", machine.Pin.OUT)
LED.on()

from imu import MPU6050
from time import sleep
from machine import Pin, I2C
import math


i2c = I2C(0, sda=Pin(0), scl=Pin(1), freq=400000)
imu = MPU6050(i2c)
i2c.scan()

#thruster adjustment logic
def adjust_thrusters(pitch, roll):
    # Baseline (horizontal reference)
    pitch_baseline = 0
    roll_baseline = 0

    # Threshold for sensitivity
    threshold = 2.0  # degrees

    pitch_error = pitch - pitch_baseline
    roll_error = roll - roll_baseline

    # Horizontal stabilization logic
    if abs(pitch_error) > threshold:
        if pitch_error > 0:
            print("m1 and m2 increased ")
        else:
            print("m1 and m2 decrease ")

    if abs(roll_error) > threshold:
        if roll_error > 0:
            print("m1 decrease , m2 increase ")
        else:
            print("m1 increase , m2 decrease ")


while True:
    ax=round(imu.accel.x,2)
    ay=round(imu.accel.y,2)
    az=round(imu.accel.z,2)
    gx=round(imu.gyro.x)
    gy=round(imu.gyro.y)
    gz=round(imu.gyro.z)
    tem=round(imu.temperature,2)
    
    print("ax",ax,"\t","ay",ay,"\t","az",az,"\t","gx",gx,"\t","gy",gy,"\t","gz",gz,"\t","Temperature",tem,"        ",end="\r")
    
    sleep(0.2)
    
    pitch = math.atan2(ax, math.sqrt(ay*2 + az*2)) * 180 / math.pi
    roll = math.atan2(ay, math.sqrt(ax*2 + az*2)) * 180 / math.pi
    
    print(f"Pitch: {pitch:.2f}, Roll: {roll:.2f}")
    adjust_thrusters(pitch, roll)
    
    sleep(1)