# coding: cp1251 -*-


import requests
from lxml import html
import os
import urlparse

started_url = raw_input('Введите ссылку для парсинга(без http://): ')
started_url = 'http://' + started_url + '/'
path = 'C:/Users/asus1/Desktop/downloaded_images/'
if not os.path.exists(path):
    os.mkdir(path)
response  = requests.get(started_url)
list_extension = ['jpg', 'png', 'gif', 'bmp']
contents = response.content
parsed_body = html.fromstring(response.text)
images = parsed_body.xpath('//img/@src')
if not images:
    print "Картинок не найдено"
else:
    images = [urlparse.urljoin(response.url, started_url) for started_url in images]
    print 'Найдено {0} картинок(-ки)' .format(len(images))
    for started_url in images:
        lst_images =  started_url.split('.') #последний элемент списка - расширение
        name = lst_images[-2].split('/')
        name = name[-1]
        for i in '/:*?"<>|':
            name = name.replace(i, '')   
        count = 0
        num = 0
        while num < len(list_extension):
            if list_extension[num] == lst_images[-1]:
                count = 1
                num = len(list_extension) - 1
            num += 1
        if count == 1:
            print "Загружаем изображение", name + '.' + lst_images[-1]
            image = requests.get(started_url)
            downloaded_file = open(path + name + '.' + lst_images[-1] , 'wb')
            downloaded_file.write(image.content)
            downloaded_file.close()
        else:
            print "Не удалось скачать картинку"
