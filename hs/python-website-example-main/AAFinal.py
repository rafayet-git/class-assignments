#!/usr/bin/python

import urllib.request
from zipfile import ZipFile
import os
import ast
import matplotlib.pyplot as plt

def sortlistp1():
    with open('wikipedia-iso-country-codes.csv','r') as file:
        a = file.read()
    a = a.strip(' ').split('\n')
    i = 0
    y = 0
    while i < len(a):
        a[i] = a[i].strip(' ').split(',')
        while y < len(a[i]):
            a[i][y] = a[i][y].strip(' ')
            y += 1
        i += 1
    a.pop(0)
    random.shuffle(a)
    a = a[:25]
    return(a)
        
# t = sortlistp1()
t = [['South Africa', 'ZA', 'ZAF', '710', 'ISO 3166-2:ZA'], ['India', 'IN', 'IND', '356', 'ISO 3166-2:IN'], ['United Kingdom', 'GB', 'GBR', '826', 'ISO 3166-2:GB'], ['Luxembourg', 'LU', 'LUX', '442', 'ISO 3166-2:LU'], ['Slovenia', 'SI', 'SVN', '705', 'ISO 3166-2:SI'], ['Kenya', 'KE', 'KEN', '404', 'ISO 3166-2:KE'], ['Moldova', 'MD', 'MDA', '498', 'ISO 3166-2:MD'], ['Ukraine', 'UA', 'UKR', '804', 'ISO 3166-2:UA'], ['Malaysia', 'MY', 'MYS', '458', 'ISO 3166-2:MY'], ['Belize', 'BZ', 'BLZ', '84', 'ISO 3166-2:BZ'], ['North Korea', 'KP', 'PRK', '408', 'ISO 3166-2:KP'], ['Peru', 'PE', 'PER', '604', 'ISO 3166-2:PE'], ['Andorra', 'AD', 'AND', '20', 'ISO 3166-2:AD'], ['Sudan', 'SD', 'SDN', '736', 'ISO 3166-2:SD'], ['Germany', 'DE', 'DEU', '276', 'ISO 3166-2:DE'], ['Aruba', 'AW', 'ABW', '533', 'ISO 3166-2:AW'], ['Turkey', 'TR', 'TUR', '792', 'ISO 3166-2:TR'], ['Chad', 'TD', 'TCD', '148', 'ISO 3166-2:TD'], ['Azerbaijan', 'AZ', 'AZE', '31', 'ISO 3166-2:AZ'], ['Tunisia', 'TN', 'TUN', '788', 'ISO 3166-2:TN'], ['Samoa', 'WS', 'WSM', '882', 'ISO 3166-2:WS'], ['Guatemala', 'GT', 'GTM', '320', 'ISO 3166-2:GT'], ['Senegal', 'SN', 'SEN', '686', 'ISO 3166-2:SN'], ['Singapore', 'SG', 'SGP', '702', 'ISO 3166-2:SG'], ['Belgium', 'BE', 'BEL', '56', 'ISO 3166-2:BE']]

def sortlistp2(index):
    y = 0
    temp = []
    while y < len(t):
        temp.append(t[y][index])
        y += 1
    return temp

name = sortlistp2(0)
two = sortlistp2(1)
three = sortlistp2(2)

def file():
    y = 0
    while y < len(three):
        urllib.request.urlretrieve("https://api.worldbank.org/v2/en/country/" + three[y] + "?downloadformat=csv", name[y] + ".zip")
        y += 1
        
def extractFile():
    y = 0
    while y < len(name):
        files = []
        with ZipFile(name[y] + '.zip', 'r') as zipped:
            files = zipped.namelist()
            zipped.extract(files[1])
        os.rename(files[1], name[y] + '.csv')
        y += 1
        
# file()
# extractFile()

Listofdata = ['Population, total', 'GDP (current US$)', 'CO2 emissions (metric tons per capita)', 'Rural population', 'Life expectancy at birth, total (years)', 'Land area (sq. km)', 'Mobile cellular subscriptions']
years = ['1960', '1961', '1962', '1963', '1964', '1965', '1966', '1967', '1968', '1969', '1970', '1971', '1972', '1973', '1974', '1975', '1976', '1977', '1978', '1979', '1980', '1981', '1982', '1983', '1984', '1985', '1986', '1987', '1988', '1989', '1990', '1991', '1992', '1993', '1994', '1995', '1996', '1997', '1998', '1999', '2000', '2001', '2002', '2003', '2004', '2005', '2006', '2007', '2008', '2009', '2010', '2011', '2012', '2013', '2014', '2015', '2016', '2017', '2018', '2019', '2020']

def makedir():
    y = 0
    while y < len(name):
        os.mkdir('Graphs/' + name[y])
        y += 1
        
# makedir()
        
def test(name):
    z = 0
    t = 0
    file = open(name + '.csv')
    lists = []
    for y in file:
        x = y.rstrip().split('\t')
        lists.append(x)
    lists = lists[4:]
    ee = []
    while t < len(lists):
        lists[t][0] = lists[t][0][:-1]
        ee.append(ast.literal_eval(lists[t][0]))
        t += 1
    t = 0
    final = []
    while t < len(ee):
        if ee[t][2] in Listofdata:
            final.append(ee[t])
        t += 1
    z += 1
    return final
    
def donde(name, data):
    y = 0
    z = test(name)
    e = []
    while y < len(z):
        if z[y][2] == data:
            e.append(z[y])
        y += 1
    e[0] = e[0][4:]
    e = list(e[0])
    y = 0
    while y < len(e):
        if e[y] == '':
            e[y] = '0'
        e[y] = float(e[y])
        y += 1
    y = 1
    while y < len(e):
        if e[y] == 0  and e[y-1] != 0:
            e[y] = e[y-1]
        y += 1
    return e
        
def plots():
    y = 0
    z = 0
    while y < len(name):
        z = 0
        while z < len(Listofdata):
            plt.figure(figsize=(12, 7))
            plt.plot(years, donde(name[y], Listofdata[z]), 'ro--')
            plt.xlabel('Years')
            plt.ylabel(Listofdata[z])
            plt.title(Listofdata[z] + ' for ' + name[y])
            plt.xticks(rotation = 80)
            plt.tight_layout(pad=1)
            plt.savefig('Graphs/' + name[y] + '/' + Listofdata[z] + '.png')
            plt.clf()
            plt.cla()
            plt.close()
            z += 1
        y += 1

# plots()

def countryhtml():
    ok = '''
<!DOCTYPE HTML>
<html>
    <head>
        <title>
            Country Data Graphs
        </title>
        <link rel="stylesheet" href="style.css">
    </head>
    <body>
        <h1>Country Data Graphs</h1>
        <nav>
            <ul>
                <li><a href="http://moe.stuy.edu/~rhossain30/finalProject/v14/home.html">Home</a></li>
                <li><a href="http://moe.stuy.edu/~rhossain30/finalProject/v14/country.html">Country List</a></li>
                <li><a href="http://moe.stuy.edu/~rhossain30/finalProject/v14/countryrandom.py">Random Country</a></li>
                <li><a href="http://moe.stuy.edu/~rhossain30/finalProject/v14/all.html">All Countries</a></li>
            </ul>
        </nav>
        <h2>Click on a country to see its graphs.</h2>
        <ol>
            _NAV_
        </ol>
    </body>
</html>
'''
    y = 0
    z = ''
    while y < len(name):
        z += '<li><a href="http://moe.stuy.edu/~rhossain30/finalProject/v14/HTMLWeb/' + name[y] + '.html">' + name[y] + '</a></li>\n\t'
        y += 1
    ok = ok.replace('_NAV_', z)
    with open('country.html', 'w') as web:
        web.write(ok)
        web.close()
        
#countryhtml()
        
def htmlweb():
    y = 0
    h = '<img src="http://moe.stuy.edu/~rhossain30/finalProject/v14/Graphs/'
    while y < len(name):
        ok = '''
<!DOCTYPE HTML>
<html>
    <head>
        <title>
            Country Data Graphs
        </title>
        <link rel="stylesheet" href="style.css">
    </head>
    <body>
        <h1>Country Data Graphs</h1>
        <nav>
            <ul>
                <li><a href="http://moe.stuy.edu/~rhossain30/finalProject/v14/home.html">Home</a></li>
                <li><a href="http://moe.stuy.edu/~rhossain30/finalProject/v14/country.html">Country List</a></li>
                <li><a href="http://moe.stuy.edu/~rhossain30/finalProject/v14/countryrandom.py">Random Country</a></li>
                <li><a href="http://moe.stuy.edu/~rhossain30/finalProject/v14/all.html">All Countries</a></li>
            </ul>
        </nav>
        _PNG_
    </body>
</html>
'''
        e = '<h3>Here is the data for the country ' + name[y] + '</h3>\n\t' + h + name[y] + '/CO2 emissions (metric tons per capita).png" alt="CO2 Emissions">\n\t' + h + name[y] + '/GDP (current US$).png" alt="GDP">\n\t' + h + name[y] + '/Land area (sq. km).png" alt="Land Area changes">\n\t' + h + name[y] + '/Life expectancy at birth, total (years).png" alt="Life expectancy">\n\t' + h + name[y] + '/Mobile cellular subscriptions.png" alt="Mobile subscriptions">\n\t' + h + name[y] + '/Population, total.png" alt="Population">\n\t' + h + name[y] + '/Rural population.png" alt="Population in rural areas">\n\t'
        ok = ok.replace('_PNG_', e)
        with open('HTMLWeb/'+name[y]+'.html', 'w') as yes:
            yes.write(ok)
            yes.close()
        y += 1

#htmlweb()

def allcountry():
    y = 0
    z = 0
    while y < len(Listofdata):
        z = 0
        plt.figure(figsize=(12, 7))
        while z < len(name):
            plt.plot(donde(name[z], Listofdata[y]), label=name[z])
            z += 1
        plt.xlabel('Years (since 1960)')
        plt.ylabel(Listofdata[y])
        plt.xticks(rotation = 80)
        plt.title(Listofdata[y] + ' in 25 countries')
        plt.tight_layout(pad=1)
        plt.legend()
        plt.savefig('Graphs/All/'+ Listofdata[y] + '.png')
        plt.clf()
        plt.cla()
        plt.close()
        y += 1

#allcountry()