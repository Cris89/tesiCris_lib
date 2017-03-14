from fcccDesign import fcccDesign
from pbDesign import pbDesign
from ff2lDesign import ff2lDesign

class doe():
    def __init__( self, struct ):
        '''
        Constructor
        '''
        self.appStruct = struct

    def buildDoe( self ):
        if( self.appStruct.getDoeKind() == "fcccd" ):
            confs = fcccDesign( self.appStruct.getParamsValues(), 
                                self.appStruct.getNumOPs() )
            
            return confs.buildConfigurations()

        elif( self.appStruct.getDoeKind() == "pbd" ):
            confs = pbDesign( self.appStruct.getParamsValues(), 
                                self.appStruct.getNumOPs() )
            
            return confs.buildConfigurations()

        elif( self.appStruct.getDoeKind() == "ff2l" ):
            confs = ff2lDesign( self.appStruct.getParamsValues(), 
                                self.appStruct.getNumOPs() )
            
            return confs.buildConfigurations()