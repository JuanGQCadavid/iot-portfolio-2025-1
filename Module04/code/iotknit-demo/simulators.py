from iotknit import *
from datetime import datetime
import threading
import time

init("192.168.14.1")

def tempSimulator_thread():
    tempValues = [18,19,20,21,22,23,24,25,25,26,27]
    # prefix("temp-measure")
    temp1 = publisher("temp-measure")
    while True:
        print("Batch of signals")
        for val in tempValues:
            print(f"Sending signal {val}")
            temp1.publish("temp1", f"{val}")
            time.sleep(1)

def acSimulator_thread():
    status = publisher("status")
    formatted_time = datetime.now().strftime("%H:%M %d - %B - %Y")
    def acCallback(msg):
        print("AC - Command recieved:")
        if msg == "on":
            print("\t - ON")
            status.publish("acStatus", f"{formatted_time} I'm ON :D")
        if msg == "off":
            print("\t - OFF")
            status.publish("acStatus", f"{formatted_time} I'm OFF :(")
            
    button1 = subscriber("switch/r1/set")
    button1.subscribe_change(callback=acCallback)
    run()

temperature_thread = threading.Thread(target=tempSimulator_thread, daemon=True)
ac_thread = threading.Thread(target=acSimulator_thread, daemon=True)

temperature_thread.start()
ac_thread.start()

temperature_thread.join()
ac_thread.join()