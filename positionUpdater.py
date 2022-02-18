import time as tm
import datetime
from datetime import datetime as dt
import requests


URL = "http://localhost:8080/users/16/position"
latitude[4] = [45.66466793823242, 45.66966793823242, 45.67466793823242, 45.67966793823242]
longitude[4] = [9.809000190734862, 9.813000190734862, 9.819000190734862, 9.802000190734862]
headers = {'content-type': 'application/json',
    'Authorization': 'Basic YWRtaW46YWRtaW4='
}

i = 0
while (true):
    time = datetime.datetime.now()
    data = {"lat": latitude[i],
        "lng": longitude[i],
        "time": time.strftime('%Y-%m-%d %H:%M:%S'),
        "idUser": 16,
        "name": "Matteo",
        "surname": "Verzeroli"
    }

    r = requests.post(url = URL, data = data, headers = headers)
    tm.sleep(10)
    i = i + 1
    if i > 3:
        i = 0
