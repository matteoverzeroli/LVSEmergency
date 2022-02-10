import numpy as np
import pandas as pd
import pmdarima as pm
import mysql.connector
import datetime
import time as tm
from datetime import datetime as dt
from threading import Thread as th

class BadWeatherAllertsCreator(th):
    def __init__(self, station_code, areaID, conn2, cursor2, index, final_old_time_list, old_delta_list):
        th.__init__(self)
        self.station_code = station_code
        self.areaID = areaID
        self.conn2 = conn2
        self.cursor2 = cursor2
        self.index = index
        self.final_old_time_list = final_old_time_list
        self.old_final_time = final_old_time_list[self.index]
        self.old_delta_list = old_delta_list

        self.recent_time = dt.strptime("2021-04-06 15:00:00", '%Y-%m-%d %H:%M:%S')
        self.old_delta = old_delta_list[self.index]
    
    def run(self):
        # accesso al DB per ottenere la data dell'ultima acquisizione 
        self.cursor2.execute("SELECT max(time) FROM aprsdata WHERE name = %(code)s;", {'code':self.station_code})
        temporary = self.cursor2.fetchall()
        self.recent_time = list(temporary[0])[0]
        
        # interruzione del thread se dovesse essere già stata elaborata la serie storica 
        # contenente l'ultima acquisizione nel DB
        if self.recent_time == self.old_final_time:
            print("No new row")
            self.conn2.close()
            self.cursor2.close()
            return
        
        # analisi ed elaborazione delle serie storica relativa alla pressione atmosferica delle ultime 24 ore
        pressure_DB = pd.DataFrame(columns=['time','pressure'])
        self.cursor2.execute("SELECT time, pressure FROM aprsdata WHERE name = %(code)s", {'code':self.station_code})
        info = self.cursor2.fetchall()
        for i in range(len(info)):
            pressure_DB.loc[i] = list(info[i])
        min_24h = self.recent_time - datetime.timedelta(hours=24)
        min_3h = self.recent_time - datetime.timedelta(hours=3)
        pressure_DB = pressure_DB[pressure_DB.time > min_24h]
        y_24h = list(pressure_DB['pressure'])
        p_mean = sum(y_24h)/len(y_24h)
        for i in list(pressure_DB.index):
            pressure_DB.at[i,'pressure'] = pressure_DB.at[i,'pressure'] - p_mean
        pressure_DB = pressure_DB[pressure_DB.time > min_3h]
        y_3h = list(pressure_DB['pressure'])
        p_low = (y_3h[1] + y_3h[2])/2
        p_up = (y_3h[-2] + y_3h[-3])/2
        delta = p_up - p_low
        
        # generazione delle allerte relative al maltempo
        if(delta >= 0):
            self.__allertsCreator("C1", delta)
        elif delta > self.old_delta:
            self.__allertsCreator("C2", delta)
        elif delta <= -5:
            self.__allertsCreator("C3", delta)
        else:
            self.__allertsCreator("C4", delta)
            
        # aggiornamenti degli ultimi delta e tf, commit, chiusura della connessione e terminazione del thread
        self.final_old_time_list[self.index] = self.recent_time
        self.old_delta_list[self.index] = delta
        self.conn2.commit()
        self.conn2.close()
        self.cursor2.close()
        
    def __allertsCreator(self, case, delta):
        if case == "C1":
            coulor = "NONE"
            description = "Pressione in aumento, delta = " + str(round(delta,2))
        elif case == "C2":
            coulor = "NONE"
            description = "Maltempo in allontanamento/picco negativo superato, delta = " + str(round(delta,2))
        elif case == "C3":
            coulor = "RED"
            description = "Maltempo in avvicinamento, delta = " + str(round(delta,2))
        elif case == "C4":
            coulor = "NONE"
            description = "Pressione in diminuzione, delta = " + str(round(delta,2))
        self.cursor2.execute("INSERT INTO alarm (time, type, color, idArea, description) VALUES (%s, %s, %s, %s, %s);",\
                              (dt.now().strftime('%Y-%m-%d %H:%M:%S'), "BW", coulor, int(self.areaID), description))
        

class FogFrostAllertsCreator (th):
    def __init__(self, station_code, areaID, conn1, cursor1, index, final_old_time_list, old_delta_list):
        th.__init__(self)
        self.station_code = station_code
        self.areaID = areaID
        self.conn1 = conn1
        self.cursor1 = cursor1
        self.index = index
        self.final_old_time_list = final_old_time_list
        self.old_delta_list = old_delta_list
        self.old_final_time = final_old_time_list[self.index]
        self.recent_time = dt.strptime("2021-04-06 15:00:00", '%Y-%m-%d %H:%M:%S')
    
    def run(self):
        # accesso al DB per ottenere la data dell'ultima acquisizione
        self.cursor1.execute("SELECT max(time) FROM aprsdata WHERE name = %(code)s;", {'code':self.station_code})
        temporary = self.cursor1.fetchall()
        self.recent_time = list(temporary[0])[0]
        
        # interruzione del thread se dovesse essere già stata elaborata la serie storica 
        # contenente l'ultima acquisizione nel DB
        if self.recent_time == self.old_final_time:
            print("No new row")
            self.conn1.close()
            self.cursor1.close()
            return
        
        # creazione dei dataframe per i parametri meteorologici e avvio dei predittori
        summaryT = pd.DataFrame(index=["tf","t1","t2","t3"], columns=["I_low", "value", "I_up"])
        summaryUR = pd.DataFrame(index=["tf","t1","t2","t3"], columns=["I_low", "value", "I_up"])
        summaryTd = pd.DataFrame(index=["tf","t1","t2","t3"], columns=["I_low", "value", "I_up"])
        self.__tempURForcaster("temperature", summaryT)
        self.__tempURForcaster("humidity", summaryUR)
        
        # determinazione dei valori della temperatura di rugiada e rispettivi intervalli di accettazione
        for j in list(summaryTd.columns):
            for i in list(summaryTd.index):
                summaryTd.at[i,j] = self.__computeTd(summaryT.at[i,j], summaryUR.at[i,j])
        for i in list(summaryTd.index):
            summaryTd.at[i,'I_low'] = summaryTd.at[i,'value']
        for i in list(summaryTd.index):
            summaryTd.at[i,'I_up'] = summaryTd.at[i,'value'] + 0.45
        
        # debugging
        print(self.station_code)
        print(self.recent_time.strftime('%Y-%m-%d %H:%M:%S'))
        print(summaryT)
        print(summaryUR)
        print(summaryTd) 
        
        # generazione delle allerte relative alle formazioni di nebbia e brina
        if summaryT.at['tf','value'] >= summaryTd.at['tf','I_low'] and summaryT.at['tf','value'] <= summaryTd.at['tf','I_up']:
           if summaryT.at['tf','value'] > 0:
               self.__allertsCreator("tf", "FOG")
               self.__debug("tf", "FOG", summaryT, summaryTd)
           else:
               self.__allertsCreator("tf", "FROST")
               self.__debug("tf", "FROST", summaryT, summaryTd)
        elif summaryT.at['t1','value'] >= summaryTd.at['t1','I_low'] and summaryT.at['t1','value'] <= summaryTd.at['t1','I_up']:
           if summaryT.at['t1','value'] > 0:
               self.__allertsCreator("t1", "FOG")
               self.__debug("t1", "FOG", summaryT, summaryTd)
           else:
               self.__allertsCreator("t1", "FROST")
               self.__debug("t1", "FROST", summaryT, summaryTd)
        elif summaryT.at['t2','value'] >= summaryTd.at['t2','I_low'] and summaryT.at['t2','value'] <= summaryTd.at['t2','I_up']:
           if summaryT.at['t2','value'] > 0:
               self.__allertsCreator("t2", "FOG")
               self.__debug("t2", "FOG", summaryT, summaryTd)
           else:
               self.__allertsCreator("t2", "FROST")
               self.__debug("t2", "FROST", summaryT, summaryTd)
        elif summaryT.at['t3','value'] >= summaryTd.at['t3','I_low'] and summaryT.at['t3','value'] <= summaryTd.at['t3','I_up']:
           if summaryT.at['t3','value'] > 0:
               self.__allertsCreator("t3", "FOG")
               self.__debug("t3", "FOG", summaryT, summaryTd)
           else:
               self.__allertsCreator("t3", "FROST")
               self.__debug("t3", "FROST", summaryT, summaryTd)
        else:
            self.__allertsCreator()
        
        # aggiornamenti dell'ultimo tf, commit, chiusura della connessione e terminazione del thread
        self.final_old_time_list[self.index] = self.recent_time
        self.conn1.commit()
        self.conn1.close()
        self.cursor1.close()
        
    def __tempURForcaster(self, parameter, dataToUpdate):
        # analisi ed elaborazione delle serie storica del parametro temperatura o umidità relativa 
        # delle ultime 3 ore a scopo predittivo
        if parameter == "temperature":
            self.cursor1.execute("SELECT time, temperature FROM aprsdata WHERE name = \
                       %(station)s;", {'station':self.station_code})
        else:
            self.cursor1.execute("SELECT time, humidity FROM aprsdata WHERE \
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
        
        # aggiornamento dei dataframe
        dataToUpdate.at['tf', 'value'] = thread_DB.iat[len(thread_DB)-1,1]
        dataToUpdate.at['t1', 'value'] = fc[0]
        dataToUpdate.at['t2', 'value'] = fc[1]
        dataToUpdate.at['t3', 'value'] = fc[2]
        dataToUpdate.at['tf', 'I_low'] = dataToUpdate.at['tf', 'value']
        dataToUpdate.at['t1', 'I_low'] = confint[0,0]
        dataToUpdate.at['t2', 'I_low'] = confint[1,0]
        dataToUpdate.at['t3', 'I_low'] = confint[2,0]
        dataToUpdate.at['tf', 'I_up'] = dataToUpdate.at['tf', 'value']
        dataToUpdate.at['t1', 'I_up'] = confint[0,1]
        dataToUpdate.at['t2', 'I_up'] = confint[1,1]
        dataToUpdate.at['t3', 'I_up'] = confint[2,1]
        
    def __computeTd(self, T, UR):
        a = 17.27
        b = 237.7
        alpha = self.__computeAlpha(T,UR)
        return (b*alpha)/(a-alpha)
                
    def __computeAlpha(self, T,UR):
        a = 17.27
        b = 237.7
        return ((a*T)/(b+T)) + np.log(UR/100)
    
    def __allertsCreator(self, t=None, typology=None):
        if t is not None:
            if t == "tf":
                coulor = "RED"
                delta = "attuale"
            elif t == "t1":
                coulor = "ORANGE"
                delta = "tra 10 minuti"
            elif t == "t2":
                coulor = "GREEN"
                delta = "tra 20 minuti"
            elif t == "t3":
                coulor = "WHITE"
                delta = "tra 30 minuti"
            if typology == "FROST":
                trad = "brina"
            elif typology == "FOG":
                trad = "nebbia"
            description = "Rischio " + trad + " " + delta
            self.cursor1.execute("INSERT INTO alarm (time, type, color, idArea, description) VALUES (%s, %s, %s, %s, %s);",\
                              (dt.now().strftime('%Y-%m-%d %H:%M:%S'), typology, coulor, int(self.areaID), description))
        else:
            description = "Nessun rischio nè attuale nè previsto"
            typology = "FOG"
            self.cursor1.execute("INSERT INTO alarm (time, type, color, idArea, description) VALUES (%s, %s, %s, %s, %s);",\
                              (dt.now().strftime('%Y-%m-%d %H:%M:%S'), typology, "NONE", int(self.areaID), description))
                
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
        
def algorithm(database, isTest):
     # definizione dei parametri per aprire la connessione con il DB
    config = {
      'host':'progettopacdb.mysql.database.azure.com',
      'user':'dsalvetti',
      'password':'Progettopac2021!',
      'database':database
    }

    # inizializzazione delle variabili di supporto all'esecuzione dei thread

    n_area_max = 100 #maximum number of areas

    final_old_time_list = [None]*n_area_max
    old_delta_list = [0]*n_area_max
    
    while True:
        # apertura della connessione con il DB e definizione del sistema di riconnessione automatico
        connected = False
        while connected == False:
            try:
                conn = mysql.connector.connect(**config)
                print("***")
                print("Connection established")
                cursor = conn.cursor()
                connected = True
            except mysql.connector.Error as e:
                print("An error is occured at " + dt.now().strftime('%Y-%m-%d %H:%M:%S'))
                print("--> Retrying between 10 seconds")
                print(" ")
                print(e)
                tm.sleep(15)

        # accesso ai dati relativi alle zone
        cursor.execute("SELECT * FROM area;")
        rows = cursor.fetchall()
        area_DB = pd.DataFrame(columns=["idArea","areaName","lat","lng","nameAprStation","istatCode"])
        for i in range(len(rows)):
            area_DB.loc[i] = list(rows[i])
   
        # creazione dei thread per la generazione delle allerte nebbia, brina e maltempo, uno per ogni zona
        fogFrostAllertsCreators = []
        badWeatherAllertsCreators = []

        for i in range(len(rows)):
            if area_DB.at[i, "nameAprStation"] is not None:
                conn1 = mysql.connector.connect(**config)
                cursor1 = conn1.cursor()
                conn2 = mysql.connector.connect(**config)
                cursor2 = conn2.cursor()
                t = FogFrostAllertsCreator(area_DB.at[i, "nameAprStation"], area_DB.at[i, "idArea"], conn1, cursor1, i, final_old_time_list, old_delta_list)
                w = BadWeatherAllertsCreator(area_DB.at[i, "nameAprStation"], area_DB.at[i, "idArea"], conn2, cursor2, i, final_old_time_list, old_delta_list)
                fogFrostAllertsCreators.append(t)
                badWeatherAllertsCreators.append(w)
    
        # avvio dei thread         
        for i in fogFrostAllertsCreators:
            i.start()
        for i in badWeatherAllertsCreators:
            i.start()
    
        # join dei thread precedentemete avviati
        for i in fogFrostAllertsCreators:
            i.join()
        for i in badWeatherAllertsCreators:
            i.join()
    
        # chiusura della connessione con il DB
        cursor.close()
        conn.close()
        print("Done.")
        print("***")
        print(" ")

        if isTest:
            break

        tm.sleep(60*5)

if __name__ == '__main__':
    algorithm("test", False)