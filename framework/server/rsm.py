from sparkGenLinearRegr import sparkGenLinearRegr

class rsm():
    '''
    classdocs
    '''

    def __init__(self, struct):
        '''
        Constructor
        '''
        self.appStruct = struct
    
    def buildRsm(self):
        if( self.appStruct.getRsmKind() == "sparkGenLinRegr" ):
            rsm = sparkGenLinearRegr( self.appStruct.getName(),
                                      self.appStruct.getMetrics(),
                                      self.appStruct.getSparkGenLinearRegrTransforms(),
                                      self.appStruct.getParamsValues(),
                                      self.appStruct.getOPsList() )
            return rsm.buildModel()