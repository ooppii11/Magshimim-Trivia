from project_tests.messageUtilities import message


MESSAGE_SIZE = 1024
LOGIN_REQUEST_CODE =  2
LOGIN_RESPONSE_CODE =  4
LOGIN_TEST_MESSAGE_DATA = {
    "username": "test",
    "password": "12345678"
}
    
def login_test(socket):
    request = message(LOGIN_REQUEST_CODE, LOGIN_TEST_MESSAGE_DATA)
    socket.send(message.encode(request))
    response = message.decode(socket.recv(MESSAGE_SIZE))

    if not response.message_code == LOGIN_RESPONSE_CODE:
        return False, "The server did not respond with the correct code" + response.message_data 
    return True