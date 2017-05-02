from collections import OrderedDict

class appStruct():
    def __init__( self, appName ):
        '''
        Constructor
        '''
        self.name = appName
        self.status = "unknown"

        # hostpid that sends app info to the server
        self.infoHostpid = ""
        
        # default doe
        self.doeKind = "fcccd"

        self.lhdSamples = None
        
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
        self.doeConfsNumber = 0
        
        self.hostpids = []
        
        # lista di oggetti di tipo configuration
        self.doneConfs = []
        
        # parameters:metrics (in this order)
        # es.: [ ["1 100000:5.4573 32.584"], ["5 1000000:0.235 6.432"] ]
        self.OPsList = []
        
        self.otherOPs = []

        # key: configuration, values: metrics values list
        # key es.: "1 100000"
        # values es.: [5.123, 126.45768]

        # I update this dictionary adding metric values everytime I receive them;
        # at the end I will divide metrics values by numOPs --> 
        # every configuration will have metrics mean values 
        self.DoEsModel = {}

        # String version of DoEsModel
        # es.: [ ["1 100000 5.4573 32.584"], ["8 500000 4.4573 30.584"], ... ]
        self.DoEsModelString = []
        
        # features and metrics (in this order)
        # es.: [ ["1 100000:5.4573 32.584"], ["1 200000:4.4573 30.584"], ["1 300000:3.4573 28.584"], ... ]
        self.model = []
    
    
    
    
    
    def getName( self ):
        return self.name
    
    
    
    
    
    def getStatus( self ):
        return self.status
    
    def setStatus( self, stat ):
        self.status = stat
        
        
        
        
        
    def setDoeKind( self, k ):
        self.doeKind = k
    
    def getDoeKind( self ):
        return self.doeKind





    def setLhdSamples( self, num ):
        self.lhdSamples = num

    def getLhdSamples( self ):
        return self.lhdSamples





    def getInfoHostpid( self ):
        return self.infoHostpid

    def setInfoHostpid( self, hostpid ):
        self.infoHostpid = hostpid





    def getDoEsModelKeyValues( self, key ):
        return self.DoEsModel[key]

    def setDoEsModelKeyValues( self, key, values ):
        self.DoEsModel[key] = values

    def HasDoEsModelKey( self, key ):
        if( self.DoEsModel.has_key(key) ):
            return True

        else:
            return False

    def DoEsModelMeans(self):
        print( "\n##################################################" )

        print( "\nDoEsModel:" )

        for key, values in self.DoEsModel.iteritems():
            opString = key
            # opString es.: "1 100000"

            for i in range( len(values) ):
                values[i] /= float( self.numOPs )

                opString += " " + str( values[i] )

            print( opString )

            self.DoEsModelString.append( opString )

        print( "\n##################################################" )





    def getDoEsModelString( self ):
        return self.DoEsModelString


    
    
        
    def getRsmKind( self ):
        return self.rsmKind
    
    def setRsmKind( self, rsm ):
        self.rsmKind = rsm
    
    
    
    
    
    def addHostpid( self, hostpid ):
        self.hostpids.append( hostpid )
    
    def removeHostpid( self, hostpid ):
        self.hostpids.remove( hostpid )

    def getHostpids( self ):
        return self.hostpids
        
        
        
        
        
    def setNumOPs( self, num ):
        self.numOPs = num
    
    def getNumOPs( self ):
        return self.numOPs
       
        
        
        
    
    def getParams( self ):
        return self.params
    
    def addParam( self, param ):
        self.params.append( param )
        
        
        
        
        
    def addMetric( self, metric ):
        self.metrics.append( metric )
    
    def getMetrics( self ):
        return self.metrics
    
    
    
    
    
    def getParamsValues( self ):
        return self.paramsValues
    
    def addParamValues( self, values ):
        self.paramsValues.append( values )
    
    
    
    

    def getDoeConfs( self ):
        return self.doeConfs
    
    def setDoeConfs( self, confs ):
        self.doeConfs = confs
    
    def addDoeConf( self, conf ):
        self.doeConfs.append( conf )
        
        
        
        
    
    def getDoeConfsNumber( self ):
        return self.doeConfsNumber
    
    def setDoeConfsNumber( self, num ):
        self.doeConfsNumber = num
    
    def removeConfToDoeConfs( self, conf ):
        self.doeConfs.remove( conf )
    
    
    
    

    def getSparkGenLinearRegrTransforms( self ):
        return self.sparkGenLinearRegrTransforms
    
    def addMetricToSparkGenLinearRegrTransforms( self, metric ):
        self.sparkGenLinearRegrTransforms[metric] = []
    
    def addMetricInfoToSparkGenLinearRegrTransforms( self, metric, info ):
        self.sparkGenLinearRegrTransforms[metric].append( info )
            
            
       
            
            
    def addConfToDoneConfs( self, conf ):
        self.doneConfs.append( conf )
        
    def getDoneConfs( self ):
        return self.doneConfs
    
    
    
    
    
    def addOP( self, op ):
        self.OPsList.append( op )
    
    def getOPsList( self ):
        return self.OPsList
    
    
    
    
    
    def addOtherOP( self, op ):
        self.otherOPs.append( op )
    
    
    
    
    
    def setModel( self, model ):
        self.model = model
        
    def getModel( self ):
        return self.model





    def refreshStruct( self ):
        self.status = "unknown"
        self.infoHostpid = ""
        self.doeKind = "fcccd"
        self.numOPs = 1
        self.rsmKind = "sparkGenLinRegr"
        self.sparkGenLinearRegrTransforms.clear()
        self.params = []
        self.paramsValues = []
        self.metrics = []
    
    
    
    
    
    
    
    
    
    
    def showStruct( self ):
        print( "\n##################################################" )
        
        print( "\nappStruct" )
        
        print( "\nname:" )
        print( self.name )

        print( "\ninfoHostpid:" )
        print( self.infoHostpid )
        
        print( "\nstatus:" )
        print( self.status )
        
        print( "\nparameters:" )
        print( self.params )
        print( self.paramsValues )
        
        print( "\nmetrics:" )
        print( self.metrics )
        
        print( "\ndoe: " + self.doeKind )
        print( "numOPs: " + str( self.numOPs ) )

        print( "\nrsm: " + self.rsmKind )
        
        print( "\nsparkGenLinearRegrTransforms:" )
        print( self.sparkGenLinearRegrTransforms )
        
        print( "\nhostpids:" )
        print( self.hostpids )
        
        print( "\ndoeConfs:" )
        for confObj in self.doeConfs:
            for value in confObj.getConf():
                print value,
            print( " [remaining OPs: " + str( confObj.getNumOPs() ) + "]" )
        
        print( "\n\ndoneConfs:" )
        for confObj in self.doneConfs:
            for value in confObj.getConf():
                print value,
            print
        
        print( "\nOPsList:" )
        for op in self.OPsList:
            print op

        # print( "otherOPs:" )
        # for op in self.otherOPs:
        #     print op

        print( "\nDoEModel:" )
        for op in self.DoEsModelString:
            print op

        print( "\nmodel:" )
        for op in self.model:
            print op
                    
        print( "\n##################################################" )