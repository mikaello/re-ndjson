# re-ndjson

[![Build Status](https://dev.azure.com/mikaeo/re-ndjson/_apis/build/status/mikaello.re-ndjson?branchName=master)](https://dev.azure.com/mikaeo/re-ndjson/_build/latest?definitionId=1&branchName=master)

Convert to and from [NDJSON](https://en.wikipedia.org/wiki/JSON_streaming#Line-delimited_JSON)/JSON. If no option is given, the tool will infer what type of input it got and convert to the other.

## Usage

Download the OSX binary from the [release page](https://github.com/mikaello/re-ndjson/releases) or build the binary as described in the _Build_-section.

`ndjson --help`:

```
ndjson(1)                        Ndjson Manual                       ndjson(1)



NAME
       ndjson - convert to/from NDJSON to/from JSON

SYNOPSIS
       ndjson [OPTION]... FILE

DESCRIPTION
       ndjson convert FILE to JSON if it is in NDJSON format, if  FILE is in
       JSON format it will be converted to NDJSON. The result is printed to
       standard output.

OPTIONS
       --help[=FMT] (default=auto)
           Show this help in format FMT. The value FMT must be one of `auto',
           `pager', `groff' or `plain'. With `auto', the format is `pager` or
           `plain' whenever the TERM env var is `dumb' or undefined.

       -j, --from-json
           Convert from JSON file

       -n, --from-ndjson
           Convert from NDJSON file

       --version
           Show version information.

EXIT STATUS
       ndjson exits with the following status:

       0   on success.

       124 on command line parsing errors.

       125 on unexpected internal errors (bugs).

BUGS
       Open issue in  https://github.com/mikaello/re-ndjson/issues.

SEE ALSO
        https://github.com/madnight/ndjson-to-json and
       https://github.com/nypl-spacetime/json-to-ndjson



Ndjson 1.0.0                                                         ndjson(1)
```

## Build

If you want to build this program yourself, you need to have [_esy_](https://esy.sh/) installed and follow these instructions:

```
$ git clone https://github.com/mikaello/re-ndjson
$ cd re-ndjson
$ esy install
$ esy build
```

And make `_esy/default/store/b/re_ndjson-<hash>/default/executable/ReNdjsonApp.exe` available on your `$PATH` with a name you like. E.g.

```
$ cp -p _esy/default/store/b/re_ndjson-<hash>/default/executable/ReNdjsonApp.exe ~/bin/ndjson
$ echo "export PATH=\"$HOME/bin:$PATH\"" > ~/.bashrc
```

## Contribute

The program is written in ReasonML and compiled to native. Feel free to open a PR or issue if you find something that could be better :-)
