import arcpy

wrkspc = r"R:\Geog491_6\Student_Data\ljim\FinalProject" # define workspace path
arcpy.env.workspace = wrkspc # set GIS workspace
arcpy.env.overwriteOutput = True
years = [1999, 2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017]

minList = []
maxList = []

for year in years:
    currentDataSet = "data" + str(year) # define currect data set
    document = wrkspc + "\\" + str(year) + "\\" + currentDataSet + ".mxd" # define map document path
    mxd = arcpy.mapping.MapDocument(document)
    df = arcpy.mapping.ListDataFrames(mxd)[0]
    intable = arcpy.mapping.ListLayers(mxd, "", df)[1]
    outtable = wrkspc + "\\sumstats"
    fieldName = currentDataSet + ".csv.Crude Rate"
    path = arcpy.Statistics_analysis(intable, outtable, [[fieldName, "MAX"]])
    fields = arcpy.ListFields(path)
    maximum = [row[0] for row in arcpy.da.SearchCursor(path, [fields[3].name])][0]
    path = arcpy.Statistics_analysis(intable, outtable, [[fieldName, "MIN"]])
    fields = arcpy.ListFields(path)
    minimum = [row[0] for row in arcpy.da.SearchCursor(path, [fields[3].name])][0]
    minList.append(minimum)
    maxList.append(maximum)
    print str(minimum) + " : " + str(maximum)
print minList
print min(minList)
print maxList
print max(maxList)
