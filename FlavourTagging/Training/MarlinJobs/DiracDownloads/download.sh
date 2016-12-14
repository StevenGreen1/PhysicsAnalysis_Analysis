#!/bin/bash

while true
do
    python DownloadCLICSamplesThreaded.py
    echo "Sleeping for 5 minutes before attempting next download."
    sleep 5m
done

