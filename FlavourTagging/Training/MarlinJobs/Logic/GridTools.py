# Dirac tools for getting lists of files from the grid.
import os
import sys
import re

### ----------------------------------------------------------------------------------------------------
### Start of getRecSlcioFiles function
### ----------------------------------------------------------------------------------------------------
#-bash-4.1$ dirac-ilc-find-in-FC /ilc/user/s/sgreen Energy=1400 Type=Rec EvtType=ee_nunuww_nunuqqqq JobDescription=PhysicsAnalysis DetectorModel=clic_ild_cdr ReconstructionStage=clic_ild_cdr 

def getRecSlcioFiles(jobDescription, detModel, recoStage, energy, eventType):
    slcioFiles = []
    os.system('dirac-ilc-find-in-FC /ilc/user/s/sgreen JobDescription=' + jobDescription + ' Type=Rec DetectorModel=' + str(detModel) + ' ReconstructionStage=' + str(recoStage) + ' Energy=' + str(energy) + ' EvtType=' + eventType + ' > tmp.txt')
    with open('tmp.txt') as f:
        lines = f.readlines()
        for idx, line in enumerate(lines):
            line = line.strip()
            if '_REC.slcio' in line:
                slcioFiles.append(line)
    os.system('rm tmp.txt')
    return slcioFiles

### ----------------------------------------------------------------------------------------------------
### End of getRecSlcioFiles function
### ----------------------------------------------------------------------------------------------------
### Start of getDstSlcioFiles function
### ----------------------------------------------------------------------------------------------------

def getDstSlcioFiles(jobDescription, detModel, recoStage, energy, eventType):
    slcioFiles = []
    os.system('dirac-ilc-find-in-FC /ilc/user/s/sgreen JobDescription=' + jobDescription + ' Type=Rec DetectorModel=' + str(detModel) + ' ReconstructionStage=' + str(recoStage) + ' Energy=' + str(energy) + ' EvtType=' + eventType + ' > tmp.txt')
    with open('tmp.txt') as f:
        lines = f.readlines()
        for idx, line in enumerate(lines):
            line = line.strip()
            if '_DST.slcio' in line:
                slcioFiles.append(line)
    os.system('rm tmp.txt')
    return slcioFiles

### ----------------------------------------------------------------------------------------------------
### End of getDstSlcioFiles function
### ----------------------------------------------------------------------------------------------------
### Start of doesFileExist function
### ----------------------------------------------------------------------------------------------------

def doesFileExist(lfn):
    from DIRAC.DataManagementSystem.Client.DataManager import DataManager
    dm = DataManager()
    result = dm.getActiveReplicas(lfn)
    if not result['OK']:
        print "ERROR",result['Message']
        return False
    if lfn in result['Value']['Successful']:
        return True
    else:
        return False

### ----------------------------------------------------------------------------------------------------
### End of doesFileExist function
### ----------------------------------------------------------------------------------------------------
### Start of getCLICFiles function
### ----------------------------------------------------------------------------------------------------

def getCLICFiles(prodID):
    clicFiles = []
    os.system('dirac-ilc-find-in-FC /ilc/prod ProdID=' + str(prodID) + ' > tmp.txt')
    with open('tmp.txt') as f:
        lines = f.readlines()
        for idx, line in enumerate(lines):
            line = line.strip()
            if '/DST/' in line:
                clicFiles.append(line)
    os.system('rm tmp.txt')
    return clicFiles

### ----------------------------------------------------------------------------------------------------
### End of getCLICFiles function
### ----------------------------------------------------------------------------------------------------
### Start of orderedList function
### ----------------------------------------------------------------------------------------------------

def orderedList(inputList):
    setFromList = set(inputList)
    convert = lambda text: int(text) if text.isdigit() else text 
    alphanum_key = lambda key: [ convert(c) for c in re.split('([0-9]+)', key) ] 
    return list(sorted(setFromList, key = alphanum_key))

### ----------------------------------------------------------------------------------------------------
### End of orderedList function
### ----------------------------------------------------------------------------------------------------

