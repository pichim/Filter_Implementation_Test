clc, clear all
%%
% addpath ..\..\..\..\iir_filter\
importedTypes = Simulink.importExternalCTypes(...
    fullfile('..', '..', '..', '..', 'iir_filter', 'iirfilter_c.h'));
Ts = 1/25e3;
fcut = 1.0 / (2.0*pi*2.0);