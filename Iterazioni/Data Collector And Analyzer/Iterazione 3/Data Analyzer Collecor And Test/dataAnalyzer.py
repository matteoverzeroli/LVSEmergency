import numpy as np
import pandas as pd
import pmdarima as pm
import mysql.connector
import datetime
import time as tm
from datetime import datetime as dt
from threading import Thread as th

class BadWeatherAlertsCreator(th):
    def __init__(self, station_code, areaID, conn2, cursor2, index, old_final_time_list, old_delta_list):
        th.__init__(self)
        self.station_code = station_code
        self.areaID = areaID
        self.conn2 = conn2
        self.cursor2 = cursor2
        self.index = index
        self.old_final_time_list = old_final_time_list
        self.old_delta_list = old_delta_list
        self.recent_time = dt.strptime("2021-04-06 15:00:00", '%Y-%m-%d %H:%M:%S')
    
    def run(self):
        # access to date and time of last acquisition 
        self.cursor2.execute("SELECT max(time) FROM aprsdata WHERE name = %(code)s;", {'code':self.station_code})
        temporary = self.cursor2.fetchall()
        self.recent_time = list(temporary[0])[0]
        
        # interruption of current thread if should be already analyzed the time series 
        # with the last  acquisition in DB
        if self.old_final_time_list[self.index] is not None:
            if self.recent_time == self.old_final_time_list[self.index]:
                print("No new row")
                self.conn2.close()
                self.cursor2.close()
                exit(0)
        
        # analysis and processing of atmospheric pressure time series regarding last 24 hours
        pressure_DS = pd.DataFrame(columns=['time','pressure'])
        self.cursor2.execute("SELECT time, pressure FROM aprsdata WHERE\
                             time >= date_sub('2022/01/30', INTERVAL 1 DAY) and name = %(code)s", {'code':self.station_code})
        info = self.cursor2.fetchall()

        if len(info) == 0:
            print("No data within 24h: pressure " + "of " + self.station_code + "\n")
            exit(0)

        for i in range(len(info)):
            pressure_DS.loc[i] = list(info[i])

        min_3h = self.recent_time - datetime.timedelta(hours=3)
        y_24h = list(pressure_DS['pressure'])

        p_mean = sum(y_24h)/len(y_24h)

        for i in list(pressure_DS.index):
            pressure_DS.at[i,'pressure'] = pressure_DS.at[i,'pressure'] - p_mean

        pressure_DS = pressure_DS[pressure_DS.time > min_3h]
        y_3h = list(pressure_DS['pressure'])
        p_low = (y_3h[1] + y_3h[2])/2
        p_up = (y_3h[-2] + y_3h[-3])/2
        delta = p_up - p_low
        
        # bad weather alerts creation
        if(delta >= 0):
            self.__alertsCreator("C1", delta)
        elif delta > self.old_delta_list[self.index]:
            self.__alertsCreator("C2", delta)
        elif delta <= -5:
            self.__alertsCreator("C3", delta)
        else:
            self.__alertsCreator("C4", delta)
        
        # updating last delta and tf, commit, closing DB connection and thread ending 
        self.old_final_time_list[self.index] = self.recent_time
        self.old_delta_list[self.index] = delta
        self.conn2.commit()
        self.conn2.close()
        self.cursor2.close()
        
    def __alertsCreator(self, case, delta):
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
        

class FogFrostAlertsCreator (th):
    def __init__(self, station_code, areaID, conn1, cursor1, index, old_final_time_list):
        th.__init__(self)
        self.station_code = station_code
        self.areaID = areaID
        self.conn1 = conn1
        self.cursor1 = cursor1
        self.index = index
        self.old_final_time_list = old_final_time_list
        self.recent_time = dt.strptime("2021-04-06 15:00:00", '%Y-%m-%d %H:%M:%S')
    
    def run(self):
        # access to date and time of last acquisition
        self.cursor1.execute("SELECT max(time) FROM aprsdata WHERE name = %(code)s;", {'code':self.station_code})
        temporary = self.cursor1.fetchall()
        self.recent_time = list(temporary[0])[0]
        
        # interruption of current thread if should be already analyzed the time series 
        # with the last  acquisition in DB
        if self.old_final_time_list[self.index] is not None:
            if self.recent_time == self.old_final_time_list[self.index]:
                print("No new row")
                self.conn1.close()
                self.cursor1.close()
                exit(0)
        
        # creation of tables for meteorological parameters and forcasters starting
        summaryT = pd.DataFrame(index=["tf","t1","t2","t3"], columns=["I_low", "value", "I_up"])
        summaryUR = pd.DataFrame(index=["tf","t1","t2","t3"], columns=["I_low", "value", "I_up"])
        summaryTd = pd.DataFrame(index=["tf","t1","t2","t3"], columns=["I_low", "value", "I_up"])
        self.__tempURForecaster("temperature", summaryT)
        self.__tempURForecaster("humidity", summaryUR)
        
        # determination of dew point's values and rispective acceptance ranges
        for i in list(summaryTd.index):
            summaryTd.at[i,'value'] = self.__computeTd(summaryT.at[i,'value'], summaryUR.at[i,'value'])
            summaryTd.at[i,'I_low'] = summaryTd.at[i,'value']
            summaryTd.at[i,'I_up'] = summaryTd.at[i,'value'] + 0.45

        # debugging
        print(self.station_code)
        print(self.recent_time.strftime('%Y-%m-%d %H:%M:%S'))
        print(summaryT)
        print(summaryUR)
        print(summaryTd) 
        
        # fog and frost alerts creation
        if summaryT.at['tf','value'] >= summaryTd.at['tf','I_low'] and summaryT.at['tf','value'] <= summaryTd.at['tf','I_up']:
           if summaryT.at['tf','value'] > 0:
               self.__alertsCreator("tf", "FOG")
               self.__debug("tf", "FOG", summaryT, summaryTd)
           else:
               self.__alertsCreator("tf", "FROST")
               self.__debug("tf", "FROST", summaryT, summaryTd)
        elif summaryT.at['t1','value'] >= summaryTd.at['t1','I_low'] and summaryT.at['t1','value'] <= summaryTd.at['t1','I_up']:
           if summaryT.at['t1','value'] > 0:
               self.__alertsCreator("t1", "FOG")
               self.__debug("t1", "FOG", summaryT, summaryTd)
           else:
               self.__alertsCreator("t1", "FROST")
               self.__debug("t1", "FROST", summaryT, summaryTd)
        elif summaryT.at['t2','value'] >= summaryTd.at['t2','I_low'] and summaryT.at['t2','value'] <= summaryTd.at['t2','I_up']:
           if summaryT.at['t2','value'] > 0:
               self.__alertsCreator("t2", "FOG")
               self.__debug("t2", "FOG", summaryT, summaryTd)
           else:
               self.__alertsCreator("t2", "FROST")
               self.__debug("t2", "FROST", summaryT, summaryTd)
        elif summaryT.at['t3','value'] >= summaryTd.at['t3','I_low'] and summaryT.at['t3','value'] <= summaryTd.at['t3','I_up']:
           if summaryT.at['t3','value'] > 0:
               self.__alertsCreator("t3", "FOG")
               self.__debug("t3", "FOG", summaryT, summaryTd)
           else:
               self.__alertsCreator("t3", "FROST")
               self.__debug("t3", "FROST", summaryT, summaryTd)
        else:
            self.__alertsCreator()
            self.__debug("tf", "NONE", summaryT, summaryTd)
        
        # updating last tf, commit, closing DB connection and thread ending
        self.old_final_time_list[self.index] = self.recent_time
        self.conn1.commit()
        self.conn1.close()
        self.cursor1.close()
        
    def __tempURForecaster(self, parameter, dataToUpdate):
        # analysis and processing of temperature or relative umidity's time series regarding
        # last 24 hours for predictive purpose
        if parameter == "temperature":
            self.cursor1.execute("SELECT time, temperature FROM aprsdata WHERE\
                                 time >= date_sub(now(), INTERVAL 1 DAY)\
                                     and name = %(station)s;", {'station':self.station_code})
            """
            For tests use this code:

                self.cursor1.execute("SELECT time, temperature FROM aprsdata WHERE\
                                    time >= date_sub('2022/01/30', INTERVAL 1 DAY)\
                                        and name = %(station)s;", {'station':self.station_code})
            """  
        else:
            self.cursor1.execute("SELECT time, humidity FROM aprsdata WHERE\
                                 time >= date_sub(now(), INTERVAL 1 DAY)\
                                     and name = %(station)s;", {'station':self.station_code})
            """
            For tests use this code:

                self.cursor1.execute("SELECT time, humidity FROM aprsdata WHERE\
                                    time >= date_sub('2022/01/30', INTERVAL 1 DAY)\
                                        and name = %(station)s;", {'station':self.station_code})
            """  
        info = self.cursor1.fetchall()

        if len(info) == 0:
            print("No data within 24h: " + parameter + " of " + self.station_code + "\n")
            exit(0)

        parameter_DS = pd.DataFrame(columns=["time", parameter])
        for i in range(len(info)):
            parameter_DS.loc[i] = list(info[i])
        y = parameter_DS[parameter]

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
        
        # updating tables
        dataToUpdate.at['tf', 'value'] = parameter_DS.iat[len(parameter_DS)-1,1]
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
    
    def __alertsCreator(self, t=None, typology=None):
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
        if typology != "NONE":
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
            print("-Air temperature: " + str(summaryT.at[t, "value"]) + "°C")
            print("-Dew point interval: [" + str(round(summaryTd.at[t, "I_low"], 2)) + "°C; " + str(round(summaryTd.at[t, "I_up"], 2)) + "°C]")
            print("***")
            print(" ")
        else:
            print(" ")
            print("***")
            print("No fog or frost risk")
            print("-ID area: " + str(self.areaID))
            print("-Recent time: " + dt.now().strftime('%Y-%m-%d %H:%M:%S'))
            print("-Final time: " + self.recent_time.strftime('%Y-%m-%d %H:%M:%S'))
            print("-Delta: now")
            print("-Air temperature: " + str(summaryT.at[t, "value"]) + "°C")
            print("-Dew point interval: [" + str(round(summaryTd.at[t, "I_low"], 2)) + "°C; " + str(round(summaryTd.at[t, "I_up"], 2)) + "°C]")
            print("***")
            print(" ")
        
def algorithm(database, isTest):
    
    # parameters' definition to establish DB connection
    config = {
      'host':'progettopacdb.mysql.database.azure.com',
      'user':'dsalvetti',
      'password':'Progettopac2021!',
      'database':database
    }
    
    # initialization of supporting variables for thread's execution 
    n_areas = 100
    old_final_time_list = [None]*n_areas
    old_delta_list = [0]*n_areas
    
    while True:
        # opening DB connection and automatic reconnection system's definition 
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
                
        # access to zones data 
        cursor.execute("SELECT * FROM area;")
        rows = cursor.fetchall()
        area_DS = pd.DataFrame(columns=["idArea","areaName","lat","lng","nameAprStation","istatCode"])
        num_areas = len(rows)
        for i in range(num_areas):
            area_DS.loc[i] = list(rows[i])
            
        # creation of threads for fog, frost and bad weather alerts creation, one for every zone
        fogFrostAlertsCreators = []
        badWeatherAlertsCreators = []
        for i in range(num_areas):
            if area_DS.at[i, "nameAprStation"] is not None:
                conn1 = mysql.connector.connect(**config)
                cursor1 = conn1.cursor()
                conn2 = mysql.connector.connect(**config)
                cursor2 = conn2.cursor()
                t = FogFrostAlertsCreator(area_DS.at[i, "nameAprStation"], area_DS.at[i, "idArea"], conn1, cursor1, i, old_final_time_list)
                w = BadWeatherAlertsCreator(area_DS.at[i, "nameAprStation"], area_DS.at[i, "idArea"], conn2, cursor2, i, old_final_time_list, old_delta_list)
                fogFrostAlertsCreators.append(t)
                badWeatherAlertsCreators.append(w)
        
        # starting threads         
        for i in fogFrostAlertsCreators:
            i.start()
        for i in badWeatherAlertsCreators:
            i.start()
            
        # join threads
        for i in fogFrostAlertsCreators:
            i.join()
        for i in badWeatherAlertsCreators:
            i.join()
            
        # closing DB connection
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