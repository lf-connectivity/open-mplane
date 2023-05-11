docker run  \
    -p 127.0.0.1:10000:830 -p 80:8000/tcp \
    -it mplane/mpclient-demo:latest \
    python3 /mplane_demo/server.py
