#!/usr/bin/python
print("Content-Type: text/html\n\n")

import random

name = ['South Africa', 'India', 'United Kingdom', 'Luxembourg', 'Slovenia', 'Kenya', 'Moldova', 'Ukraine', 'Malaysia', 'Belize', 'North Korea', 'Peru', 'Andorra', 'Sudan', 'Germany', 'Aruba', 'Turkey', 'Chad', 'Azerbaijan', 'Tunisia', 'Samoa', 'Guatemala', 'Senegal', 'Singapore', 'Belgium']

def htmlweb():
    y = 0
    no = random.choice(name)
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
        e = '<h3>Here is the data for the country ' + no + '</h3>\n\t' + h + no + '/CO2 emissions (metric tons per capita).png" alt="CO2 Emissions">\n\t' + h + no + '/GDP (current US$).png" alt="GDP">\n\t' + h + no + '/Land area (sq. km).png" alt="Land Area changes">\n\t' + h + no + '/Life expectancy at birth, total (years).png" alt="Life expectancy">\n\t' + h + no + '/Mobile cellular subscriptions.png" alt="Mobile subscriptions">\n\t' + h + no + '/Population, total.png" alt="Population">\n\t' + h + no + '/Rural population.png" alt="Population in rural areas">\n\t'
        ok = ok.replace('_PNG_', e)
        y += 1
    return ok

print(htmlweb())