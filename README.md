
## Repository Contents 

This repository contains C++ code for simulating and analyzing data from collider experiments. There are two main scripts provided, which each simulate a different energy case: 

- **14 TeV Case** 
- **100 TeV Case**

These scripts are designed to analyze data produced from these high energy physics experiments, generating a range of valuable information about events, including details about photon numbers, transverse momentum distributions, pseudorapidity distributions, and more. 

## Thesis including the results: https://drive.google.com/file/d/1f5dOEjC6Kw9MY2TIR6mNF3EKiMpX7i2H/view

## Script Overview 

The core of each script lies within the `Loop` function, which processes each event from the ROOT data file input. This function reads data from a `.root` file, processes it, and generates a new `.root` file with the analysis output. The script also generates several histograms for easy data visualization and interpretation.

### 14 TeV Case

This script reads from a data file called `tag_1_delphes_events.root` and writes output to `Output_14Tev.root`. It sets up specific parameters for the analysis, such as the cross-section, number of events, and data luminosity, and then defines a series of histograms.

Histograms generated in this script include:

- No. of Photons per event (`PhotonSize`)
- Transverse Momentum distribution for the leading and sub-leading photons (`Photon1_PT`, `Photon2_PT`)
- Pseudorapidity distribution for the leading and sub-leading photons (`Photon1_eta`, `Photon2_eta`)
- Invariant mass and Pseudorapidity for the Higgs Boson (`Higgs_Mass`, `Higgs_eta`)

### 100 TeV Case

Similar to the 14 TeV case, this script reads from a data file called `ppT0h_hT0aa_100TeV_Cut.root` and writes output to `Output(2)_100Tev.root`. It also sets up specific parameters for the analysis and defines a similar series of histograms, but adjusted for the 100 TeV case.

## How to Run the Code

In a ROOT session, you can run these scripts as follows:

1. Load the script: `root> .L analysis.C`
2. Create an instance of the analysis: `root> analysis t`
3. Fill data members with a chosen entry number: `root> t.GetEntry(12)` 
4. Show values of a chosen entry: `root> t.Show()`
5. Loop on all entries: `root> t.Loop()`

Please note that these scripts require ROOT to be installed and correctly set up in your environment.

## Further Information

These scripts were designed for analyzing simulated High Energy Physics (HEP) experiments, but can be easily adapted for other purposes. Please feel free to modify and use them as needed for your specific requirements.

Note that the code uses TLorentzVector for 4-vector calculations and handles the physics of particle events. The analysis can be adjusted by modifying the various parameters defined in each script, and the range and granularity of the histograms can be adjusted to better suit the data under analysis.

## Dependencies

These scripts require ROOT, a modular scientific software toolkit, to run. ROOT provides all the functionalities needed to deal with large data processing, statistical analysis, visualisation and storage.

Before running these scripts, please ensure you have ROOT installed on your system. You can find instructions for downloading and installing ROOT via the following link: https://root.cern/install/.
