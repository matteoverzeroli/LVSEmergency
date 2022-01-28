# -*- coding: utf-8 -*-
"""
Created on Mon Jan 24 22:11:31 2022

@author: Lorenzo Leoni
"""
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import pmdarima as pm
from datetime import datetime as dt
import datetime
import threading
import time as tm

plt.rcParams.update({'figure.figsize':(9,7), 'figure.dpi':120})

def access_to_CSV_for_dt(index_test):
    dataset = pd.read_csv('C:\\Users\\loren\\Desktop\\Progetto PAC\\DataCollector e DataAnalyzer\\DataCollections\\data_FW0796_2022_01_22.csv')
    dataset = dataset.to_numpy()
    dict_ds = {'ID':0, 'Time':1, 'Pressure':2, 'Temperature':3, 'Humidity':4, 'Wind_direction':5, 'Wind_speed':6}
    for i in range(dataset[:, dict_ds['Time']].size):
        dataset[i, dict_ds['Time']] = dt.strptime(dataset[i, dict_ds['Time']], '%Y-%m-%d %H:%M:%S')
    recent_time = dataset[index_test, dict_ds['Time']]
    return recent_time

def compute_Td(T,UR):
    a = 17.27
    b = 237.7
    alpha = compute_alpha(T,UR)
    return (b*alpha)/(a-alpha)
    
def compute_alpha(T,UR):
    a = 17.27
    b = 237.7
    return ((a*T)/(b+T)) + np.log(UR/100)

class MyThread (threading.Thread):
   def __init__(self, name, target):
      threading.Thread.__init__(self)
      self.name = name
      self.target = target
   def run(self):
      print ("Thread " + self.name + " with target " + self.target + " is working")
      if self.target == "temperature":
          model = pm.auto_arima(temperature, start_p=1, start_q=1,
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
          for j in range(3):
              for i in range(3):
                  if j == 0:
                      pred_T[i,0] = fc[i]
                  elif j == 1:
                      pred_T[i,1] = confint[i,0]
                  else:
                      pred_T[i,2] = confint[i,1]
      if self.target == "humidity":
          model = pm.auto_arima(humidity, start_p=1, start_q=1,
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
          for j in range(3):
              for i in range(3):
                  if j == 0:
                      pred_UR[i,0] = fc[i]
                  elif j == 1:
                      pred_UR[i,1] = confint[i,0]
                  else:
                      pred_UR[i,2] = confint[i,1]
      print("Thread " + self.name + " with target " + self.target + " is terminated")

index_train = 0 # utilizzo di 80 campioni per il training
index_test = 80
final_old_time = dt.now()
recent_time = access_to_CSV_for_dt(index_test)
while index_test != 154:
    
    while final_old_time == recent_time:
        recent_time = access_to_CSV_for_dt(index_test)
        tm.sleep(20)
    
    # accesso ai dati contenuti nel file CSV
    address = "C:\\Users\\loren\\Desktop\\Progetto PAC\\DataCollector e DataAnalyzer\\DataCollections\\data_FW0796_2022_01_22.csv"
    dataset = pd.read_csv(address)
    dataset = dataset.to_numpy();
    dict_ds = {'ID':0, 'Time':1, 'Pressure':2, 'Temperature':3, 'Humidity':4, 'Wind_direction':5, 'Wind_speed':6}
    for i in range(dataset[:, dict_ds['Time']].size):
        dataset[i, dict_ds['Time']] = dt.strptime(dataset[i, dict_ds['Time']], '%Y-%m-%d %H:%M:%S')
    temperature = dataset[index_train:(index_test-1), dict_ds['Temperature']]
    humidity = dataset[index_train:(index_test-1), dict_ds['Humidity']]
    acq_time = dataset[index_train:(index_test-1), dict_ds['Time']]
    
    # creazione degli array in cui verranno inserite le predizioni e i limiti degli IC
    dict_k = {"t1":0, "t2":1, "t3":2}
    dict_info = {"Pred_value":0, "IC_low":1, "IC_up":1}
    pred_T = np.zeros(shape = (3,3))
    pred_UR = np.zeros(shape = (3,3))
    pred_Td = np.zeros(shape = (3,3))

    # avvio dei thread
    thread1 = MyThread("thread#1", "temperature")
    thread2 = MyThread("thread#2", "humidity")
    thread1.start()
    thread2.start()
    thread1.join()
    thread2.join()

    # calcolo delle predizioni sulla temperatura di rugiada e dei relativi intervalli di confidenza
    for j in range(3):
        for i in range(3):
            pred_Td[i,j] = compute_Td(pred_T[i,j], pred_UR[i,j])

    # calcolo della temperatura di rugiada attuale e dell'intervallo di confidenza I
    T_now = temperature[-1]
    Td_now = compute_Td(temperature[-1], humidity[-1])
    I_up = Td_now + 0.5
    I_low = Td_now - 0.5

    # generazione delle allerte
    if T_now >= I_low and T_now <= I_up:
        if Td_now > 0:
            print("ATTENZIONE! Attuale rischio nebbia!")
        else:
            print("ATTENZIONE! Attuale rischio brina!")
    elif pred_T[dict_k['t1'],dict_info['Pred_value']] >= pred_Td[dict_k['t1'],dict_info['IC_low']] and pred_T[dict_k['t1'],dict_info['Pred_value']] <= pred_Td[dict_k['t1'],dict_info['IC_up']]:
        if pred_Td[dict_k['t1'],dict_info['Pred_value']] > 0:
            print("ATTENZIONE! Allerta nebbia alle " + (dt.now() + datetime.timedelta(minutes=10)).strftime('%Y-%m-%d %H:%M:%S'))
        else:
            print("ATTENZIONE! Allerta brina alle " + (dt.now() + datetime.timedelta(minutes=10)).strftime('%Y-%m-%d %H:%M:%S'))
    elif pred_T[dict_k['t2'],dict_info['Pred_value']] >= pred_Td[dict_k['t2'],dict_info['IC_low']] and pred_T[dict_k['t2'],dict_info['Pred_value']] <= pred_Td[dict_k['t2'],dict_info['IC_up']]:
        if pred_Td[dict_k['t2'],dict_info['Pred_value']] > 0:
            print("ATTENZIONE! Allerta nebbia alle " + (dt.now() + datetime.timedelta(minutes=20)).strftime('%Y-%m-%d %H:%M:%S'))
        else:
            print("ATTENZIONE! Allerta brina alle " + (dt.now() + datetime.timedelta(minutes=20)).strftime('%Y-%m-%d %H:%M:%S'))
    elif pred_T[dict_k['t3'],dict_info['Pred_value']] >= pred_Td[dict_k['t3'],dict_info['IC_low']] and pred_T[dict_k['t3'],dict_info['Pred_value']] <= pred_Td[dict_k['t3'],dict_info['IC_up']]:
        if pred_Td[dict_k['t3'],dict_info['Pred_value']] > 0:
            print("ATTENZIONE! Allerta nebbia alle " + (dt.now() + datetime.timedelta(minutes=30)).strftime('%Y-%m-%d %H:%M:%S'))
        else:
            print("ATTENZIONE! Allerta brina alle " + (dt.now() + datetime.timedelta(minutes=30)).strftime('%Y-%m-%d %H:%M:%S'))
    final_old_time = acq_time[-1]
    index_train += 1
    index_test += 1
    print("\nStart training: " + acq_time[1].strftime('%Y-%m-%d %H:%M:%S'))
    print("Stop training: " + acq_time[-1].strftime('%Y-%m-%d %H:%M:%S') + "\n")
    tm.sleep(20)