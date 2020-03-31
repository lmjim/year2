import arcpy

wrkspc = r"R:\Geog491_6\Student_Data\ljim\FinalProject" # define workspace path
arcpy.env.workspace = wrkspc # set GIS workspace
arcpy.env.overwriteOutput = True

##document = wrkspc + "\\states2015.mxd"
##mxd = arcpy.mapping.MapDocument(document) # open map document
##df = arcpy.mapping.ListDataFrames(mxd)[0]
##lyrs = arcpy.mapping.ListLayers(mxd, "", df)
##for lyr in lyrs:
##    print lyr.name
####arcpy.SaveToLayerFile_management(lyrs[1], "statesSymbology.lyr")
##arcpy.SaveToLayerFile_management(lyrs[2], "naSymbology.lyr")



year = 2015
currentDataSet = "data" + str(year) # define currect data set
document = wrkspc + "\\" + currentDataSet + ".mxd" # define map document path
statesSymbology = arcpy.mapping.Layer(wrkspc + "\\statesSymbology.lyr")
naSymbology = arcpy.mapping.Layer(wrkspc + "\\naSymbology.lyr")
mxd = arcpy.mapping.MapDocument(document)

dfs = arcpy.mapping.ListDataFrames(mxd)
for df in dfs:
    lyrs = arcpy.mapping.ListLayers(mxd, "", df)
    arcpy.mapping.UpdateLayer(df, lyrs[1], statesSymbology)
    arcpy.mapping.UpdateLayer(df, lyrs[2], naSymbology)

##    symbologyFields = [["VALUE_FIELD", "firearm_deaths_by_state.csv.Crude_Rate_2015", "data2015.csv.Crude Rate"]]
##    arcpy.ApplySymbologyFromLayer_management(lyrs[1], statesSymbology)
    
mxd.saveACopy("data2015Symbology.mxd")
