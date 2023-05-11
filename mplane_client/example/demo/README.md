# M-Plane Demo

A small demonstration of an M-Plane e2e request and response. This demo is
written as a docker container which can be run on an arbitrary host.

## Build

From the directory above `mplane_demo`, i.e. `mplane-rru/mplane/mpclient`, run 
`docker build -f demo.Dockerfile --tag mplane/mpclient-demo:latest`. Note that 
the image `mplane/mpclient-built-tests:latest` is expected to be available in
your local Docker images. `mplane/mpclient-built-tests:latest` is built during
the mpclient dockerized build.

## Run

Port 80 should be available on localhost. Port 9999 on localhost should forward
to an M-Plane server. Port 9999 can be directed to forward to an M-Plane server
port with `ssh`, e.g.:

```
ssh -L 9999:localhost:830 <M-Plane server host>
```

Once port 9999 is setup, run `mplane_demo/run_demo.sh`. The console will contain
a log from `mpclient-server` and the webapp running in the docker container, and
a webpage displaying information fetched from the M-Plane server will be
available at `localhost:80`.

## Files

- `getalarms.xml`: A yin payload for fetching the `active-alarm-list` O-RAN YANG leaf
- `index.html`: The webpage served by the demo
- `mpclient_pb2.py`: gRPC python bindings
- `mpclient_pb2_grpc.py`: gRPC python stubs
- `run_demo.sh`: Helper script for starting the demo
- `server.py`: The python program containing the webapp and a thread which
  periodically fetches the `active-alarms-list`
- `static/`: JS and CSS for the homepage

`mpclient_pb2.py` and `mpclient_pb2_grpc.py` are generated from mpclient.proto.
The following command generates these files:

```
python3 -m grpc_tools.protoc --experimental_allow_proto3_optional -I./if \
--python_out=. --grpc_python_out=. mpclient.proto
```

libprotoc version 3.13.0 was used to generate the files.
