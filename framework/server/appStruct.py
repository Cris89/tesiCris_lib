from collections import OrderedDict

class appStruct():
    def __init__(self, appName):
        '''
        Constructor
        '''
        self.name = appName
        self.status = "unknown"
        
        # default doe
        self.doeKind = "fcccd"
        self.numOPs = 1
        
        # default rsm
        self.rsmKind = "sparkGenLinRegr"
        
        # the order of the metrics must be the same here and in the opsList
        # es.: (key, value): ( "avg_throughput", ["ln", "ln", "gaussian", "log"] )
        self.sparkGenLinearRegrTransforms = OrderedDict( {} )
            
        # es.: [ "num_threads", "num_trials" ]
        self.params = []
        
        # es.: [ [1,2,3,4,5,6,7,8], [100000,200000,300000,400000,500000,600000,700000,800000,900000,1000000] ]
        self.paramsValues = []
        
        # the order of the metrics must be the same here and in the opsList
        # es.: [ "avg_error", "avg_throughput" ]
        self.metrics = []
        
        # lista di oggetti di tipo configuration
        self.doeConfs = []
        self.doeConfsNumber= 0
        
        self.hostpids = []
        
#         # dizionario: key = hostpid, value = lista di oggetti di tipo configuration
#         self.runningConfs = {}
        
        # lista di oggetti di tipo configuration
        self.doneConfs = []
        
        # parameters:metrics (in this order)
        # es.: [ ["1 100000:5.4573 32.584"], ["5 1000000:0.235 6.432"] ]
        self.OPsList = []
        
        self.otherOPs = []
        
        # features and metrics (in this order)
        # es.: [ ["1 100000 5.4573 32.584"], ["1 200000 4.4573 30.584"], ["1 300000 3.4573 28.584"] ]
        self.model = []    
    
    
    
    
    
    def getName(self):
        return self.name
    
    
    
    
    
    def getStatus(self):
        return self.status
    
    def setStatus(self, stat):
        self.status = stat
        
        
        
        
        
    def setDoeKind(self, k):
        self.doeKind = k
    
    def getDoeKind(self):
        return self.doeKind
    
    
    
    
    
    def getRsmKind(self):
        return self.rsmKind
    
    def setRsmKind(self, rsm):
        self.rsmKind = rsm
    
    
    
    
    
    def addHostpid(self, hostpid):
        self.hostpids.append(hostpid)
    
    def removeHostpid(self, hostpid):
        self.hostpids.remove(hostpid)
        
        
        
        
        
    def setNumOPs(self, num):
        self.numOPs = num
    
    def getNumOPs(self):
        return self.numOPs
       
        
        
        
    
    def getParams(self):
        return self.params
    
    def addParam(self, param):
        self.params.append(param)
        
        
        
        
        
    def addMetric(self, metric):
        self.metrics.append(metric)
    
    def getMetrics(self):
        return self.metrics
    
    
    
    
    
    def getParamsValues(self):
        return self.paramsValues
    
    def addParamValues(self, values):
        self.paramsValues.append(values)
    
    
    
    
    def getDoeConfs(self):
        return self.doeConfs
    
    def setDoeConfs(self, confs):
        self.doeConfs = confs
    
    def addDoeConf(self, conf):
        self.doeConfs.append(conf)
        
        
        
        
    
    def getDoeConfsNumber(self):
        return self.doeConfsNumber
    
    def setDoeConfsNumber(self, num):
        self.doeConfsNumber = num
    
    def removeConfToDoeConfs(self, conf):
        self.doeConfs.remove(conf)
        
        
        
        
    
#     def getRunningConfs(self):
#         return self.runningConfs
#     
#     def addHostpidToRunningConfs(self, hostpid):
#         self.runningConfs[hostpid] = []
#     
#     def addConfToRunningConfs(self, hostpid, conf):
#         self.runningConfs[hostpid].append(conf)
#     
#     def removeConfToRunningConfs(self, hostpid, conf):
#         self.runningConfs[hostpid].remove(conf)
#         
#     def restoreConfs(self, hostpid, disconnection):
#         for conf in self.runningConfs[hostpid]:
#             self.addDoeConf(conf)
#         
#         del self.runningConfs[hostpid][:]
#         
#         if( disconnection == True ):
#             del self.runningConfs[hostpid]
    
    
    
    
    
    def getSparkGenLinearRegrTransforms(self):
        return self.sparkGenLinearRegrTransforms
    
    def addMetricToSparkGenLinearRegrTransforms(self, metric):
        self.sparkGenLinearRegrTransforms[metric] = []
    
    def addMetricInfoToSparkGenLinearRegrTransforms(self, metric, info):
        self.sparkGenLinearRegrTransforms[metric].append(info)
            
            
       
            
            
    def addConfToDoneConfs(self, conf):
        self.doneConfs.append(conf)
        
    def getDoneConfs(self):
        return self.doneConfs
    
    
    
    
    
    def addOP(self, op):
        self.OPsList.append(op)
    
    def getOPsList(self):
        return self.OPsList
    
    
    
    
    
    def addOtherOP(self, op):
        self.otherOPs.append(op)
    
    
    
    
    
    def setModel(self, model):
        self.model = model
        
    def getModel(self):
        return self.model
    
    
    
    
    
    
    
    
    
    
    def showStruct(self):
        print( "\n##################################################" )
        
        print( "\nappStruct" )
        
        print( "\nname:" )
        print self.name
        
        print( "\nstatus:" )
        print self.status
        
        print( "\nparameters:" )
        print self.params
        print self.paramsValues
        
        print( "\nmetrics:" )
        print self.metrics
        
        print( "\ndoe: " + self.doeKind )
        print( "numOPs: " + str( self.numOPs ) )
        
        print( "\nsparkGenLinearRegrTransforms:" )
        print self.sparkGenLinearRegrTransforms
        
        print( "\nhostpids:" )
        print self.hostpids
        
        print( "\ndoeConfs:" )
        for confObj in self.doeConfs:
            for value in confObj.getConf():
                print value,
            print( " [remaining OPs: " + str( confObj.getNumOPs() ) + "]" )
        
#         print( "\nrunningConfs:" )
#         for key, confs in self.runningConfs.iteritems():
#             print( "\nhostpid: " + key )
#             
#             for confObj in confs:
#                 for value in confObj.getConf():
#                     print value,
#                 print
        
        print( "\n\ndoneConfs:" )
        for confObj in self.doneConfs:
            for value in confObj.getConf():
                print value,
            print
        
        print( "\nOPsList:" )
        for op in self.OPsList:
            print op
        
#         print( "\nOtherOPs:" )
#         for op in self.otherOPs:
#             print op
        
        print( "\nmodel:" )
        for op in self.model:
            print op
                    
        print( "\n##################################################" )