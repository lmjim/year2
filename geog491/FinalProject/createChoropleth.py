import arcpy
def changeDisplay(years, wrkspc):
    # Change symbology of states to a choropleth of crude rate
    # Set North America to a gray color
    statesSymbology = arcpy.mapping.Layer(wrkspc + "\\layout\\statesSymbology.lyr") # Layer that has correct symbology for states
    naSymbology = arcpy.mapping.Layer(wrkspc + "\\layout\\naSymbology.lyr") # Layer that has correct symbology for N.A.
    for year in years: # for each year
        currentDataSet = "data" + str(year) # define currect data set
        document = wrkspc + "\\" + str(year) + "\\" + currentDataSet + ".mxd" # define map document path
        mxd = arcpy.mapping.MapDocument(document) # open map document
        dfs = arcpy.mapping.ListDataFrames(mxd) # get list of data frames
        for df in dfs: # for each data frame
            lyrs = arcpy.mapping.ListLayers(mxd, "", df) # get list of layers
            arcpy.mapping.UpdateLayer(df, lyrs[1], statesSymbology) # update states layer to match wanted symbology
            arcpy.mapping.UpdateLayer(df, lyrs[2], naSymbology) # update N.A. layer to match wanted symbology
        
        mxd.save() # save the document
    return

#changeDisplay([2015], r"R:\Geog491_6\Student_Data\ljim\FinalProject") # this is for testing purposes
