//  ECAL Dimension
const double ECalSizeX =30.;   //in cm
const double ECalSizeY =30.;   //in cm
const double ECalSizeZ =22.;   //in cm full scale length

const double ECalPosiX =0.;	//in cm
const double ECalPosiY =0.;	//in cm
const double ECalPosiZ =180.+ECalSizeZ*0.5;	//in cm

const int ECalNRow       = 30;
const int ECalNCol       = 30;
const int ECalNCells     = ECalNRow*ECalNCol;
const double ECalInnHole = 4.5; // this is radius

//Cluster reconstruction variables
const double SeedE    = 8.;     //in MeV
const double CellsE   = 0.2;     //in MeV
const double RadiusCl = 4.6;     //in cm due righe due colonne
const double IsCaloCalibON= 0.;  //Calor calibration constants: 0 all 1; 1 gauss with sigma = 1%
