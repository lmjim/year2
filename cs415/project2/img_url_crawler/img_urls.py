import requests
from bs4 import BeautifulSoup
from sys import argv

search = "%20".join(argv[1:])
soup = BeautifulSoup(requests.get('https://www.pexels.com/search/{}/'.format(search)).content, features="lxml")

for img in soup.find_all("img", src=True,):
    if "photos" in img["src"]:
        print(img["src"])
        try:
            print(img["alt"])
        except:
            print("{}".format(" ".join(search)))
        print("")