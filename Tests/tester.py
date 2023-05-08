import project_tests
import socket

ADRESS = "127.0.0.1"
PORT = 5555
TESTS = [
    #project_tests.hello_test,
    project_tests.signup_test,
    project_tests.login_test,
    project_tests.error_test
]


def execute_test(socket, test):
    output = test(socket)
    if type(output) == tuple:
        print(output[1])
        return False
    return True


def execute_tests():
    for test in TESTS:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
            sock.connect((ADRESS, PORT))
            if not execute_test(sock, test): return
    print("The program pass the tests:({}/{})".format(len(TESTS), len(TESTS)))


def main():
    execute_tests()


if __name__ == "__main__":
    main()
	
	
	
	
	