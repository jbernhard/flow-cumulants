# Flow cumulants

A Python implementation of the direct _Q_-cumulant method from
[nucl-ex/1010.0233](http://inspirehep.net/record/871528)
([PDF](http://arxiv.org/pdf/1010.0233.pdf)) and 
[A. Bilandzic's thesis](https://inspirehep.net/record/1186272?ln=en)
([PDF](https://inspirehep.net/record/1186272/files/CERN-THESIS-2012-018.pdf)).

## Requirements

Python 3 with numpy and numexpr.

## Usage

This is a simple script for calculating flow cumulants for batches of events stored in text files.  Files must
contain a column of particle phi (azimuthal angle), and events should be separated by blank lines or comments
(#).

Basic usage is

    flow-cumulants < events.dat

i.e. event data is read from stdin.  This allows easy parallelization via GNU parallel and handling of
compressed files via e.g. zcat.

For additional information see `flow-cumulants -h/--help`.

## Notes

I wrote this mainly

* to practice implementing a flow cumulant algorithm;
* to see how cool numexpr is (seriously, it's awesome).
