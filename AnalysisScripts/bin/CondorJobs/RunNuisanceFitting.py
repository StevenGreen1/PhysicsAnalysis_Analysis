#!/usr/bin/python

import os, sys, getopt, re, subprocess, math, dircache, logging, time, random, string

class CondorNuisanceFitting:
    'Common base class for running whizard on condor'

### ----------------------------------------------------------------------------------------------------
### Start of constructor
### ----------------------------------------------------------------------------------------------------

    def __init__(self):
        self._NuisanceFittingArgList = [] 
        self._CondorMaxRuns = 10000000 
        self._ExecutableName = 'Fitting.sh'
        self._Executable = os.path.join('/var/clus/usera/sg568/PhysicsAnalysis/Analysis/AnalysisScripts/bin', self._ExecutableName)
        self._NuisanceFittingArgList.append('0.01')
        self._NuisanceFittingArgList.append('0.02')
        self._NuisanceFittingArgList.append('0.05')
        self._NuisanceFittingArgList.append('0.10')
        self.runCondorJobs()
        self.checkCondorJobs()

### ----------------------------------------------------------------------------------------------------
### Start of runCondorJobs function
### ----------------------------------------------------------------------------------------------------

    def runCondorJobs(self):
        nQueued = self.nQueuedCondorJobs()
        condorJobFile = 'NuisanceFitting.job'

        while True:
            for idx, arguement in enumerate(self._NuisanceFittingArgList):
                nRemaining = len(self._NuisanceFittingArgList) - idx - 1
                nQueued = 0 

                while True:
                    nQueued = self.nQueuedCondorJobs()
                    if nQueued >= self._CondorMaxRuns:
                        time.sleep(10)
                    else:
                        break

                with open(condorJobFile, 'w') as jobFile:
                    jobString = self.getCondorJobString(idx)
                    jobString += 'arguments = ' + arguement + '\n'
                    jobString += 'queue 1 \n'
                    jobFile.write(jobString)

                subprocess.call(['condor_submit', condorJobFile])
                print 'Submitted job as there were only ' + str(nQueued) + ' jobs in the queue and ' + str(nRemaining) + ' jobs remaining.'
                time.sleep(0.5)
                os.remove(condorJobFile)

                if 0 == nRemaining:
                    print 'All condor jobs submitted.'
                    return

### ----------------------------------------------------------------------------------------------------
### End of runCondorJobs function
### ----------------------------------------------------------------------------------------------------
### Start of getCondorJobString function
### ----------------------------------------------------------------------------------------------------

    def getCondorJobString(self, idx):
        jobString  = 'executable              = ' + self._Executable + '                                             \n'
        jobString += 'initial_dir             = ' + os.getcwd() + '                                                  \n'
        jobString += 'notification            = never                                                                \n'
        jobString += 'Requirements            = ( POOL == \"GEN_FARM\" && OSTYPE == \"SLC6\" )                       \n'
        jobString += 'Rank                    = memory                                                               \n'
        jobString += 'output                  = ' + os.environ['HOME'] + '/CondorLogs/NuisanceFitting_' + str(idx) + '.out  \n'
        jobString += 'error                   = ' + os.environ['HOME'] + '/CondorLogs/NuisanceFitting_' + str(idx) + '.err \n'
        jobString += 'log                     = ' + os.environ['HOME'] + '/CondorLogs/NuisanceFitting_' + str(idx) + '.log \n'
        jobString += 'environment             = CONDOR_JOB=true                                                      \n'
        jobString += 'Universe                = vanilla                                                              \n'
        jobString += 'getenv                  = false                                                                \n'
        jobString += 'copy_to_spool           = true                                                                 \n'
        jobString += 'should_transfer_files   = yes                                                                  \n'
        jobString += 'when_to_transfer_output = on_exit_or_evict                                                     \n'
        return jobString

### ----------------------------------------------------------------------------------------------------
### End of getCondorJobString function
### ----------------------------------------------------------------------------------------------------
### Start of checkCondorJobs function
### ----------------------------------------------------------------------------------------------------

    def checkCondorJobs(self):
        while True:
            nActiveJobs = self.nQueuedCondorJobs()
            print 'There are ' + str(nActiveJobs) + ' jobs running on condor.'
            if (nActiveJobs > 0):
                time.sleep(10)
            else:
                print 'There are no more active condor jobs.'
                return

### ----------------------------------------------------------------------------------------------------
### End of checkCondorJobs function
### ----------------------------------------------------------------------------------------------------
### Start of nQueuedCondorJobs function
### ----------------------------------------------------------------------------------------------------

    def nQueuedCondorJobs(self):
        queueProcess = subprocess.Popen(['condor_q','-w'], stdout=subprocess.PIPE)
        queueOutput = queueProcess.communicate()[0]
        regex = re.compile(self._ExecutableName)
        queueList = regex.findall(queueOutput)
        return int(len(queueList))

### ----------------------------------------------------------------------------------------------------
### End of nQueuedCondorJobs function
### ----------------------------------------------------------------------------------------------------

### ----------------------------------------------------------------------------------------------------
### Call class in main
### ----------------------------------------------------------------------------------------------------
CondorNuisanceFitting()
