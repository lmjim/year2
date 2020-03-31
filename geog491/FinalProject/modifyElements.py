import arcpy
import getStats
def configText(years, wrkspc):
    # Create and configure all text elements
    for year in years:
        currentDataSet = "data" + str(year) # define currect data set
        document = wrkspc + "\\" + str(year) + "\\" + currentDataSet + ".mxd" # define map document path
        totalDeaths = getStats.getTotal(wrkspc, currentDataSet, document) # get total number of deaths for the year (used later on)
        maxDeaths = getStats.getMax(wrkspc, currentDataSet, document) # get top two states with worst number of deaths for the year
        maxCrudeRate = getStats.getCrudeMax(wrkspc, currentDataSet, document) # get top two states with worst rate of death for the year
        mxd = arcpy.mapping.MapDocument(document) # open map document

        # Create a total of 8 textboxes
        elemlist = arcpy.mapping.ListLayoutElements(mxd, "TEXT_ELEMENT") # get list of text elements
        i = 0
        while i < 7:
            elemlist[0].clone() # element 0 is a textbox, so clone it
            i = i + 1
        del elemlist
        
        # Modify text elements
        elemlist = arcpy.mapping.ListLayoutElements(mxd, "TEXT_ELEMENT") # get current list of text elements
        note = elemlist[0] # define variable
        note.name = "note" # set element name
        note.text = "* Crude Rate is per 100,000 based on state's population" # set what the text says
        analysis = elemlist[1] # define variable
        analysis.name = "analysis" # set element name
        analysis.text = maxDeaths[0] + " has the highest total number of deaths followed by " + maxDeaths[1] + ".\n" + maxCrudeRate[0] + " has the highest crude rate followed by " + maxCrudeRate[1] + "." # set what the text says
        total = elemlist[2] # define variable
        total.name = "total" # set element name
        total.text = "Total Number of Deaths Caused by Firearms: " + str(totalDeaths) # set what the text says
        hawaii = elemlist[3] # define variable
        hawaii.name = "hawaiiLabel" # set element name
        hawaii.text = "Hawaii" # set what the text says
        alaska = elemlist[4] # define variable
        alaska.name = "alaskaLabel" # set element name
        alaska.text = "Alaska" # set what the text says
        contUS = elemlist[5] # define variable
        contUS.name = "contUSLabel" # set element name
        contUS.text = "Contiguous United States" # set what the text says
        sources = elemlist[6] # define variable
        sources.name = "sources" # set element name
        sources.text = "Sources: NYU Spatial Data Repository; United States Census Bureau; National Center for Injury Prevention and Control, CDC" # set what the text says
        author = elemlist[7] # define variable
        author.name = "author" # set element name
        author.text = "Created by: Lily Jim" # set what the text says
        title = elemlist[8] # define variable
        title.name = "title" # set element name
        title.text = "Deaths Caused by Firearms in " + str(year) # set title

        # Set text positions
        # Note
        note.fontSize = 10.0
        note.elementHeight =  0.1552
        note.elementWidth = 3.447
        note.elementPositionX = 6.6765
        note.elementPositionY = 1.5
        # Analysis
        analysis.fontSize = 9.53
        analysis.elementHeight = 0.30
        analysis.elementWidth = 3.9645
        analysis.elementPositionX = 6.4178
        analysis.elementPositionY = 1.75
        # Total
        total.fontSize = 12.89
        total.elementHeight = 0.20
        total.elementWidth = 4.1882
        total.elementPositionX = 6.3059
        total.elementPositionY = 2.1
        # Hawaii
        hawaii.fontSize = 10.0
        hawaii.elementHeight = 0.150
        hawaii.elementWidth = 0.4028
        hawaii.elementPositionX = 3.7172
        hawaii.elementPositionY = 1.8
        # Alaska
        alaska.fontSize = 10.0
        alaska.elementHeight = 0.15
        alaska.elementWidth = 0.4028
        alaska.elementPositionX = 1.7172
        alaska.elementPositionY = 1.8
        # Contiguous US
        contUS.fontSize = 12.89
        contUS.elementHeight = 0.20
        contUS.elementWidth = 2.0296
        contUS.elementPositionX = 6.758
        contUS.elementPositionY = 2.8
        # Sources
        sources.fontSize = 9.67
        sources.elementHeight = 0.150
        sources.elementWidth = 7.484
        sources.elementPositionX = 2.516
        sources.elementPositionY = 7.3
        # Author
        author.fontSize = 9.66
        author.elementHeight = 0.150
        author.elementWidth = 1.1786
        author.elementPositionX = 1
        author.elementPositionY = 7.3
        # Title
        title.fontSize = 19.33
        title.elementHeight = 0.30
        title.elementWidth = 4.2979
        title.elementPositionX = 3.3511
        title.elementPositionY = 7.45

        # Save the document
        mxd.save()
    return

def configScaleBar(years, wrkspc):
    # Change size and placement of scalebars
    for year in years:
        currentDataSet = "data" + str(year) # define currect data set
        document = wrkspc + "\\" + str(year) + "\\" + currentDataSet + ".mxd" # define map document path
        mxd = arcpy.mapping.MapDocument(document) # open map document
        elemlist = arcpy.mapping.ListLayoutElements(mxd, "MAPSURROUND_ELEMENT", "Alternating Scale Bar") # get list of scalebars
        # Contiguous US
        contUS = elemlist[2]
        contUS.name = "contUSScale"
        contUS.elementHeight = 0.3156
        contUS.elementWidth = 2.5713
        contUS.elementPositionX = 6.6144
        contUS.elementPositionY = 2.4344
       # Hawaii
        hawaii = elemlist[1]
        hawaii.name = "hawaiiScale"
        hawaii.elementHeight = 0.2525
        hawaii.elementWidth = 1.320
        hawaii.elementPositionX = 3.2579
        hawaii.elementPositionY = 1.4975
        # Alaska
        alaska = elemlist[0]
        alaska.name = "alaskaScale"
        alaska.elementHeight = 0.2525
        alaska.elementWidth = 1.3214
        alaska.elementPositionX = 1.2579
        alaska.elementPositionY = 1.4975

        # Save document
        mxd.save()
    return

def configNorthArrow(years, wrkspc):
    # Change the size and placement of arrows
    for year in years:
        currentDataSet = "data" + str(year) # define currect data set
        document = wrkspc + "\\" + str(year) + "\\" + currentDataSet + ".mxd" # define map document path
        mxd = arcpy.mapping.MapDocument(document) # open map document
        elemlist = arcpy.mapping.ListLayoutElements(mxd, "MAPSURROUND_ELEMENT", "North Arrow") # get list of north arrows
        # Contiguous US
        contUS = elemlist[2]
        contUS.name = "contUSArrow"
        contUS.elementHeight = 0.4
        contUS.elementWidth = 0.192
        contUS.elementPositionX = 9.304
        contUS.elementPositionY = 2.5
        # Hawaii
        hawaii = elemlist[1]
        hawaii.name = "hawaiiArrow"
        hawaii.elementHeight = 0.4
        hawaii.elementWidth = 0.192
        hawaii.elementPositionX = 4.6453
        hawaii.elementPositionY = 1.55
        # Alaska
        alaska = elemlist[0]
        alaska.name = "alaskaArrow"
        alaska.elementHeight = 0.4
        alaska.elementWidth = 0.192
        alaska.elementPositionX = 1.0
        alaska.elementPositionY = 1.55

        # Save document
        mxd.save()
    return

def configLegend(years, wrkspc):
    # Change size and placement of legend
    for year in years:
        currentDataSet = "data" + str(year) # define currect data set
        document = wrkspc + "\\" + str(year) + "\\" + currentDataSet + ".mxd" # define map document path
        mxd = arcpy.mapping.MapDocument(document) # open map document
        legend = arcpy.mapping.ListLayoutElements(mxd, "LEGEND_ELEMENT")[0] # get legend
        # Legend
        legend.elementHeight = 1.6
        legend.elementWidth = 0.9857
        legend.elementPositionX = 5.2815
        legend.elementPositionY = 1.4

        # Save document
        mxd.save()
    return
