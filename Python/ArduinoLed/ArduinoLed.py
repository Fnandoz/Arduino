import urllib
from time import sleep

params = ("ledon1" ,"ledoff1", "ledon2", "ledoff2")
while True:
    for i in range(4):
        url = "http://192.168.0.177/?%s" % params[i]
        f = urllib.urlopen(url)
        contents = f.read()
        f.close()
        sleep(1)

