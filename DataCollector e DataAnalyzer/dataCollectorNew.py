# -*- coding: utf-8 -*-
"""
Created on Tue Jan 25 21:05:18 2022

@author: Lorenzo Leoni
"""
import mysql.connector
import pandas as pd
import requests as rq
import time as tm
from threading import Thread as th
from datetime import datetime as dt
import datetime

class MyThread (th):
    def __init__(self, name, station_code, API_key):
        th.__init__(self)
        self.name = name
        self.station_code = station_code
        self.API_key = API_key
        self.esecution = 1
        self.id_row = 1
        self.delta = datetime.timedelta(hours=1)
    def run(self):
        print("Esecution #", self.esecution, "of thread #", self.name,"at", dt.now().strftime('%Y-%m-%d %H:%M:%S'))
        address = "https://api.aprs.fi/api/get?name=" + self.station_code + "&what=wx&apikey=" + self.API_key + "&format=json"
        response = rq.get(address)
        data = response.json()
        time = dt.utcfromtimestamp(int(data["entries"][0]["time"]))
        time = time + self.delta
        time = time.strftime('%Y-%m-%d %H:%M:%S')
        temp = float(data["entries"][0]["temp"])
        pressure = float(data["entries"][0]["pressure"])
        humidity = int(data["entries"][0]["humidity"])
        wind_direction = int(data["entries"][0]["wind_direction"])
        wind_speed = float(data["entries"][0]["wind_speed"])
        wind_gust = float(data["entries"][0]["wind_gust"])
        rain_1h = float(data["entries"][0]["rain_1h"])
        rain_24h = float(data["entries"][0]["rain_24h"])
        rain_mn = float(data["entries"][0]["rain_mn"])
        #luminosity = float(data["entries"][0]["luminosity"])
        cursor.execute("SELECT max(time) FROM test.aprsdata WHERE name = %(code)s;", {'code':self.station_code})
        temporary = cursor.fetchall()
        temporary = list(temporary[0])[0]
        if temporary is not None:
            self.time_old = temporary.strftime('%Y-%m-%d %H:%M:%S')
        else:
            self.time_old = None
        print("- Actual time:", time)
        print("- Old time:", self.time_old)
        if self.time_old is None or time != self.time_old:
            cursor.execute("INSERT INTO test.aprsdata (name, time, temperature, pressure, humidity, windDirection, windSpeed, windGust, \
                           rainOneHour, rainDay, rainMidNight) VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s);",\
                                  (self.station_code, time, temp, pressure, humidity, wind_direction, wind_speed, wind_gust, rain_1h, rain_24h, rain_mn))
            conn.commit()
            print("- #", self.id_row, "/", self.station_code, "/", time, "/", pressure, "hPa /", temp, "°C /", humidity, "% /", wind_direction, "° /", wind_speed, "m/s / (gust)", wind_gust, "m/s /", rain_1h, "mm /", rain_24h, "mm /", rain_mn, "mm")
            print("° Update committed to DB")
            self.id_row += 1
        else:
            print("° Same acquisition --> no new row")
        self.esecution += 1

# definizione dei parametri per aprire la connessione con il DB
config = {
  'host':'progettopacdb.mysql.database.azure.com',
  'user':'dsalvetti',
  'password':'Progettopac2021!',
  'database':'test',
  'client_flags': [mysql.connector.ClientFlag.SSL],
  'ssl_ca': 'C:\\Users\\loren\\Desktop\\Progetto PAC\\DataCollector e DataAnalyzer\\DigiCertGlobalRootG2.crt.pem'
}

# definizione delle API key
API_key = ["165780.vwUJxymaP4yIjUx", "167256.2UfZjqsO8842Bk3l", "167471.rw8Fn5BbbYAYdMw"]
API_key_num = 0

# avvio dell'applicazione
stop_time = input("Stop datatime [YYYY-MM-DD HH:MM:SS]: ")
print(" ")
stop_time = dt.strptime(stop_time, '%Y-%m-%d %H:%M:%S')

while stop_time > dt.now():
    
    # apertura della connessione con il DB
    connected = False
    while connected == False:
        try:
            conn = mysql.connector.connect(**config)
            print("***")
            print("Connection established")
        except mysql.connector.Error:
            print("An error is occured at " + dt.now().strftime('%Y-%m-%d %H:%M:%S'))
            print("--> Retrying between 10 seconds")
            print(" ")
            tm.sleep(10)
        else:
            cursor = conn.cursor()
            connected = True

    # accesso ai dati relativi alle zone
    cursor.execute("SELECT * FROM test.area;")
    rows = cursor.fetchall()
    area_DB = pd.DataFrame(columns=["idArea","areaName","lat","lng","nameAprStation","istatCode"])
    for i in range(len(rows)):
        area_DB.loc[i] = list(rows[i])
    
    # switch delle API key
    if API_key_num == 0:
        j = 0
        API_key_num = 1
        print("API key: " + API_key[j])
    elif API_key_num == 1:
        j = 1
        API_key_num = 2
        print("API key: " + API_key[j])
    else:
        j = 2
        API_key_num = 0
        print("API key: " + API_key[j])
    
    # creazione dei thread
    threads = []
    for i in range(len(rows)):
        if area_DB.at[i, "nameAprStation"] is not None:
            t = MyThread(i, area_DB.at[i, "nameAprStation"], API_key[j])
            threads.append(t)
        
    # avvio dei thread 
    for go in threads:
        go.run()
    
    # chiusura della connessione con il DB
    cursor.close()
    conn.close()
    print("Done.")
    print("***")
    print(" ")
    tm.sleep(60*9)