import time as tm
import datetime
from datetime import datetime as dt
import requests


URL = "http://localhost:8080/users/16/position"
lat = [45.66466793823242, 45.66966793823242, 45.67466793823242, 45.67966793823242]
lng = [9.809000190734862, 9.813000190734862, 9.819000190734862, 9.802000190734862]
headers = {'Content-type': 'application/json', 'Accept': 'text/plain', 'Authorization' : 'Basic bS52ZXJ6ZXJvbGk6bS52ZXJ6ZXJvbGk='}
i = 0

while True:
    data = {"lat" : lat[i], "lng" : lng[i]}
    try:
        r = requests.post(url = URL, json = data, headers = headers)
        print(r.text)
        print(r.status_code)
    except:
        print("Error Request")
    tm.sleep(10)
    i = i + 1
    if i > 3:
        i = 0
