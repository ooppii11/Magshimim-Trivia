import json
import struct

SIGNUP_TEST_MESSAGES = [
    {"username": "test", "password": "12345678", "email" : "XXXXXXX@XXXX.com"}
    ]

LOGIN_TEST_MESSAGES = [
    {"username" : "test", "password" : "12345678"}
    ]

INVAILD_MESSAGES = [
    {"" : ""}, 
    {"username": "test", "password": "123456", "email" : "XXXXXXX@XXXX.com"}, 
    {"username" : "test", "password" : "123456"}
    ]

CODES = {
    "SignupRequest" : 1,
    "LoginRequest" : 2,
    "signupResponse" : 3,
    "loginResponse" : 4,
    "errorResponse" : 99,
}


class info:
    def __init__(self, msg, requestCode, responseCode):
        self.msg = msg
        self.requestCode = requestCode
        self.responseCode = responseCode


def sendMsg(socket, info):
    request = chr(info.requestCode)
    if(len(json.dumps(info.msg)) <= 2**(4*8)):
        request += ''.join([chr(byte) for byte in struct.pack("I", len(json.dumps(info.msg)))])
        request += json.dumps(info.msg)
    socket.sendall((request).encode())
    data = socket.recv(1024)
    if not ((data.decode()).startwith(chr(info.responseCode))):
        return False
    return True


def signup_test(socket):
    count = 0
    for msg in SIGNUP_TEST_MESSAGES:
        count += 1
        if(not (sendMsg(socket, info(msg, CODES["SignupRequest"], CODES["signupResponse"])))):
            return False, "The server did not respond with the correct code for the " + str(count) + " test in login_test"
    return True, "The server responded with the correct code for all tests in login_test:"


def login_test(socket):
    count = 0
    for msg in LOGIN_TEST_MESSAGES:
        count += 1
        if(not (sendMsg(socket, info(msg, CODES["LoginRequest"], CODES["loginResponse"])))):
            return False, "The server did not respond with the correct code for the " + str(count) + " test in login_test"
    return True, "The server responded with the correct code for all tests in login_test:"


def error_test(socket):
    count = 0
    for msg in INVAILD_MESSAGES:
        count += 1
        if(not (sendMsg(socket, info(msg, CODES["LoginRequest"], CODES["errorResponse"])))):
            return False, "The server did not respond with the correct code for the " + str(count) + " test in error_test"
    count += 1
    for msg in INVAILD_MESSAGES:
        if(not (sendMsg(socket, info(msg, CODES["SignupRequest"], CODES["errorResponse"])))):
                return False, "The server did not respond with the correct code for the " + str(count) + " test in error_test"
    return True, "The server responded with the correct code for all tests in error_test:"
