import arcpy
def setUp(years, wrkspc, blankDocument):
    # Create each document
    for year in years:
        # Create document for new year
        currentDataSet = "data" + str(year) # define currect data set
        untitled = arcpy.mapping.MapDocument(blankDocument) # open blank document
        document = wrkspc + "\\" + str(year) + "\\" + currentDataSet + ".mxd" # define map document path
        untitled.saveACopy(document) # save blank document as new map document for current data set
        del untitled # delete variable

    # Set up the dataframes
    for year in years:
        # Access Document
        currentDataSet = "data" + str(year) # define currect data set
        document = wrkspc + "\\" + str(year) + "\\" + currentDataSet + ".mxd" # define map document path
        mxd = arcpy.mapping.MapDocument(document) # open new map document
        df1 = arcpy.mapping.ListDataFrames(mxd)[0] # get first data frame
        df2 = arcpy.mapping.ListDataFrames(mxd)[1] # get second data frame
        df3 = arcpy.mapping.ListDataFrames(mxd)[2] # get third data frame
        legend = arcpy.mapping.ListLayoutElements(mxd, "LEGEND_ELEMENT")[0]
        legend.autoAdd = False
        
        # Make shapefiles into layers
        arcpy.Copy_management("shapeFiles/US_states.shp", wrkspc + "\\" + str(year) + "\\US_states.shp")
        arcpy.AddField_management(wrkspc + "\\" + str(year) + "\\US_states.shp", "CRUDE_RATE", "DOUBLE")
        usStates = arcpy.mapping.Layer(wrkspc + "\\" + str(year) + "\\US_states.shp") # create layer from shapefile
        na = arcpy.mapping.Layer("shapeFiles/North_America.shp") # create layer from shapefile
        mainland = arcpy.mapping.Layer("shapeFiles/mainland.shp") # create layer form shapefile
        hawaii = arcpy.mapping.Layer("shapeFiles/hawaii.shp") # create layer form shapefile
        alaska = arcpy.mapping.Layer("shapeFiles/alaska.shp") # create layer form shapefile
        
        # Join table to layer
        table = "dataTables/" + currentDataSet + ".csv" # define data table
        arcpy.AddJoin_management(usStates, "NAME", table, "State")
        field = currentDataSet + ".csv.Crude Rate"
        arcpy.CalculateField_management(usStates, "CRUDE_RATE", "!" + field + "!", "PYTHON")
        
        # Set up data frames with appropriate layers
        # Mainland, data frame 1
        df1.name = "mainland" # rename first data frame to mainland
        mainland.visible = False
        arcpy.mapping.AddLayer(df1, mainland) # add mainland to mainland frame
        legend.autoAdd = True
        arcpy.mapping.AddLayer(df1, usStates, "BOTTOM") # add US States to mainland frame
        legend.autoAdd = False
        arcpy.mapping.AddLayer(df1, na, "BOTTOM") # add North America to mainland frame
        # Hawaii, data frame 2
        df2.name = "hawaii" # rename second data frame to mainland
        hawaii.visible = False
        arcpy.mapping.AddLayer(df2, hawaii) # add hawaii to hawaii frame
        arcpy.mapping.AddLayer(df2, usStates, "BOTTOM") # add US States to hawaii frame
        arcpy.mapping.AddLayer(df2, na, "BOTTOM") # add North America to hawaii frame
        # Alaska, data frame 3
        df3.name = "alaska" # rename third data frame to mainland
        alaska.visible = False
        arcpy.mapping.AddLayer(df3, alaska) # add alaska to alaska frame
        arcpy.mapping.AddLayer(df3, usStates, "BOTTOM") # add US States to alaska frame
        arcpy.mapping.AddLayer(df3, na, "BOTTOM") # add North America to alaska frame

        # Set Positions
        # Mainland
        df1.elementHeight = 4.1538
        df1.elementWidth = 9
        df1.elementPositionX = 1
        df1.elementPositionY = 3.0962
        # Hawaii
        df2.elementHeight = 1.0
        df2.elementWidth = 1.8373
        df2.elementPositionX = 3.0
        df2.elementPositionY = 2.0
        # Alaska
        df3.elementHeight = 1.0
        df3.elementWidth = 1.8372
        df3.elementPositionX = 1
        df3.elementPositionY = 2.0
        
        # Set Extents
        # Mainland
        extent1 = df1.extent
        extent1.XMin = -125.654729593
        extent1.XMax = -65.757570507
        extent1.YMin = 23.357817783
        extent1.YMax = 51.002660438
        df1.extent = extent1
        # Hawaii
        extent2 = df2.extent
        extent2.XMin = -179.699756338
        extent2.XMax = -153.499628662
        extent2.YMin = 16.56082258
        extent2.YMax = 30.82190642 
        df2.extent = extent2
        # Alaska
        extent3 = df3.extent
        extent3.XMin = -181.544314649
        extent3.XMax = -128.085270896
        extent3.YMin = 46.270878862
        extent3.YMax = 75.369359388
        df3.extent = extent3
        
        # Save the document
        mxd.save()
    return
