import serial
import io
import argparse
import time

parser = argparse.ArgumentParser(description='Command Serial Messages')
parser.add_argument('--set_color', type=str, help="Supply Color String <RED>,<GREEN>,<BLUE>", default=None)
parser.add_argument('--set_luminance', type=str, help="Supply Luminance Value <LUMINANCE>", default=None)
parser.add_argument('--set_rate', type=str, help="Supply Pulse Rate <PULSE RATE>", default=None)
parser.add_argument('--save', type=int, help="Save current led settings under id", default=None)
parser.add_argument('--current_settings', action='store_true', help="echo current led settings", default=None)

args = parser.parse_args()



led = serial.Serial('/dev/ttyUSB0' ,baudrate=115200 ,bytesize=8, parity='N', stopbits=1, timeout=1)
led.close()
led.open()
sio = io.TextIOWrapper(io.BufferedRWPair(led, led))
if args.set_color:
    sio.write(f"COLOR {args.set_color}\r")
    sio.flush()

if args.set_luminance:
    if int(args.set_luminance) > 1000:
       sio.write(f"LUM 1000\r")
    elif int(args.set_luminance) < 0:
       sio.write(f"LUM 0\r")
    else:
       sio.write(f"LUM {args.set_luminance}\r")
    sio.flush()

if args.set_rate:
    if int(args.set_rate) > 255:
        sio.write(f"RATE 255\r")
    elif int(args.set_rate) < 0:
        sio.write(f"RATE 0\r\n")
    else:
        sio.write(f"RATE {args.set_rate}\r")
    sio.flush()

if args.save:
   sio.write(f"ID {args.save}")
   sio.flush()

if args.current_settings:
   sio.write("SAVE?\r")
   sio.flush()
   response = sio.read()
   print(response.strip())

led.close()
