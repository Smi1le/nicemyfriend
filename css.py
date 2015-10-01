import urllib
from urllib.request import urlopen
url="http://lenta.ru/"
html1=urlopen(url)
page=html1.read()
fh=open('text.txt','w')
fh.write(str(page))
fh.close()
