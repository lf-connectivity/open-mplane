#!/usr/bin/env python3
# (c) Facebook, Inc. and its affiliates. Confidential and proprietary.

import threading
import time
import subprocess
import xml.etree.ElementTree as ET

from flask import Flask, render_template
from flask_socketio import SocketIO
import grpc
import json

import mpclient_pb2_grpc as mpclient
from mpclient_pb2 import (
    Authentication,
    ConnectRequest,
    DisconnectRequest,
    NetconfRpcRequest,
    NetconfRpcResponse,
)

app = Flask(__name__, template_folder="/mplane_demo", 
                      static_folder="static", 
                      static_url_path="")
socketio = SocketIO(app)

# Globals
Alarms = []

# Constants
GRPC_HOST = "localhost"
GRPC_PORT = "50051"
GRPC_CERT = "/mplane_client/build/server.crt"

NETCONF_HOST = "host.docker.internal"
NETCONF_PORT = 9999
NETCONF_USER = "oran"
NETCONF_PASS = "Thunga1e"

NETCONF_RPC_TIMEOUT = 3

SERVER_CMD = "/mplane_client/build/wrapper.sh /mplane_client/build/mpc_client"

# Alarms RPC payload
ALARMS_YIN = open("/mplane_demo/getalarms.xml", "r").read()


def start_server():
    """Start the mpc_client application"""
    subprocess.Popen(SERVER_CMD.split())
    time.sleep(1)


def fetch_thread():
    """Periodically send an RPC to mpc_client to fetch alarms-list"""
    stub = mpclient.MpclientStub(
        grpc.secure_channel(
            f"{GRPC_HOST}:{GRPC_PORT}",
            grpc.ssl_channel_credentials(
                root_certificates=open(GRPC_CERT, "rb").read(),
            ),
        )
    )
    while True:
        conn_resp = stub.connect(
            ConnectRequest(
                host=NETCONF_HOST,
                port=NETCONF_PORT,
                auth=Authentication(
                    user=NETCONF_USER,
                    keys=[],
                    password=NETCONF_PASS,
                ),
            )
        )
        if not conn_resp.success:
            continue
        rpc_resp = stub.netconfRpc(
            NetconfRpcRequest(
                sessionId=conn_resp.sessionId,
                serializedYang=ALARMS_YIN,
                timeoutSec=NETCONF_RPC_TIMEOUT,
            )
        )
        if rpc_resp.status == NetconfRpcResponse.Status.SUCCESS:
            parseAlarms(rpc_resp.message)
        rpc_resp = stub.disconnect(DisconnectRequest(sessionId=conn_resp.sessionId))


def parseAlarms(xml_string):
    """Parse Alarms from alarms-list"""
    root = ET.fromstring(xml_string)
    new_alarms = []
    for alarm in root[0]:
        new_alarms += [{
            "id": alarm.find("{urn:o-ran:fm:1.0}fault-id").text,
            "severity": alarm.find("{urn:o-ran:fm:1.0}fault-severity").text,
            "description": alarm.find("{urn:o-ran:fm:1.0}fault-text").text, 
        }]
    global Alarms
    Alarms = new_alarms


@socketio.on("alarms")
def alarms():
    """Socket for fetching alarms from webserver"""
    global Alarms
    socketio.emit("alarms", {"alarms": json.dumps(Alarms)})


@app.route("/")
def home():
    """Homepage handler"""
    return render_template("index.html")


if __name__ == "__main__":
    start_server()
    t = threading.Thread(target=fetch_thread)
    t.start()
    socketio.run(app, host="0.0.0.0", port=8000)
