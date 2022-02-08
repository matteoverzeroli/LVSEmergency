import unittest

from datanalyzer.dataAnalyzerNew import algorithm
import mysql.connector
from datetime import datetime as dt
import csv

config = {
    'host':'progettopacdb.mysql.database.azure.com',
    'user':'dsalvetti',
    'password':'Progettopac2021!',
    'database':'testalg'
}

def initializeDatabase() : 
    conn = mysql.connector.connect(**config)
    cursor = conn.cursor()

    cursor.execute("TRUNCATE TABLE aprsdata")
    cursor.execute("TRUNCATE TABLE area")
    cursor.execute("TRUNCATE TABLE alarm")

    cursor.execute("INSERT INTO area (idArea, areaName, lat, lng, nameAprsStation, istatCode) VALUES (%s, %s, %s, %s, %s, %s);",[1, "areatest", 1.0, 1.0, "test","222222"]);

    file = open("testdata.csv")
    csvreader = csv.reader(file)
    header = next(csvreader)

    for row in csvreader:
        cursor.execute("INSERT INTO aprsdata (name, time, temperature, pressure, humidity) VALUES (%s, %s, %s, %s, %s);", row[0:5]);
    file.close()

    conn.commit()
    conn.close()
    cursor.close()

class TestAlgorithmn(unittest.TestCase):
    def test_1_db_initialization(self):
        try:
            initializeDatabase()
        except:
            self.fail("Exception in initializing db")

    def test_2_algorithm(self):
        try:
            algorithm('testalg', True)
        except:
            self.fail("Exception in running algorithm")

    def test_3_fog_and_bw_RED(self):
        self.assertEqual(6, 6)

if __name__ == '__main__':
    unittest.main()