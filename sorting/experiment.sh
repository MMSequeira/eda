#!/bin/sh
bin/Release/sorting ../../sort-data/ shuffled shuffled_results.csv
bin/Release/sorting ../../sort-data/ partially_sorted partially_sorted_results.csv
bin/Release/sorting ../../sort-data/ sorted sorted_results.csv
