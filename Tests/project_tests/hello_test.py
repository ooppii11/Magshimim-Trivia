MESSAGE = "Hello"

def hello_test(socket):
    message = socket.recv(len(MESSAGE)).decode()
    socket.send(MESSAGE.encode())
    if message == MESSAGE:
        return True
    return False, "The server doesn't sent 'Hello' message"