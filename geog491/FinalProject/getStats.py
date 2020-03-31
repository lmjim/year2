import arcpy
def getTotal(wrkspc, currentDataSet, document):
    # Return the total number of deaths by firearms during specified year
    mxd = arcpy.mapping.MapDocument(document) # access map document
    df = arcpy.mapping.ListDataFrames(mxd)[0] # get first data frame
    intable = arcpy.mapping.ListLayers(mxd, "", df)[1] # get states layer
    outtable = wrkspc + "\\sumstats" # define an output path, NOTE: have overwriteOutput set to true
    fieldName = currentDataSet + ".csv.Deaths" # specify which column to get statistics on
    path = arcpy.Statistics_analysis(intable, outtable, [[fieldName, "SUM"]]) # use statistics function to get sum
    fields = arcpy.ListFields(path) # get list of fields in new table
    total = int([row[0] for row in arcpy.da.SearchCursor(path, [fields[3].name])][0]) # get actual number out of table
    del mxd
    return total

def getMax(wrkspc, currentDataSet, document):
    # Return the names of the states with the highest and second highest number of deaths
    mxd = arcpy.mapping.MapDocument(document) # access map document
    df = arcpy.mapping.ListDataFrames(mxd)[0] # get first data frame
    layer = arcpy.mapping.ListLayers(mxd, "", df)[1] # get states layer
    out = wrkspc + "\\sumstats" # define an output path
    deathsField = currentDataSet + ".csv.Deaths" # specify which column to get statistics on
    path = arcpy.Statistics_analysis(layer, out, [[deathsField, "MAX"]]) # use statistics function to get max
    fields = arcpy.ListFields(path) # get list of fields in new table
    maximum = [row[0] for row in arcpy.da.SearchCursor(path, [fields[3].name])][0] # get actual number out of table
    second = 0 # intialize second highest value
    nameField = currentDataSet + ".csv.State" # define column to look at
    state = "unknown" # initialize highest state
    state2 = "unknown" # initialize second highest state
    cursor = arcpy.da.SearchCursor(layer, [nameField, deathsField], deathsField+" > 1000") # create cursor to go over states and values
    for row in cursor:
        if row[1] == maximum: # if the value matches the maximum
            state = row[0] # define the highest state
        else: # otherwise look for the second highest value and state
            if row[1] > second: # if the value is higher than the current recorded value
                second = row[1] # define the value
                state2 = row[0] # define the state
    del mxd
    return [state, state2] # return both states

def getCrudeMax(wrkspc, currentDataSet, document):
    # Return the names of the states with the highest and second highest crude rate
    mxd = arcpy.mapping.MapDocument(document) # access map document
    df = arcpy.mapping.ListDataFrames(mxd)[0] # get first data frame
    layer = arcpy.mapping.ListLayers(mxd, "", df)[1] # get states layer
    out = wrkspc + "\\sumstats" # define an output path
    rateField = "US_states.CRUDE_RATE" # specify which column to get statistics on
    path = arcpy.Statistics_analysis(layer, out, [[rateField, "MAX"]]) # use statistics function to get max
    fields = arcpy.ListFields(path) # get list of fields in new table
    maximum = [row[0] for row in arcpy.da.SearchCursor(path, [fields[3].name])][0] # get actual number out of table
    second = 0 # initialize second highest value
    nameField = currentDataSet + ".csv.State" # # define column to look at
    state = "unknown" # initialize highest state
    state2 = "unknown" # initialize secod highest state
    cursor = arcpy.da.SearchCursor(layer, [nameField, rateField], rateField + " > 15") # create cursor to go over states and values
    for row in cursor:
        if row[1] == maximum: # if the value matches the maximum
            state = row[0] # define the highest state
        else: # otherwise look for the seconnd highest value and state
            if row[1] > second: # if the value is higher than the current recorded value
                second = row[1] # define the value
                state2 = row[0] # define the state
    del mxd
    return [state, state2] # return both states

# The following is for testing purposes
#arcpy.env.overwriteOutput = True
#getTotal(r"R:\Geog491_6\Student_Data\ljim\FinalProject", "data2015", r"R:\Geog491_6\Student_Data\ljim\FinalProject\data2015.mxd")
#getMax(r"R:\Geog491_6\Student_Data\ljim\FinalProject", "data2015", r"R:\Geog491_6\Student_Data\ljim\FinalProject\data2015.mxd")
#getCrudeMax(r"R:\Geog491_6\Student_Data\ljim\FinalProject", "data2015", r"R:\Geog491_6\Student_Data\ljim\FinalProject\data2015.mxd")

