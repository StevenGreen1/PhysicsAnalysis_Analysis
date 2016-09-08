from DIRAC.Core.Base import Script
Script.parseCommandLine()
from DIRAC.Resources.Catalog.FileCatalogClient import FileCatalogClient

fc = FileCatalogClient()

meta = {}
meta['ProdID']=2152 

res = fc.findFilesByMetadata(meta)
if not res['OK']:
   print res['Message']

lfns = res['Value']

print "Found %s files" % len(lfns)
for lfn in lfns:
   print lfn
