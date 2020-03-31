# About This Project

The script finalproject.py creates ArcMap documents, exporting them to pdf. The information mapped comes from the CDC.
The data contains information on the number of deaths caused by firearms in the United States, broken up by year and state.
This data is joined to shapefiles to produce a standardized map for each year.
The pdfs this script creates are already provided in the results folder.

*Disclaimer: Not affiliated with ESRI or CDC in any way.*  
**CDC data has restrictions on it**, see [terms of use](https://wonder.cdc.gov/mcd-icd10.html "CDC Wonder Database").

---

## Files Needed to Run

All files needed to run are provided in this repo. These are necessary:

1. 19 folders labeled for each year 1999-2017 and one labeled results  
   *These folders can be empty, but they need to exist*
2. dataTables folder containing the csv files from the CDC
3. shapeFiles folder containing the shapefiles used in this project
4. layout folder containg two .lyr files for symbology and one .mxd for layout
5. The following python files:  
   + finalproject  
   + createDocuments  
   + modifyElements  
   + getStats  
   + createChoropleth

*The .py files that start with 'test' are not necessary.*

---

## How to Run

If you are using IDLE, make sure to open version that came with your ArcGIS suite.

1. Open finalproject.py
2. Change the wrkspc path found on line 17  
   + The path should match the path to the FinalProject directory on your computer  
   + The path should end with "\FinalProject"  
   + The path cannot have any spaces in it  
   *If you want to run the test files, they also require a similar edit of the wrkspc path*
3. Run finalproject.py
4. Open the results folder the generated pdfs

