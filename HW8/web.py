# CS288 Homework 8
# Read the skeleton code carefully and try to follow the structure
# You may modify the code but try to stay within the framework.

import sys
import os
import subprocess
import re
import sys
import mysql.connector

from xml.dom.minidom import parse, parseString

# convert to xhtml
# use: java -jar tagsoup-1.2.jar --files html_file
def html_to_xml(fn):
   html_to_xhtml = "java -jar tagsoup-1.2.1.jar --files " + fn
   os.system(html_to_xhtml)
   xhtml_file = fn.replace(".html",".xhtml")
   return xhtml_file

# get all text recursively to the bottom
def get_text(e):
   lst=[]
   if e.nodeType in (3,4): 
       lst.append(e.data)
   else: 
       for i in e.childNodes: 
           lst = lst + get_text(i)
   return lst

# insert values into dic format
def to_dict(stock): 
    dic = {}
    dic['symbol'] = stock[0]
    dic['name'] = stock[1].replace("'", '')
    dic['price'] = stock[2]
    dic['chng'] = stock[3]
    dic['pchng'] = stock[4].replace('%', '')
    dic['volume'] = re.sub('[^0-9,.]', '', stock[5])
    dic['avg'] = re.sub('[^0-9,.]', '', stock[6])
    dic['mcap'] = re.sub('[^0-9,.]', '', stock[6])
    return dic

# retrieve the values from file 
def extract_values(dm):
   lst = []
   l = dom.getElementsByTagName('tr')
   l = l[1:]
   for i in l: 
       lst.append( get_text(i) )

   d_lst=[]
   for stock in lst: 
        d_lst.append( to_dict(stock) ) 
   return d_lst

# select values from table 
def select_from_db(cursor, tbl): 
   db=mysql.connector.connect(
       host="localhost",
       user="cs288",
       passwd="cs288",
       database="stock"
   )
   cursor=db.cursor()
   cursor.execute('SELECT * FROM ' + tbl)
   stocks = cursor.fetchall()
   
   for stock in stocks: 
       print( stock )

# insert values to table 
def insert_to_db(l,tbl):
   db=mysql.connector.connect(
       host="localhost",
       user="cs288",
       passwd="cs288",
       database="stock"
   )
   cursor=db.cursor()
   query1='CREATE TABLE IF NOT EXISTS ' + tbl + '(symbol varchar(80), name varchar(80), price float, chng float, pchng float, volume float, avg float, mcap float);'
   cursor.execute( query1 )
   
   for stock in l: 
      columns = ', '.join("`" + str(x).replace('/', '_') + "`" for x in stock.keys() )
      values = ', '.join("'" + str(x).replace('/', '_') + "'" for x in stock.values() )
      query2 = "INSERT INTO %s ( %s ) VALUES ( %s );" % (tbl, columns, values)
      cursor.execute(query2)

   db.commit()
   return cursor 

def main():
   html_fn = sys.argv[1]
   fn = html_fn.replace('.html','')
   xhtml_fn = html_to_xml(html_fn)

   global dom
   dom = parse(xhtml_fn)

   lst = extract_values(dom)

   #make sure your mysql server is up and running
   cursor = insert_to_db(lst,fn) # fn = table name for mysql

   l = select_from_db(cursor,fn) # display the table on the screen

   # make sure the Apache web server is up and running
   # write a PHP script to display the table(s) on your browser
   result = subprocess.run(
       ['php','index.php'], 
   )
   return l

if __name__ == "__main__":
    main()