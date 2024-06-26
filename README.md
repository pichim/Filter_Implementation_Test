# Filter Implementation Test

## TODO

- Check if frequency response estimation in python is correct and double check MATLAB and Python version
- Further improve SDFT towards dynamic notch implementation
- Move MATLAB SDFT implementation to this repo

## Implementation

IIR filter, fading notch and chirp signal generator implementation in C and  in C++.

The filters are excited with a chirp signal and the filter response is stored as a text file.

## Evaluation

The evaluation is done in MATLAB and in Python.

Using the filter input and output, the frequency response of the filters is estimated and compared to the theoretical time discrete as well as time continous frequency response.

The fading notch filter is also evaluated.

The evaluation in Python can directly be inspected on GitHub: [docs/python/eval_filter_implementation.ipynb](docs/python/eval_filter_implementation.ipynb)

## Links
- https://webaudio.github.io/Audio-EQ-Cookbook/audio-eq-cookbook.html
- https://ccrma.stanford.edu/~jos/filters/filters.html
