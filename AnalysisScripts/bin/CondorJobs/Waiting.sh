#!/bin/bash

while [ "$(condor_q -w | grep RunWhizardWeights.py | wc -l)" -gt "0" ]
do
    echo "Waiting. $(condor_q -w | grep RunWhizardWeights.py | wc -l) jobs still running.  Checking again in 5 mins."
    sleep 5m
done

echo "Jobs finished"

#python WeightToXmlConverterCondor.py

#python ConcatenateWeightFilesCondor.py
