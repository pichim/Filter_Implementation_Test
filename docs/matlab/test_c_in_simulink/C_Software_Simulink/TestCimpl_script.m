clc, clear all
%%
importedTypes = Simulink.importExternalCTypes('pt1filter.h')
Ts = 1/25e3;
Tf = 2;