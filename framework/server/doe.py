from fcccDesign import fcccDesign

class doe():
    
    def __init__(self, struct):
        '''
        Constructor
        '''
        self.appStruct = struct

    def buildDoe(self):
        if( self.appStruct.getDoeKind() == "fcccd" ):
            confs = fcccDesign( self.appStruct.getParamsValues(), 
                                self.appStruct.getNumOPs() )
            
            return confs.buildConfigurations()