# Name: Lily Jim
# Date: 5/20/2019
# Assignment: Geog 491 Final Project
# Description: Map data from CDC

import arcpy # import ArcGIS functions
from arcpy import env # import env for ease of use
import datetime as dt # import access to time

# Import custom functions
from createDocuments import setUp
from modifyElements import *
from createChoropleth import changeDisplay

def main():
    # Call functions to produce wanted output of pdfs
    wrkspc = r"R:\Geog491_6\Student_Data\ljim\FinalProject" # define workspace path
    env.workspace = wrkspc # set GIS workspace
    env.overwriteOutput = True # allow files to be overrided
    
    years = [1999, 2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017] # define all the years of data
    #years = [2015] # this is for testing purposes
    #years = [2005, 2010, 2015] # this is for testing purposes
    blankDocument = wrkspc + "\\layout\\Layout.mxd" # path to "blank" document with necessary elements added
    
    # Import data and set up frames
    setUp(years, wrkspc, blankDocument)
    print "Done with data frame setup"
    
    # Add text elements
    configText(years, wrkspc)
    print "Done with text configuration"

    # Move scalebars and north arrows
    configScaleBar(years, wrkspc)
    print "Done with scale bar configuration"
    configNorthArrow(years, wrkspc)
    print "Done with north arrow configuration"

    # Change map display into choropleth
    changeDisplay(years, wrkspc)
    print "Done with display changes"

    # Move legend
    configLegend(years, wrkspc)
    print "Done with legend configuration"

    # Export to pdf
    for year in years:
        currentDataSet = "data" + str(year) # define currect data set
        document = wrkspc + "\\" + str(year) + "\\" + currentDataSet + ".mxd" # define map document path
        docPDF = wrkspc + "\\results\\" + currentDataSet + ".pdf" # define pdf path
        mxd = arcpy.mapping.MapDocument(document) # open map document
        arcpy.mapping.ExportToPDF(mxd, docPDF) # export map document to pdf
    print "Done exporting to PDF"
    return

if __name__ == "__main__":
    print dt.datetime.now() # print starting time
    main() # run main
    print dt.datetime.now() # print finishing time
