#!/usr/bin/python

import os, sys, getopt, re, subprocess, math, dircache, logging, time, random, string

class CondorFitting:
    'Common base class for running whizard on condor'

### ----------------------------------------------------------------------------------------------------
### Start of constructor
### ----------------------------------------------------------------------------------------------------

    def __init__(self):
        self._FittingArgList = [] 
        self._CondorMaxRuns = 10000000 

        self._ExecutableName = 'PerfectAnalysis.sh'
        self._Executable = os.path.join('/var/clus/usera/sg568/PhysicsAnalysis/Analysis/AnalysisScripts/bin', self._ExecutableName)
        savePath = '/r06/lc/sg568/PhysicsAnalysis/Analysis/Chi2Fragments/Optimisation_1400GeV/'
        for i in range(0,141):
            self._FittingArgList.append(str(i*10000) + ' ' + str((i+1)*10000) + ' ' + savePath)
        self.runCondorJobs()

        self._ExecutableName = 'Analysis.sh'
        self._Executable = os.path.join('/var/clus/usera/sg568/PhysicsAnalysis/Analysis/AnalysisScripts/bin', self._ExecutableName)
        savePath = '/r06/lc/sg568/PhysicsAnalysis/Analysis/Chi2Fragments/Final_1400GeV/'
        for i in range(0,141):
            self._FittingArgList.append(str(i*10000) + ' ' + str((i+1)*10000) + ' ' + savePath)
        self.runCondorJobs()

#        self._ExecutableName = 'PerfectAnalysis3000.sh'
#        savePath = '/r06/lc/sg568/PhysicsAnalysis/Analysis/Chi2Fragments/Optimisation_3000GeV/'
#        self._Executable = os.path.join('/var/clus/usera/sg568/PhysicsAnalysis/Analysis/AnalysisScripts/bin', self._ExecutableName)
#        for i in range(0,285):
#            self._FittingArgList.append(str(i*10000) + ' ' + str((i+1)*10000) + ' ' + savePath)
#        self.runCondorJobs()

#        self._ExecutableName = 'Analysis3000.sh'
#        savePath = '/r06/lc/sg568/PhysicsAnalysis/Analysis/Chi2Fragments/Final_3000GeV/'
#        self._Executable = os.path.join('/var/clus/usera/sg568/PhysicsAnalysis/Analysis/AnalysisScripts/bin', self._ExecutableName)
#        for i in range(0,285):
#            self._FittingArgList.append(str(i*10000) + ' ' + str((i+1)*10000) + ' ' + savePath)
#        self.runCondorJobs()

        self.checkCondorJobs()

### ----------------------------------------------------------------------------------------------------
### Start of runCondorJobs function
### ----------------------------------------------------------------------------------------------------

    def runCondorJobs(self):
        nQueued = self.nQueuedCondorJobs()
        condorJobFile = 'Fitting.job'

        while True:
            for idx, arguement in enumerate(self._FittingArgList):
                nRemaining = len(self._FittingArgList) - idx - 1
                nQueued = 0 

                while True:
                    nQueued = self.nQueuedCondorJobs()
                    if nQueued >= self._CondorMaxRuns:
                        time.sleep(10)
                    else:
                        break

                with open(condorJobFile, 'w') as jobFile:
                    jobString = self.getCondorJobString(idx, arguement)
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

    def getCondorJobString(self, idx, arguement):
        jobString  = 'executable              = ' + self._Executable + '                                             \n'
        jobString += 'initial_dir             = ' + os.getcwd() + '                                                  \n'
        jobString += 'notification            = never                                                                \n'
        jobString += 'Requirements            = ( POOL == \"GEN_FARM\" && OSTYPE == \"SLC6\" )                       \n'
        jobString += 'Rank                    = memory                                                               \n'
        jobString += 'output                  = ' + os.environ['HOME'] + '/CondorLogs/Fitting_' + os.path.splitext(self._ExecutableName)[0] + '_' + '_'.join(arguement.split(' ')[:-1]) + '.out  \n'
        jobString += 'error                   = ' + os.environ['HOME'] + '/CondorLogs/Fitting_' + os.path.splitext(self._ExecutableName)[0] + '_' + '_'.join(arguement.split(' ')[:-1]) + '.err \n'
        jobString += 'log                     = ' + os.environ['HOME'] + '/CondorLogs/Fitting_' + os.path.splitext(self._ExecutableName)[0] + '_' + '_'.join(arguement.split(' ')[:-1]) + '.log \n'
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
                time.sleep(1000)
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
CondorFitting()
