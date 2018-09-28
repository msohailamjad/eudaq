# EUDET-type beam telescopes using EUDAQ2

## Hardware

- Mimosa Sensors and NI DAQ: EUDAQ2 code here in ```user/eudet```
- EUDET or AIDA TLU: EUDAQ2 code in ```user/tlu```
- Reference Plane, for example FEI4, USBPix / STControl: EUDAQ2 code which is currently working is here: ```https://github.com/beam-telescopes/USBpix/tree/release_5.3_eudaq20```

## Running modes

Under testing.

In brackets the exemplary start scripts are quoted which can be found in ```user/eudet/misc/start_scripts```; the EUDAQ ini and conf-files in ```user/eudet/misc/conf```.

### Standard (EUDET) mode

The EUDET TLU (```01_eudet_tlu```) or the AIDA TLU (```01_aida_tlu```) in EUDET mode can be used.

EUDAQ1-like (global busy) data taking synchronising by Event ID:
- online: using one ```EventIDSyncDataCollector``` connected to all producer (```02_eudet_tlu_telescope``` or ```02_aida_tlu_telescope_eventID-DC```)
- offline: using multiple ```DirectSaveDataCollector``` each connected to one producer (```02_aida_tlu_telescope```) and merge them offline using ```euCliMergerStandardEventID``` (to be merged to the master) 

If the devices are reading out the Trigger ID, the synchronisation can also happen by this:
- online: using one ```TriggerIDSyncDataCollector``` connected to all producer (```02_aida_tlu_telescope_triggerID```) 
- offline: using multiple ```DirectSaveDataCollector``` each connected to one producer (```02_aida_tlu_telescope```) and merge them offline using ```euCliMergerStandardTriggerID``` (to be merged to the master) 

### Mixed mode

This can be used with the AIDA TLU and the the ```DUTIgnoreBusy``` option in order to allow multiple triggers within one Mimosa read out:

Mixed mode data taking synchronising by Trigger ID:
- online: using one ```TriggerIDSyncDataCollector``` connected to all producer (```02_aida_tlu_telescope_triggerID```)
- offline: using multiple ```DirectSaveDataCollector``` each connected to one producer (```02_aida_tlu_telescope```) and merge them offline using ```euCliMergerMixed``` (to be merged to the master) 

### AIDA mode

The synchronisation by timestamps will be developed and can be in usage if a (quasi)-continous read-out of the Mimosa data stream is available. 
This can happen with a new Mimosa DAQ, like the MMC3 board which is currently under development: https://github.com/SiLab-Bonn/pymosa

## User Manual

Wiki-Pages for operating EUDET-type beam telescopes: https://telescopes.desy.de/User_manual
