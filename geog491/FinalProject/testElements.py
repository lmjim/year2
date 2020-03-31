import arcpy # import ArcGIS functions
from arcpy import env # import env for ease of use
wrkspc = r"R:\Geog491_6\Student_Data\ljim\FinalProject" # define workspace path
env.workspace = wrkspc # set GIS workspace
env.overwriteOutput = True
years = [1999, 2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017]
blankDocument = "Layout.mxd" # path to blank document with 3 data frames

mxd = arcpy.mapping.MapDocument(blankDocument)
elemlist = arcpy.mapping.ListLayoutElements(mxd, "TEXT_ELEMENT")
elemlist[0].name = "textbox"
elemlist[1].name = "title"
for elem in elemlist:
    print elem.name
elemlist[0].text = "Textbox"
elemlist[1].text = "Title"

elemlist = arcpy.mapping.ListLayoutElements(mxd, "MAPSURROUND_ELEMENT")
for elem in elemlist:
    print elem.name
mxd.saveACopy("elemtest.mxd")
