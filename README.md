# timer

For the moment C++ only.
The plan is to add Boost like in DPEcho, and a Fortran version.

## Usage 

It works with the `tik/tok` scheme and comes with a test unit. It contains:
- `tik`: starts stopwatch, void if repeated w/o stop in between
- `tok`: prints total time; does not stop the clock
- `tak`: prints lap (i.e. time elapsed since last valid lap, tak or tik)
- `rst`: reset 
- `pws`: pauses total and lap time;
- `seg`: to save partial time over a segment (experimental, unsupported);
- `lap`: like tak but no print, only return;
- `tot`: like tok but no print, only return.

## Authors and acknowledgment
Salvatore Cielo, Leibniz-Rechenzentrum

## License
Apache II
