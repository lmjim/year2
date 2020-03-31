# Image URL Crawler

This simple program crawls the free image hosting site, pexels.com, and prints out URLs and captions for images.

Code is provided *AS-IS* with no guarentees of correctness. The user has full permission to use/modify/distribute this script as they may see fit.

## Install

This script was written in Python 3.6.7.

1) Clone this repo.

2) Run `pip install -r requirements.txt`

## Use

To find image URLs, run the command:

    Python img_urls.py <IMAGE CATEGORY>

where `<IMAGE CATEGORY>` is a space-delimited query for images.

### Examples

 example, to get a bunch of cat image URLs/captions run

    python img_urls.py cats

    python img_urls.py cute cats

    python img_urls.py an island with a boat next to it

This script passes your arguments to the pexels query engine.

## Results

Results are passed to standard out. Pipe them to a file with pipes.

    python img_urls.py an island with a boat next to it > Island_boat_urls.txt

### Output

The script prints the URL and then caption followed by a newline, and possibly more images.

    https://images.pexels.com/photos/2100305/pexels-photo-2100305.jpeg?auto=compress&cs=tinysrgb&dpr=1&w=500
    Aerial Photography Of Boat Sailing Near Island

    https://images.pexels.com/photos/2106183/pexels-photo-2106183.jpeg?auto=compress&cs=tinysrgb&dpr=1&w=500
    Aerial Island View

    https://images.pexels.com/photos/460715/pexels-photo-460715.jpeg?auto=compress&cs=tinysrgb&dpr=1&w=500
    Aerial Photography of Boat on Lake

    https://images.pexels.com/photos/91120/pexels-photo-91120.jpeg?auto=compress&cs=tinysrgb&dpr=1&w=500
    People on Rock by Sea
