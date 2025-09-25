# timer

An academic exercise. Ideally, the most compact timer you can find. For the moment C++ only.
Also, an example of integration with [p3em](https://gitlab.lrz.de/di52vum/p3em) for energy measure.

## Usage 

It works with the `tik/tok` scheme and comes with a test unit. It contains:
- `tik`: starts stopwatch, void if repeated w/o stop in between
- `tok`: prints total time; does not stop the clock
- `tak`: prints lap (i.e. time elapsed since last valid lap, tak or tik)
- `rst`: reset 
- `pws`: pauses total and lap time;
- `lap`: like tak but no print, only return
- `tot`: like tok but no print, only return

## Authors and acknowledgment
Salvatore Cielo, LRZ

## License
TBA