import re
from PhysicsModel import PhysicsModel

class RPVModel(PhysicsModel):
    def __init__(self):
        pass
    def setModelBuilder(self, modelBuilder):
        "Connect to the ModelBuilder to get workspace, datacard and options. Should not be overloaded."
        self.modelBuilder = modelBuilder
        self.DC = modelBuilder.DC
        self.options = modelBuilder.options
    def setPhysicsOptions(self,physOptions):
        "Receive a list of strings with the physics options from command line"
        pass
    def doParametersOfInterest(self):
        """Create POI and other parameters, and define the POI set."""
        # --- Signal Strength as only POI --- 
        self.modelBuilder.doVar("r[1,0,20]");
        self.modelBuilder.doVar("rQCDbin0[1,0,3]");
        self.modelBuilder.doVar("rQCDbin1[1,0,3]");
        self.modelBuilder.doVar("rQCDbin3[1,0,3]");
        self.modelBuilder.doVar("rQCDbin4[1,0,3]");
        self.modelBuilder.doVar("rQCDbin6[1,0,3]");
        # low mj control regions
        self.modelBuilder.doVar("rQCDbin7[1,0,3]");
        self.modelBuilder.doVar("rQCDbin8[1,0,3]");
        self.modelBuilder.doVar("rQCDbin9[1,0,3]");
        self.modelBuilder.doVar("rTTbarbin2[1,0,6]");
        self.modelBuilder.doVar("rTTbarbin5[1,0,6]"); 
        # signal bins
        self.modelBuilder.doVar("rQCDbin10[1,0,3]");
        self.modelBuilder.doVar("rTTbarbin11[1,0,6]"); 
        self.modelBuilder.doVar("rTTbarbin12[1,0,6]"); 
        self.modelBuilder.doVar("rQCDbin13[1,0,3]");
        self.modelBuilder.doVar("rTTbarbin14[1,0,6]"); 
        self.modelBuilder.doVar("rTTbarbin15[1,0,6]"); 
        self.modelBuilder.doVar("rQCDbin16[1,0,3]");
        self.modelBuilder.doVar("rQCDbin17[1,0,3]");
        self.modelBuilder.doSet("POI","r")
    def preProcessNuisances(self,nuisances):
        "receive the usual list of (name,nofloat,pdf,args,errline) to be edited"
        pass # do nothing by default
#        for (n,nf,p,a,e) in nuisances:
#            print "Setting range to (-4,4) for nuisance " + str(n)
#            self.modelBuilder.out.Print("v")
#            self.modelBuilder.out.var(str(n)).Print("v")
#            self.modelBuilder.out.var(str(n)).setRange(str(n), -4, 4)
    def getYieldScale(self,bin,process):
        "Return the name of a RooAbsReal to scale this yield by or the two special values 1 and 0 (don't scale, and set to zero)"
        if process=="ttbar":
            if (bin=="bin2" or bin=="bin5" or
                bin=="bin11" or bin=="bin12" or
                bin=="bin14" or bin=="bin15"): 
                return "rTTbar"+bin 
            # these bins are qcd-dominated so take normalization from kinematically njets-2 ttbar region
            if bin=="bin0": 
               return "rTTbarbin2"
            if bin=="bin1": 
               return "rTTbarbin2"
            if bin=="bin3": 
               return "rTTbarbin5"
            if bin=="bin4": 
               return "rTTbarbin5"
            if bin=="bin10": 
               return "rTTbarbin12"
            if bin=="bin13": 
               return "rTTbarbin15"
            if bin=="bin16": 
               return "rTTbarbin11"
            if bin=="bin17": 
               return "rTTbarbin14"
#            return "rTTbar" 
        if process=="qcd": 
            if (bin=="bin0" or bin=="bin1" or
                bin=="bin3" or bin=="bin4" or
                bin=="bin6" or bin=="bin7" or bin=="bin8" or bin=="bin9" or
                bin=="bin10" or bin=="bin13" or bin=="bin16" or bin=="bin17"):
                return "rQCD"+bin 
            # these bins are ttbar-dominated so take normalization from kinematically njets+2 QCD region
            if bin=="bin2":
                return "rQCDbin1"
            if bin=="bin5":
                return "rQCDbin4"
            if bin=="bin11":
                return "rQCDbin16"
            if bin=="bin12":
                return "rQCDbin10"
            if bin=="bin14":
                return "rQCDbin17"
            if bin=="bin15":
                return "rQCDbin13"
        return "r" if self.DC.isSignal[process] else 1;
    def done(self):
        "Called after creating the model, except for the ModelConfigs"
        pass

rpvModel = RPVModel()

