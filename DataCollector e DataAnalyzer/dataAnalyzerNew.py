# -*- coding: utf-8 -*-
"""
Created on Thu Jan 27 14:14:49 2022

@author: Lorenzo Leoni
"""

import numpy as np
import pandas as pd
#import matplotlib.pyplot as plt
import pmdarima as pm
import mysql.connector
import datetime
import time as tm
from datetime import datetime as dt
from threading import Thread as th

class FogFrostAllertsCreator (th):
    def __init__(self, station_code, areaID, conn1, cursor1, index):
        th.__init__(self)
        self.station_code = station_code
        self.conn1 = conn1
        self.areaID = areaID
        self.cursor1 = cursor1
        self.index = index
        self.old_final_time = final_old_time_list[self.index]
        self.recent_time = dt.strptime("2021-04-06 15:00:00", '%Y-%m-%d %H:%M:%S')
    
    def run(self):
        self.cursor1.execute("SELECT max(time) FROM test.aprsdata WHERE name = %(code)s;", {'code':self.station_code})
        temporary = self.cursor1.fetchall()
        self.recent_time = list(temporary[0])[0]
        final_old_time_list[self.index] = self.recent_time
        if flag == False or self.recent_time == self.old_final_time:
            print("Dentro")
            self.conn1.close()
            self.cursor1.close()
            return
        final_old_time_list[self.index] = self.recent_time
        summaryT = pd.DataFrame(index=["tf","t1","t2","t3"], columns=["value", "I_low", "I_up"])
        summaryUR = pd.DataFrame(index=["tf","t1","t2","t3"], columns=["value", "I_low", "I_up"])
        summaryTd = pd.DataFrame(index=["tf","t1","t2","t3"], columns=["value", "I_low", "I_up"])
        self.__tempURForcaster("temperature", summaryT)
        self.__tempURForcaster("humidity", summaryUR)
        for j in range(3):
            for i in range(4):
                summaryTd.iat[i,j] = self.__computeTd(summaryT.iat[i,j], summaryUR.iat[i,j])
        print(self.station_code)
        print(summaryT)
        print(summaryUR)
        print(summaryTd)        
        if summaryT.at['tf','value'] >= summaryTd.at['tf','I_low'] and summaryT.at['tf','value'] <= summaryTd.at['tf','I_up']:
           if summaryT.at['tf','value'] > 0:
               print('CAUTION! Fog allert')
               self.__allertsCreator("tf", "FOG")
               self.__debug("tf", "FOG", summaryT, summaryTd)
           else:
               print('CAUTION! Frost allert')
               self.__allertsCreator("tf", "FROST")
               self.__debug("tf", "FROST", summaryT, summaryTd)
        elif summaryT.at['t1','value'] >= summaryTd.at['t1','I_low'] and summaryT.at['t1','value'] <= summaryTd.at['t1','I_up']:
           if summaryT.at['t1','value'] > 0:
               print('Caution! Fog')
               self.__allertsCreator("t1", "FOG")
               self.__debug("t1", "FOG", summaryT, summaryTd)
           else:
               print('ATTENZIONE! Allerta brina')
               self.__allertsCreator("t1", "FROST")
               self.__debug("t1", "FROST", summaryT, summaryTd)
        elif summaryT.at['t2','value'] >= summaryTd.at['t2','I_low'] and summaryT.at['t2','value'] <= summaryTd.at['t2','I_up']:
           if summaryT.at['t2','value'] > 0:
               print('ATTENZIONE! Allerta nebbia')
               self.__allertsCreator("t2", "FOG")
               self.__debug("t2", "FOG", summaryT, summaryTd)
           else:
               print('ATTENZIONE! Allerta brina')
               self.__allertsCreator("t2", "FROST")
               self.__debug("t2", "FROST", summaryT, summaryTd)
        elif summaryT.at['t3','value'] >= summaryTd.at['t3','I_low'] and summaryT.at['t3','value'] <= summaryTd.at['t3','I_up']:
           if summaryT.at['t3','value'] > 0:
               print('ATTENZIONE! Allerta nebbia')
               self.__allertsCreator("t3", "FOG")
               self.__debug("t3", "FOG", summaryT, summaryTd)
           else:
               print('ATTENZIONE! Allerta brina')
               self.__allertsCreator("t3", "FROST")
               self.__debug("t3", "FROST", summaryT, summaryTd)
        self.conn1.commit()
        self.conn1.close()
        self.cursor1.close()
        
    def __tempURForcaster(self, parameter, dataToUpdate):
        if parameter == "temperature":
            self.cursor1.execute("SELECT time, temperature FROM test.aprsdata WHERE name = \
                       %(station)s;", {'station':self.station_code})
        else:
            self.cursor1.execute("SELECT time, humidity FROM test.aprsdata WHERE \
                           name = %(station)s;", {'station':self.station_code})
        info = self.cursor1.fetchall()
        thread_DB = pd.DataFrame(columns=["time", parameter])
        for i in range(len(info)):
            thread_DB.loc[i] = list(info[i])
        min_time = self.recent_time - datetime.timedelta(hours=24)
        thread_DB = thread_DB[thread_DB.time > min_time]
        y = thread_DB[parameter]
        model = pm.auto_arima(y, start_p=1, start_q=1,
                              test='adf',
                              max_p=3, max_q=3,
                              m=1,
                              d=None,
                              seasonal=False,
                              start_P=0,
                              D=0,
                              trace=True,
                              error_action='ignore',
                              suppress_warnings=True,
                              stepwise=True)
        fc, confint = model.predict(n_periods=3, return_conf_int=True)
        dataToUpdate.at['tf', 'value'] = thread_DB.iat[len(thread_DB)-1,1]
        dataToUpdate.at['t1', 'value'] = fc[0]
        dataToUpdate.at['t2', 'value'] = fc[1]
        dataToUpdate.at['t3', 'value'] = fc[2]
        if parameter == "temperature":
            dataToUpdate.at['tf', 'I_low'] = dataToUpdate.at['tf', 'value'] - 0.15
            dataToUpdate.at['t1', 'I_low'] = dataToUpdate.at['t1', 'value'] - 0.18
            dataToUpdate.at['t2', 'I_low'] = dataToUpdate.at['t2', 'value'] - 0.21
            dataToUpdate.at['t3', 'I_low'] = dataToUpdate.at['t3', 'value'] - 0.24
            dataToUpdate.at['tf', 'I_up'] = dataToUpdate.at['tf', 'value'] + 0.15
            dataToUpdate.at['t1', 'I_up'] = dataToUpdate.at['t1', 'value'] + 0.18
            dataToUpdate.at['t2', 'I_up'] = dataToUpdate.at['t2', 'value'] + 0.21
            dataToUpdate.at['t3', 'I_up'] = dataToUpdate.at['t3', 'value'] + 0.24
        if parameter == "humidity":
            dataToUpdate.at['tf', 'I_low'] = dataToUpdate.at['tf', 'value'] - 0.50
            dataToUpdate.at['t1', 'I_low'] = dataToUpdate.at['t1', 'value'] - 0.55
            dataToUpdate.at['t2', 'I_low'] = dataToUpdate.at['t2', 'value'] - 0.60
            dataToUpdate.at['t3', 'I_low'] = dataToUpdate.at['t3', 'value'] - 0.65
            dataToUpdate.at['tf', 'I_up'] = dataToUpdate.at['tf', 'value'] + 0.50
            dataToUpdate.at['t1', 'I_up'] = dataToUpdate.at['t1', 'value'] + 0.55
            dataToUpdate.at['t2', 'I_up'] = dataToUpdate.at['t2', 'value'] + 0.60
            dataToUpdate.at['t3', 'I_up'] = dataToUpdate.at['t3', 'value'] + 0.65
        
    def __computeTd(self, T, UR):
        a = 17.27
        b = 237.7
        alpha = self.__computeAlpha(T,UR)
        return (b*alpha)/(a-alpha)
                
    def __computeAlpha(self, T,UR):
        a = 17.27
        b = 237.7
        return ((a*T)/(b+T)) + np.log(UR/100)
    
    def __allertsCreator(self, t, typology):
        coulor = None
        delta = None
        trad = None
        if t == "tf":
            coulor = "RED"
            delta = "attuale"
        elif t == "t1":
            coulor = "ORANGE"
            delta = "10 minuti"
        elif t == "t2":
            coulor = "GREEN"
            delta = "20 minuti"
        else:
            coulor = "WHITE"
            delta = "30 minuti"
        if typology == "FROST":
            trad = "brina"
        else:
            trad = "nebbia"
        description = "Rischio " + trad + " tra " + delta
        self.cursor1.execute("INSERT INTO test.alarm (time, type, color, idArea, description) VALUES (%s, %s, %s, %s, %s);",\
                              (dt.now().strftime('%Y-%m-%d %H:%M:%S'), typology, coulor, self.areaID, description))
     
    def __debug(self, t, typology, summaryT, summaryTd):
        delta = None
        if t == "tf":
            delta = "now"
        elif t == "t1":
            delta = "10 minutes"
        elif t == "t2":
            delta = "20 minutes"
        else:
            delta = "30 minutes"
        print(" ")
        print("***")
        print("CAUTION! " + str.lower(typology) + " allert")
        print("-ID area: " + str(self.areaID))
        print("-Recent time: " + dt.now().strftime('%Y-%m-%d %H:%M:%S'))
        print("-Final time: " + self.recent_time.strftime('%Y-%m-%d %H:%M:%S'))
        print("-Delta: " + delta)
        print("-Interval: [" + str(summaryTd.at[t, "I_low"]) + "; " + str(summaryT.at[t, "value"]) + "; " + str(summaryTd.at[t, "I_up"]) + "]")
        print("***")
        print(" ")
#------------------------------------------------------------------------------   
# definizione dei parametri per aprire la connessione con il DB
config = {
  'host':'progettopacdb.mysql.database.azure.com',
  'user':'dsalvetti',
  'password':'Progettopac2021!',
  'database':'test',
  'client_flags': [mysql.connector.ClientFlag.SSL],
  'ssl_ca': 'C:\\Users\\loren\\Desktop\\Progetto PAC\\DataCollector e DataAnalyzer\\DigiCertGlobalRootG2.crt.pem'
}

# avvio dell'applicazione
"""
stop_time = input("Stop datatime [YYYY-MM-DD HH:MM:SS]: ")
print(" ")
"""
stop_time = "2022-01-31 00:00:00"
stop_time = dt.strptime(stop_time, '%Y-%m-%d %H:%M:%S')
final_old_time_list = [None]*5
flag = True

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
    cursor.close()
    conn.close()
    
    # creazione dei thread per la creazione delle allerte nebbia e brina
    fogFrostAllertsCreators = []
    for i in range(len(rows)):
        if area_DB.at[i, "nameAprStation"] is not None:
            conn1 = mysql.connector.connect(**config)
            cursor1 = conn1.cursor()
            t = FogFrostAllertsCreator(area_DB.at[i, "nameAprStation"], area_DB.at[i, "idArea"], conn1, cursor1, i)
            fogFrostAllertsCreators.append(t)
    for i in fogFrostAllertsCreators:
        i.start()
    for i in fogFrostAllertsCreators:
        i.join()
       
    # chiusura della connessione con il DB
    print("Done.")
    print("***")
    print(" ")
    tm.sleep(60*5)