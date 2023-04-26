import project_tests.hello_test
import socket

ADRESS = "127.0.0.1"
PORT = 5555

def main():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        sock.connect((ADRESS, PORT))
        project_tests.hello_test.hello_test(sock)


if __name__ == "__main__":
    main()