from project_tests.messageUtilities import message


MESSAGE_SIZE = 1024
SIGNUP_REQUEST_CODE =  1
SIGNUP_RESPONSE_CODE =  3
SIGNUP_TEST_DATA = {
    "username": "test",
    "password": "12345678",
    "email" : "XXXXXXX@XXXX.com"
}

    
def signup_test(socket):
    request = message(SIGNUP_REQUEST_CODE, SIGNUP_TEST_DATA)
    socket.send(message.encode(request))
    response = message.decode(socket.recv(MESSAGE_SIZE))

    if not response.message_code == SIGNUP_RESPONSE_CODE:
        return False, "The server did not respond with the correct code" + response.message_data 
    return True