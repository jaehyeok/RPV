#!/bin/sh

# Submit batch jobs on lxplus

# Set directory where log files will be stored
# better to be in work directory instead of home directory
LOGDIR=/afs/cern.ch/user/j/jaehyeok/work/BatchLog

# numbef of toys
NTOY=100 
# seed for job 1: will be incremeneted by 1  
SEED=50000; 

#for MASS in {1000,1100,1200,1300,1400,750}
for MASS in 1500
do 

    for ITOY in $(eval echo "{1..$NTOY}")
    do  

        LOGERR=`echo Log_M${MASS}_seed${SEED}.err `
        LOGOUT=`echo $LOGERR | sed 's/err/out/g' `
        
        echo ".. bsub -q 1nh -e $LOGDIR/$LOGERR -o $LOGDIR/$LOGOUT SubmitOneJob.sh $MASS $SEED "
        bsub -q 1nh -e $LOGDIR/$LOGERR -o $LOGDIR/$LOGOUT SubmitOneJob.sh $MASS $SEED
        
        SEED=$(($SEED+1))

    done
	        
    #echo ".. Wait 20 minutes before submitting next set of jobs "
    #date 
    #sleep 1200 

done 
