# -*- coding: utf-8 -*-
"""
Created on Fri Jan 21 17:10:23 2022

@author: lorenzo Leoni
"""

import requests as rq
import time as tm
import csv 
from datetime import datetime as dt
from threading import Thread as th

class MyThread (th):
    def __init__(self, address, period, stop_time):
        th.__init__(self)
        self.address = address
        self.period = period
        self.stop_time = stop_time
    def run(self):
        esecution = 1
        id_row = 1
        time_old = dt.now()
        name = "data_" + station_code + "_" + dt.now().strftime('%Y_%m_%d') + ".csv"
        with open(name,'w', newline='') as csvfile:
            writer = csv.writer(csvfile)
            writer.writerow(["ID, Time, Pressure", "Temperature", "Humidity", "Wind_direction", "Wind_speed", "Wind_gust"])
        while self.stop_time > dt.now():
            print("Esecution #", esecution, "at", dt.now().strftime('%Y-%m-%d %H:%M:%S'))
            response = rq.get(self.address)
            data = response.json()
            pressure = float(data["entries"][0]["pressure"])
            time_new = dt.utcfromtimestamp(int(data["entries"][0]["time"])).strftime('%Y-%m-%d %H:%M:%S')
            temperature = float(data["entries"][0]["temp"])
            humidity = int(data["entries"][0]["humidity"])
            wind_direction = int(data["entries"][0]["wind_direction"])
            wind_speed = float(data["entries"][0]["wind_speed"])
            wind_gust = float(data["entries"][0]["wind_gust"])
            if esecution == 1 or time_new != time_old:
                with open(name,'a', newline='') as csvfile:
                    writer = csv.writer(csvfile)
                    writer.writerow([id_row, time_new, pressure, temperature, humidity, wind_direction, wind_speed, wind_gust])
                print("  #", id_row, "/", time_new, "/", pressure, "hPa /", temperature, "°C /", humidity, "% /", wind_direction, "° /", wind_speed, "m/s / (gust)", wind_gust, "m/s")
                id_row += 1
                time_old = time_new
            else:
                print(" same acquisition --> no new row")
            esecution += 1
            tm.sleep(self.period)

print("\n**Data collection through APRS.FI's API invocation**\n")
station_code = input("Station code: ")
API_key = input("API key: ")
period = int(input("Period [s]: "))
stop_time = input("Stop datatime [YYYY-MM-DD HH:MM:SS]: ")
API_address = "https://api.aprs.fi/api/get?name=" + station_code + "&what=wx&apikey=" + API_key + "&format=json"
print(" ")
MyThread = MyThread(API_address, period, dt.strptime(stop_time, '%Y-%m-%d %H:%M:%S'))
MyThread.run()