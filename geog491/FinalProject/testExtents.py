# test extent on states2015

import arcpy # import ArcGIS functions
from arcpy import env # import env for ease of use
wrkspc = r"R:\Geog491_6\Student_Data\ljim\FinalProject" # define workspace path
env.workspace = wrkspc # set GIS workspace
document = wrkspc + "\\states2015.mxd" # define map document path
mxd = arcpy.mapping.MapDocument(document) # open new map document
df = arcpy.mapping.ListDataFrames(mxd)[0]
ex = df.extent
print "XMin: " + str(ex.XMin)
print "XMax: " + str(ex.XMax)
print "YMin: " + str(ex.YMin)
print "YMax: " + str(ex.YMax)
