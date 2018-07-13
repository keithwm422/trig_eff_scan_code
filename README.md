#TRIGGER EFFECIENCY SCANS FOR ANITA-IV


######################################
TUFF status:TUFFs are in the paths but all notches are OFF (so TUFFs in inputs.anita4_trigeffscan.conf need to be at 1)
Attenuation: fixed 25 dB variable from Elog 691




Other settings??




This directory is used to house the tools and steps for the trigger efficiency scan of ANITA-IV in icemc. 


The data for the TES is taken from elog 691.

The pulse injected into icemc is taken from Channel 1 of Testpico_avg_33dB+25dB...root and "trimmed" (timing window edited). The macros in this directory take trim the pulse and produce the output that was then injected into icemc.( the details of this are the script called trim_Avg_Ch1_pulses.C)

The mag-freq was taken for multiple attenuations and the ratio found to see if Channel 1 included variable attenuation or not. (macro included as plot_freq_mag_graphs.C).

The response of the antennas with the TUFFs ON but all notches off (configK or notches_0_0_0 directory and trigconfigK.imp in anitaBuildTool) were produced with macros included here and credited to Andrew Ludwig ().

Macro to plot the maxsnr histogram is included


-snr_trig vs att
-snr_dig vs att
-trig_eff vs att
-trig_eff vs snr_trig



Process is 
1) run trig_eff_makevalues.C to get an output of a textfile that has efficiency in one column and attenuaton in the other.
	 Also outputs the graphs of l3TrigPattern that was used in calculating the triggerefficiency
2) run plot_trig_eff_att(_graph).C to make a root file with a TProfile (TGraph) for the trigger efficiency versus attenuation
3) run snr_att_makerootfiles.C to generate a root file that has SNR of trigger and digitizer as histograms for each polarization
4) run plot_snr_att(_graphs).C to make a root file with TProfiles (Tgraphs) of the means of the snr for the trigger of Vertical pol versus attenuation
5) run plot_trig_eff_snr.C which will read in the root files from the previous steps (should be blah and blah) to produce a plot of trig eff vs snr
