#!/bin/bash

source ~/env_anita_2.sh
#source ~/ANITA/anita3/anitaBuildTool/components/icemc/setup.sh

inputFile=inputs.anita4_trigEffScan.conf

for att in `seq 0 1`;do

    sed -i.bak '/Off-axis attenuation/d' ${inputFile}
    echo "Off-axis attenuation: 0, $att, 0, $att, 0 # Attenuation applied to central phi sectors and the two adjecent ones (when 999 no signal in those antennas)" >> ${inputFile}

    att=$(($att * 1))
    output=efficiencyScanPulseAtAntennaNewTrigger/Att${att}db
    mkdir -p ${output}
    echo $output
    ./testInputAfterAntenna -i ${inputFile} -o ${output} -r 1 -n 1    

done
