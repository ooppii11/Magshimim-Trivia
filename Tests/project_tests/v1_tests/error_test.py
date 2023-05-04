from project_tests.messageUtilities import message


MESSAGE_SIZE = 1024
LOGIN_REQUEST_CODE =  2
ERROR_RESPONSE_CODE =  99
INVAILD_MESSAGE = {
    "username" : "test",
    "password" : "123456"
}

def error_test(socket):
    request = message(LOGIN_REQUEST_CODE, INVAILD_MESSAGE)
    socket.send(message.encode(request))
    response = message.decode(socket.recv(MESSAGE_SIZE))

    if not response.message_code == ERROR_RESPONSE_CODE:
        return False, "The server did not respond with the correct code" + response.message_data 
    return True