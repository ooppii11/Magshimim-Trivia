import project_tests.hello_test
import socket

ADRESS = "127.0.0.1"
PORT = 5555
TESTS = [
    project_tests.hello_test
]


def execute_tests(socket):
    for test in TESTS:
        if output:=type(test(socket)) == tuple:
            print(output[1])
            return
    print("The program pass the tests:({}/{})".format(len(TESTS), len(TESTS)))


def main():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        sock.connect((ADRESS, PORT))
        execute_tests(sock)


if __name__ == "__main__":
    main()