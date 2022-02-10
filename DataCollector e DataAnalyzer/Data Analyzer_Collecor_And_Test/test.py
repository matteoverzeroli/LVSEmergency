import unittest

from datanalyzer.dataAnalyzerNew import algorithm
import mysql.connector
from datetime import datetime as dt
import csv
import os
import glob

config = {
    'host':'progettopacdb.mysql.database.azure.com',
    'user':'dsalvetti',
    'password':'Progettopac2021!',
    'database':'testalg'
}

def initialize_database() : 
    print("***Inizializing database for test")
    conn = mysql.connector.connect(**config)
    cursor = conn.cursor()

    cursor.execute("TRUNCATE TABLE aprsdata")
    cursor.execute("TRUNCATE TABLE area")
    cursor.execute("TRUNCATE TABLE alarm")
    
    #insert area for test
    cursor.execute("INSERT INTO area (idArea, areaName, lat, lng, nameAprsStation, istatCode) VALUES (%s, %s, %s, %s, %s, %s);",[1, "areatest1", 1.0, 1.0, "test1","111111"])
    cursor.execute("INSERT INTO area (idArea, areaName, lat, lng, nameAprsStation, istatCode) VALUES (%s, %s, %s, %s, %s, %s);",[2, "areatest2", 2.0, 2.0, "test2","222222"])
    cursor.execute("INSERT INTO area (idArea, areaName, lat, lng, nameAprsStation, istatCode) VALUES (%s, %s, %s, %s, %s, %s);",[3, "areatest3", 3.0, 3.0, "test3","333333"])
    cursor.execute("INSERT INTO area (idArea, areaName, lat, lng, nameAprsStation, istatCode) VALUES (%s, %s, %s, %s, %s, %s);",[4, "areatest4", 4.0, 4.0, "test4","444444"])
    cursor.execute("INSERT INTO area (idArea, areaName, lat, lng, nameAprsStation, istatCode) VALUES (%s, %s, %s, %s, %s, %s);",[5, "areatest5", 5.0, 5.0, "test5","555555"])
    cursor.execute("INSERT INTO area (idArea, areaName, lat, lng, nameAprsStation, istatCode) VALUES (%s, %s, %s, %s, %s, %s);",[6, "areatest6", 5.0, 5.0, "test6","666666"])

    #reading all csv file in main directory and insert data in db

    files = glob.glob( '**.csv' )
    for file in files:
        file = open(file)
        csvreader = csv.reader(file)
        header = next(csvreader)

        for row in csvreader:
            cursor.execute("INSERT INTO aprsdata (name, time, temperature, pressure, humidity) VALUES (%s, %s, %s, %s, %s);", row[0:5]);
        file.close()

    conn.commit()
    conn.close()
    cursor.close()

def get_fog_RED_and_bw_RED():
    conn = mysql.connector.connect(**config)
    cursor = conn.cursor()

    cursor.execute("SELECT type, color, idArea, description FROM alarm WHERE idArea = 1 ORDER BY type ASC")

    rows = cursor.fetchall()

    conn.close()
    cursor.close()

    return rows

def get_frost_RED_and_bw_NONE():
    conn = mysql.connector.connect(**config)
    cursor = conn.cursor()

    cursor.execute("SELECT type, color, idArea, description FROM alarm WHERE idArea = 2 ORDER BY type ASC")

    rows = cursor.fetchall()

    conn.close()
    cursor.close()

    return rows

def get_fog_NONE_and_bw_NONE():
    conn = mysql.connector.connect(**config)
    cursor = conn.cursor()

    cursor.execute("SELECT type, color, idArea, description FROM alarm WHERE idArea = 3 ORDER BY type ASC")

    rows = cursor.fetchall()

    conn.close()
    cursor.close()

    return rows

def get_fog_WHITE_and_bw_NONE():
    conn = mysql.connector.connect(**config)
    cursor = conn.cursor()

    cursor.execute("SELECT type, color, idArea, description FROM alarm WHERE idArea = 4 ORDER BY type ASC")

    rows = cursor.fetchall()

    conn.close()
    cursor.close()

    return rows

def get_fog_GREEN_and_bw_NONE():
    conn = mysql.connector.connect(**config)
    cursor = conn.cursor()

    cursor.execute("SELECT type, color, idArea, description FROM alarm WHERE idArea = 5 ORDER BY type ASC")

    rows = cursor.fetchall()

    conn.close()
    cursor.close()

    return rows


class TestAlgorithmn(unittest.TestCase):
    def test_1_db_initialization(self):
        try:
            initialize_database()
        except:
            self.fail("Exception in initializing db")

    def test_2_algorithm(self):
        try:
            algorithm('testalg', True)
        except:
            self.fail("Exception in running algorithm")

    def test_3_fog_RED_and_bw_RED(self):
        result = get_fog_RED_and_bw_RED()
        
        expected = [('BW', 'RED', 1, 'Maltempo in avvicinamento, delta = -7.0'), ('FOG', 'RED', 1, 'Rischio nebbia attuale')]

        self.assertEqual(result, expected)

    def test_4_frost_RED_and_bw_NONE(self):
        result = get_frost_RED_and_bw_NONE()
        
        expected = [('BW', 'NONE', 2, 'Pressione in diminuzione, delta = -2.0'), ('FROST', 'RED', 2, 'Rischio brina attuale')]

        self.assertEqual(result, expected)

    def test_5_fog_NONE_and_bw_NONE(self):
        result = get_fog_NONE_and_bw_NONE()
        
        expected = [('BW', 'NONE', 3, 'Pressione in diminuzione, delta = -2.0'), ('FOG', 'NONE', 3, 'Nessun rischio nè attuale nè previsto')]

        self.assertEqual(result, expected)

    def test_6_fog_WHITE_and_bw_NONE(self):
        result = get_fog_WHITE_and_bw_NONE()
        
        expected = [('BW', 'NONE', 4, 'Pressione in diminuzione, delta = -0.75'), ('FOG', 'WHITE', 4, 'Rischio nebbia tra 30 minuti')]

        self.assertEqual(result, expected)

    def test_7_fog_GREEN_and_bw_NONE(self):
        result = get_fog_GREEN_and_bw_NONE()
        
        expected = [('BW', 'NONE', 5, 'Pressione in diminuzione, delta = -0.75'), ('FOG', 'GREEN', 5, 'Rischio nebbia tra 20 minuti')]

        self.assertEqual(result, expected)

if __name__ == '__main__':
    unittest.main()